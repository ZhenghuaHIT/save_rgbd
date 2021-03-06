//----------------------------------------------------
// 2017.3.3
// save_rgb.cpp
// 功能：实现订阅kinect彩色图像，并保存（鼠标点击图像窗口，按空格键保存）
// 编写：王力
// 学号：15B908017
//----------------------------------------------------

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <fstream>
//定义每次保存的图像数目
#define saveFrameNum 100

using namespace std;
using namespace cv_bridge;


bool saveImage(true);

ofstream out;
void saveFeatureFile(string content)
{  
        out.open("/home/hou/data/rgbddata/rgb.txt",ios::app);
        if (out.is_open())
        { 
          out <<content<<"\n";                              
          out.close();
        }        
}


void imageCallBack(const sensor_msgs::ImageConstPtr& msg)
{
  cv::imshow("Show RgbImage", cv_bridge::toCvShare(msg, "rgb8")->image);//指定cv_bridge::toCvShare的msg类型rgb8

  char key;
  // key = cvWaitKey(33);//检测键盘按键延时时间，设置过短可能导致按键检测不到
  // key = cvWaitKey(15);
  // cout<<key<<endl;
 if(key == 32)
  {
    saveImage = false;    
  }
  if(key == 's')
  {
    saveImage = true;    
  }

  if(saveImage)
  {
    string strtime;
    stringstream stream2;
    stream2<<ros::Time::now();
    strtime = stream2.str();
    // cout<<strtime<<endl;
    string filename=strtime;  
    filename.append(".png");

    string content("");
    content.append(strtime);
    content.append("  rgb/");
    content.append(filename);
    saveFeatureFile(content);
    

    string fullfilename("/home/hou/data/rgbddata/rgb/");
    fullfilename.append(filename); 
    cv::imwrite(fullfilename, cv_bridge::toCvShare(msg)->image);    

    cout << filename << " had saved." << endl;
  }
}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "save_rgb");

  ros::NodeHandle nh;
  cv::namedWindow("Show RgbImage");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  // image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw", 1000, imageCallBack);
  image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_color", 1, imageCallBack);
  //image_transport::Subscriber sub = it.subscribe("/camera/ir/image_raw", 1, imageCallBack);

  //image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/image", 1, imageCallBack);


  //image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/image_raw", 1, imageCallBack);

  //image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw", 1, imageCallBack);


  // image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw/compressed", 1, imageCallBack);
  // image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw/compressedDepth", 1, imageCallBack);
  // image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw/theora", 1, imageCallBack);
  // image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/hw_registered/image_rect", 1, imageCallBack);
  // image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_rect_color", 1, imageCallBack);


  ros::spin();
  cv::destroyWindow("Show RgbImage");

  //ROS_INFO("Hello world!");
}
