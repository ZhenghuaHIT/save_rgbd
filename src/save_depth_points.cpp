//----------------------------------------------------
// 2017.3.4
// save_depth_points.cpp
// 功能：实现订阅kinect深度图像，并保存（鼠标点击图像窗口，按空格键保存）
// 编写：王力
// 学号：15B908017
//----------------------------------------------------

#include <ros/ros.h>
#include <iostream>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <sensor_msgs/PointCloud2.h>

using namespace std;
using namespace pcl;

unsigned int filesNum = 0;

bool saveCloud(false);

boost::shared_ptr<visualization::CloudViewer> viewer;

void cloudCB(const sensor_msgs::PointCloud2& input)
{
  pcl::PointCloud<pcl::PointXYZRGBA> cloud;
  pcl::fromROSMsg(input, cloud);
  if(!viewer->wasStopped())
    viewer->showCloud(cloud.makeShared());

  if(saveCloud)
  {
    stringstream stream;
    stream << "inputCloud" << filesNum << ".pcd";
    string filename = stream.str();

    if(io::savePCDFile(filename, cloud, true) == 0)
    {
      filesNum++;
      cout << filename << "Saved." << endl;
    }
    else
      PCL_ERROR("Problem saving %s.\n", filename.c_str());

    saveCloud = false;
  }
}

void keyboardEventccured(const visualization::KeyboardEvent& event, void* nothing)
{
  if(event.getKeySym() == "space" && event.keyDown())
    saveCloud = true;
}

boost::shared_ptr<visualization::CloudViewer> createViewer()
{
  boost::shared_ptr<visualization::CloudViewer> v(new visualization::CloudViewer("OpenNI viewer"));
  v->registerKeyboardCallback(keyboardEventccured);

  return(v);
}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "save_depth_points");
  ros::NodeHandle nh;
  cout << "Press space to record point cloud to a file." << endl;

  viewer = createViewer();
  ros::Subscriber pcl_sub = nh.subscribe("/camera/depth_registered/points", 1000, cloudCB);

  //ros::Subscriber pcl_sub = nh.subscribe("/camera/depth_registered/image", 1, cloudCB);

  ros::Rate rate(30.0);

  while(ros::ok() && !viewer->wasStopped())
  {
    ros::spinOnce();
    rate.sleep();
  }
  //ROS_INFO("Hello world!");
  return 0;
}
