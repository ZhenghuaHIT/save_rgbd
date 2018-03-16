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

//定义每次保存的图像数目
#define saveFrameNum 100

using namespace std;
using namespace cv_bridge;

unsigned int fileNum = 0;//保存数据的文件名编号
unsigned int imageNum = 1;//图像的编号
bool saveImage(false);

void imageCallBack(const sensor_msgs::ImageConstPtr& msg)
{
    
  cv::imshow("Show RgbImage", cv_bridge::toCvShare(msg, "rgb8")->image);//指定cv_bridge::toCvShare的msg类型rgb8  

  char key;
  key = cvWaitKey(33);//检测键盘按键延时时间，设置过短可能导致按键检测不到
//   key = cvWaitKey(15);
  if(key == 32)//空格按键
  {
    saveImage = true;
    fileNum++;
  }

  if(saveImage)
  {
    stringstream stream;
    string filename;
    

    stream << "/home/hou/data/rgbddata/" << fileNum << "/" << imageNum << ".png";

    //string filename = stream.str();
    filename = stream.str();
    cv::imwrite(filename, cv_bridge::toCvShare(msg)->image);

    static unsigned int frameNum = 1;
    if(frameNum == saveFrameNum)
    {
      saveImage = false;
      frameNum = 0;
      imageNum = 0;
    }
    frameNum++;
    imageNum++;

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
//   image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw", 1000, imageCallBack);
 image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_color", 1, imageCallBack);
//   image_transport::Subscriber sub = it.subscribe("/camera", 1, imageCallBack);
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
