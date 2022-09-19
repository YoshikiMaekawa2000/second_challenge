#ifndef LOCAL_MAP_CREATOR.H
#define LOCAL_MAP_CREATOR.H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>

class local_map_creator
{
    public:
        local_map_creator();
        void process();

    private:
        void laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg);
        // void init_map();
        // void create_local_map();


        int hz;
        bool laser_info_came_ = false;


        ros::NodeHandle nh;
        ros::NodeHandle pnh;

        ros::Subscriber sub_laser;
        ros::Publisher pub_local_map;
        ros::Publisher pub_obstacle_poses;

        nav_msgs::OccupancyGrid local_map_msg;
        sensor_msgs::LaserScan laser_msg;
        geometry_msgs::PoseArray obstacle_poses_msg;


};

#endif
//
//
//
