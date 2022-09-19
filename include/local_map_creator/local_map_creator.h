#ifndef LiOCAL_MAP_CREATOR_H
#define LOCAL_MAP_CREATOR_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>

class Local_map_creator
{
    public:
        Local_map_creator();
        void process();

    private:
        void laser_callback(const sensor_msgs::LaserScan::ConstPtr &msg);
        void init_map();
        void create_local_map();
        bool angle_check(double angle);
        void point_obstacle(double angle, double laser_range);

        int hz;
        int local_map_size;
        int laser_step;
        double local_map_reso;
        double roomba_radius;
        double ignore_angle_mergin;



        bool laser_check;


        ros::NodeHandle nh;
        ros::NodeHandle private_nh;

        ros::Subscriber sub_laser;
        ros::Publisher pub_local_map;
        ros::Publisher pub_obstacle_poses;

        nav_msgs::OccupancyGrid local_map;
        sensor_msgs::LaserScan laser;
        geometry_msgs::PoseArray obstacle_poses;


};

#endif
//
//
//
