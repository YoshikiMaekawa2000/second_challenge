#ifndef GLOBAL_PATH_PLANNER_H
#define GLOBAL_PATH_PLANNER_H

#include <ros/ros.h>
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"


struct coordinate
{
    float x;
    float y;
};

class Global_path_planner
{
    public:
        Global_path_planner();
        void process();
    private:

        void map_callback(const nav_msgs::OccupancyGrid::ConstPtr &msg);
        void thick_wall();
        void set_goal();

        int hz;
        int width;
        int height;
        std::vector<std::vector<int>> map_grid;
        std::vector<std::vector<int>> map_grid_copy;
        std::vector<coordinate> goal;

        coordinate origin;


        // std::vector< std::vector<int> > map_grid;

        bool map_check=false;
        bool wall_check=false;
        bool goal_check=false;

        ros::NodeHandle nh;
        ros::NodeHandle private_nh;

        ros::Subscriber sub_map;

        nav_msgs::OccupancyGrid map;

};

#endif
