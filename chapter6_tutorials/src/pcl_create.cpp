#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

int main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_create");
    ros::NodeHandle nh;

    
   // pcl::PointCloud<pcl::PointXYZ> cloud;
    

    
    pcl::PointCloud<pcl::PointXYZ>::Ptr clouda_ptr (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile<pcl::PointXYZ> ("/home/lucifr/code/voxel_grid/bin_Laser-00161_-00861.pcd", *clouda_ptr);
    
    sensor_msgs::PointCloud2 clouda_ros;
    pcl::toROSMsg (*clouda_ptr, clouda_ros);
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("cloud__a", 1); 
    //clouda_ros.header.frame_id = "sensor_framec";


  //  ros::Rate loop_rate(1);
    ros::Rate r(3);
    while (ros::ok()) 
    { 
        
        clouda_ros.header.stamp = ros::Time::now();
        clouda_ros.header.frame_id = "sensor_framec";
	pcl_pub.publish(clouda_ros);
	//ros::spinOnce();
	r.sleep(); 
    }
    ros::spin ();
    return 0;
}
