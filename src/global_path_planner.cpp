#include "global_path_planner/global_path_planner.h"

Global_path_planner::Global_path_planner():private_nh("~")
{

    private_nh.param("hz",hz, {10});
    sub_map=nh.subscribe("/map", 10, &Global_path_planner::map_callback, this);
}

void Global_path_planner::map_callback(const nav_msgs::OccupancyGrid::ConstPtr &msg)
{
    map = *msg;
    map_check=true;

    height = map.info.height;         //row, 行
    width  = map.info.width;          //col, 列

    //型（vectorの２次元配列）　　　　変数名　　　初期化
    //std::vector<int> 変数名 (要素数、値）
    // std::vector< std::vector<int> >  map_grid  (height, std::vector<int> (width, 0));
    // std::vector< std::vector<int> >  map_grid_copy  (height, std::vector<int> (width, 0));
    map_grid = std::vector< std::vector<int> >(height, std::vector<int>(width, 0));
    map_grid_copy = std::vector< std::vector<int> >(height, std::vector<int>(width, 0));

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            map_grid[i][j] = map.data[i+j*width];
            map_grid_copy[i][j] = map.data[i+j*width];
        }
    }

    //origin mean point which is edge of left down
    origin.x = map.info.origin.position.x;
    origin.y = map.info.origin.position.y;
}

void Global_path_planner::thick_wall()
{
    // for(int i=5; i<height-5; i++)
    // {
    //     for(int j=5; j<width; j++)
    //     {
    //         if(map_grid_copy[i][j]==100)
    //         {
    //             for(int k=i-2; k<i+3; k++)
    //             {
    //                 for(int l=j-2; l<j+3; l++)
    //                 {
    //                     map_grid[k][l]=100;
    //                 }
    //             }
    //         }
    //     }
    // }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            map.data[i+j*height] = map_grid[i][j];
        }
    }
    wall_check=true;
}

void Global_path_planner::set_goal()
{
    goal = {{2000, 2000}, {2320, 2010}, {2320, 2290}, {2000, 2290}, {1660, 2280}, {1600, 2000}, {2000, 2000}};
    goal_check = true;
}







void Global_path_planner::process()
{
    ros::Rate loop_rate(hz);

    while(ros::ok())
    {
        ROS_INFO("map_callback: %d", map_check);
        ROS_INFO("wall_check  : %d", wall_check);
        ROS_INFO("goal_check  : %d", goal_check);
        if(map_check)
        {
            thick_wall();

            if(wall_check)
            {
                set_goal();
            }

        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Global_path_planner");
    Global_path_planner global_path_planner;
    global_path_planner.process();
    return 0;

}
