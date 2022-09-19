#include <local_map_creator/local_map_creator.h>



Local_map_creator::Local_map_creator():private_nh("~"){

    private_nh.param("hz", hz, {10});
    private_nh.param("local_map_size", local_map_size, {4});
    private_nh.param("local_map_reso", local_map_reso, {0.05});
    private_nh.param("laser_step", laser_step, {10});

    private_nh.param("laser_check", laser_check, {false});

    local_map.info.resolution = local_map_reso;
    local_map.info.width = local_map_size/local_map_reso;
    local_map.info.height = local_map_size/local_map_reso;
    local_map.info.origin.position.x = -local_map_size/2;
    local_map.info.origin.position.y = -local_map_size/2;
    local_map.data.reserve(local_map.info.width * local_map.info.height);


    //topic名"scan"は、送信側であらかじめ決められているので変更不可
    sub_laser = nh.subscribe("scan", 10, &Local_map_creator::laser_callback, this);

    pub_local_map = nh.advertise<nav_msgs::OccupancyGrid>("local_map_topic", 10);
    pub_obstacle_poses = nh.advertise<geometry_msgs::PoseArray>("obstacle_poses_topic", 1);

    init_map();
    obstacle_poses.poses.clear();


}

//Lidarから情報を受け取り、下流のモジュールに流す
void Local_map_creator::laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    laser=*msg;
    laser_check=true;
}

//local_mapの初期化
void Local_map_creator::init_map()
{
    //iheader fileでnav_msgs::OccupancyGrid local_map;を宣言

    local_map.data.clear();

    for(int i=0; i< sizeof(local_map.data); i++){
        local_map.data.push_back(-1); //未知領域は-1。すべてのマスを未知領域とする
    }

}

void Local_map_creator::create_local_map()
{
    double scan_angle=laser.angle_max - laser.angle_min;

    for(int i=0; i<int(laser.ranges.size()); i+=laser_step){
        double angle=i*laser.angle_increment + laser.angle_min;
        point_obstacle(angle, laser.ranges[i]);
    }
}

bool Local_map_creator::angle_check(double angle)
{
    // adjust_yaw(angle);

    if(angle > -3.0/4 * M_PI + ignore_angle_mergin && angle < -1.0/4 * M_PI - ignore_angle_mergin){
        return true;
    } else if(angle > -1.0/4 * M_PI + ignore_angle_mergin && angle < 1.0/4 * M_PI - ignore_angle_mergin){
        return true;
    } else if(angle > 1.0/4 * M_PI + ignore_angle_mergin && angle < 3.0/4 * M_PI - ignore_angle_mergin){
        return true;
    }
    return false;
}


void Local_map_creator::point_obstacle(double angle, double laser_range)
{
    double search_step = local_map_reso;
    if(laser_range < roomba_radius || !angle_check(angle))
    {
        laser_range = local_map_size;
    }

    for(double dist_from_start = 0; dist_from_start < local_map_size; dist_from_start += sertch_step)
    {
        double x_now = dist_from_start * std::cos(angle);
        double y_now = dist_from_start * std::sin(angle);

        if(
}





void Local_map_creator::process()
{
    ros::Rate rate(hz);
    while(ros::ok()){

        if(laser_check){
            // ROS_INFO("laser_info :%d",laser_check);
            create_local_map();


        }
        ros::spinOnce();
        rate.sleep();
    }
}
            // init_map();
            // create_local_map();
            //
            //



int main(int argc, char** argv){
    ros::init(argc, argv, "local_map_creater");
    Local_map_creator local_map_creator;
    local_map_creator.process();

    return 0;
}

