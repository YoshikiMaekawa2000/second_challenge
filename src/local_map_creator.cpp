#include <local_map_creator/local_map_creator.h>



local_map_creator::local_map_creator():private_nh("~"){

    private_nh.getParam("hz", hz);
    // private_nh.getParam("map_size", map_size);



    sub_laser=nh.subscribe("laser_topic", 10, &local_map_creator::laser_callback, this);


}

//Lidarから情報を受け取り、下流のモジュールに流す
void local_map_creator::laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    laser=*msg;
    laser_info_came_=true;
}

//local_mapの初期化
// void local_map_creator:init_map()
// {
//     //header fileでnav_msgs::OccupancyGrid local_map;を宣言
//     local_map.data.clear();
//
//     int size=local_map.info.width * local_map.info.height;
//     for(int i=0; i<size; i++){
//         local_map.data.push_back(-1); //未知領域は-1。すべてのマスを未知領域とする
//     }
// }

// void local_map_creator::create_local_map()
// {
//     //headerでgeometry_msgs::PoseArray obstacle_poses;を宣言
//     obstacle_poses.pose.clear();
//     double scan_angle=laser.angle_max - laser.angle_min;
//
//     int laser_step=int(2*map_reso*laser.ranges.size()/laser_density/scan_angle/map_size);
//     for(int i=0; i<int(laser.ranges.size()); i+=laser_step){
//         double angle=i*laser.angle_increment + laser.angle_min;
//         create_line(angle, laser.ranges[i]);
//     }
// }


void local_map_creater::process()
{
    ros::Rate rate(hz);
    while(ros::ok()){
        if(laser_info_came_){
            ROS_INFO("laser_info :%s",laser_info_came)
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
    local_map_creater local_map_creator;
    local_map_creater.process();

    return 0;
}

