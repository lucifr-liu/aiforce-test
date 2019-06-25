#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

ros::Publisher pub;
sensor_msgs::PointCloud2 output;//声明的输出的点云的格式
int main (int argc, char** argv)
{
  ros::init (argc, argv, "voxel_grid");//声明节点的名称
  ros::NodeHandle nh;
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  //pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());

  //pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; //原始的点云的数据格式
  //pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;//存储滤波后的数据格式

  pub = nh.advertise<sensor_msgs::PointCloud2> ("ot_pt", 100);

  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("/home/lucifr/code/voxel_grid/bin_Laser-00161_-00861.pcd", *cloud); // Remember to download the file first!

  std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
       << " data points (" << pcl::getFieldsList (*cloud) << ").";
 
 std::cout << "1" << std::endl;
  // Create the filtering object
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  std::cout << "2" << std::endl;
 // sor.setInputCloud (cloudPtr);  //设置输入的滤波，将需要过滤的点云给滤波对象
  sor.setInputCloud (cloud);
std::cout << "3" << std::endl;
  sor.setLeafSize (0.3f, 0.3f, 0.3f);  //值越大，采样越稀疏
std::cout << "4" << std::endl;
  sor.filter (cloud_filtered);

   std::cerr << "PointCloud after filtering: " //<< cloud_filtered->width * cloud_filtered->height 
      << " data points (" << pcl::getFieldsList (cloud_filtered) << ").";


std::cout << "5" << std::endl;
 //pcl::toROSMsg(cloud, output);
  pcl_conversions::moveFromPCL(cloud_filtered, output);//第一个参数是输入，后面的是输出
std::cout << "6" << std::endl;
  output.header.frame_id = "base2_link";;
  std::cout << "7" << std::endl;
  // Publish the data
  pub.publish (output);
std::cout << "10" << std::endl;  
  ros::spin ();
std::cout << "9" << std::endl; 
return 0;
  
}
