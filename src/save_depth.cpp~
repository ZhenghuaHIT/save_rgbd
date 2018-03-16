//----------------------------------------------------
// 2017.3.8
// save_depth.cpp
// 实现订阅kinect深度图像，并保存（鼠标点击图像窗口，按空格键保存）
// by WangLi
//----------------------------------------------------

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <fstream>
//定义每次保存的图像数目
#define saveFrameNum 100
#define depthScale 5000//kinect深度尺度因子
using namespace std;
using namespace cv_bridge;

bool saveDepth(true);


ofstream out;
void saveFeatureFile(string content)
{  
        out.open("/home/hou/data/rgbddata/depth.txt",ios::app);
        if (out.is_open())
        { 
          out <<content<<"\n";                              
          out.close();
        }    
}



void imageCallBack(const sensor_msgs::ImageConstPtr& msg)
{
  IplImage image = cv_bridge::toCvShare(msg)->image;

  cv::Mat getImage2;cv::Mat getImage;
  getImage2 = cv::Mat(&image);//IplImage格式转换为cv::Mat

  float centerValue = 0;
  //centerValue = (float)getImage.at<ushort>(239, 319);
  centerValue = getImage2.at<float>(239, 319);
  //cout << "图像中心点深度值：" << centerValue << endl;

 // cout << "msg：" << msg << endl;
  // cout << "matimage：" << getImage << endl;
  //转换深度图像格式，原始深度图像类型为32FC1，为float类型，不能保存为图像格式，需要转换为16UC1格式
  getImage2.convertTo(getImage, CV_16UC4, depthScale, 0);



  //cv::imshow("Show DepthImage msg", cv_bridge::toCvShare(msg, "16UC1")->image);//未指定cv_bridge::toCvShare的msg类型，按照原始数据格式读取
  cv::imshow("Show DepthImage", getImage);
  
  char key;
  //key = cvWaitKey(33);//检测键盘按键延时时间，设置过短可能导致按键检测不到
  // key = cvWaitKey(15);//空格按键

  if(key == 32)
  {
    saveDepth = false;    
  }
  if(key == 115)
  {
    saveDepth = true;    
  }

  if(saveDepth)
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
    content.append("  depth/");
    content.append(filename);
    saveFeatureFile(content);
    

    string fullfilename("/home/hou/data/rgbddata/depth/");
    fullfilename.append(filename); 
    //cv::imwrite(filename, cv_bridge::toCvShare(msg, "16UC1")->image);
    cv::imwrite(fullfilename, getImage);
    


    //cv::imwrite(filename, cv_ptrD->image);



    //saveDepth = false;

    //输出图像中心点深度值
    ushort centerVal = 0;
    float temp;
    centerVal = getImage.at<ushort>(239, 319);
    temp = (float)centerVal/depthScale;
    cout << "转换后图像中心点深度值：" << temp<< endl;
    
    //cout << filename << "had saved." << endl;

     ofstream out2;
     ofstream out3;
     out2.open("/home/hou/data/rgbddata/msg.txt",ios::app);
        if (out2.is_open())
        { 
          out2 <<&image<<"\n"<<"\n"<<"\n"<<"\n";                              
          out2.close();
        }     
    out3.open("/home/hou/data/rgbddata/getImage2.txt",ios::app);
        if (out3.is_open())
        { 
          out3 <<getImage2<<"\n"<<"\n"<<"\n"<<"\n";                              
          out3.close();
        } 


  }
  
}



int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "save_depth");

  ros::NodeHandle nh;
  cv::namedWindow("Show DepthImage");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);

// roslaunch freenect_launch freenect-registered-xyzrgb.launch
image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/image", 1000, imageCallBack);

// roslaunch openni_launch openni.launch
// image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/sw_registered/image_rect_raw", 1000, imageCallBack);





  ros::spin();
  
  cv::destroyWindow("Show DepthImage");

  //ROS_INFO("Hello world!");
}
