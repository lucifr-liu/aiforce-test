#include "ros/ros.h"
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>
#include <octomap_ros/conversions.h>
#include <octomap/octomap.h>
#include <message_filters/subscriber.h>
#include "visualization_msgs/Marker.h"
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/base/OptimizationObjective.h>
#include <ompl/base/objectives/PathLengthOptimizationObjective.h>
#include <ompl/geometric/planners/rrt/InformedRRTstar.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/config.h>
#include <iostream>

using namespace std;
using namespace octomap;

void octomap_cb (const octomap_msgs::Octomap2ConstPtr& octomap_msg)
{

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "octomap_rviz");
    ros::NodeHandle n;

    ros::Subscriber octree_sub = n.subscribe<octomap_msgs::Octomap>("/octomap_full", 1, octomap_cb);
    

//  vis_pub = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
    vis_pub = n.advertise<nav_msgs::Path>( "visualization_marker", 0 );
//  traj_pub = n.advertise<trajectory_msgs::MultiDOFJointTrajectory>("waypoints",1);
    traj_pub = n.advertise<nav_msgs::Path>("waypoints",1);
    
    std::cout << "1" << std::endl;

    ros::spin();

    return 0;
}
