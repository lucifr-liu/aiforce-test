    #include<ros/ros.h>  
    #include<pcl/point_cloud.h>  
    #include<pcl_conversions/pcl_conversions.h>  
    #include<sensor_msgs/PointCloud2.h>  
    #include<pcl/io/pcd_io.h>
      
    int main (int argc, char **argv)  
    {  
      ros::init (argc, argv, "orbslam");  
      ros::NodeHandle nh;  
      ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("/orbslam2_with_kinect2", 10);  
      
      pcl::PointCloud<pcl::PointXYZ> cloud;  
      sensor_msgs::PointCloud2 output;  
      pcl::io::loadPCDFile ("/home/lucifr/code/voxel_grid/table_scene_lms400.pcd", cloud);  
      pcl::toROSMsg(cloud,output);// 转换成ROS下的数据类型 最终通过topic发布
	
      output.header.stamp=ros::Time::now();
      output.header.frame_id  ="camera_rgb_frame";
	
      ros::Rate loop_rate(2);  
      while (ros::ok())  
      {  
        pcl_pub.publish(output);  
        std::cout << "4" << std::endl;
        ros::spinOnce();  
        loop_rate.sleep();  
      }  
      return 0;  
    }  



