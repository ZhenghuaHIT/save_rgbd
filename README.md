# How to record a dataset.
**Authors**: Zhenghua.Hou HIT 16S108281

**2017.11.9**: Finish recording a dataset by subscribing to a Kinect published in ROS.

# 1. License
Only Myself and My junior of laboratory.

# 2. Prerequisites
## C++11 or C++0x Compiler
I use the new thread and chrono functionalities of C++11. 
## OpenCV
I use [OpenCV](http://opencv.org).
## ROS
I use [ROS](http://www.ros.org/).
## Kinect Driver
**Kinect v2**  
Kinect v2 only supports **USB 3.0** and **OpenCV 2**  
I use [iai-kinect2](https://github.com/code-iai/iai_kinect2).  
I use [libfreenect2](https://github.com/OpenKinect/libfreenect2).    

**Kinect v1**  
I use openni_launch
```
sudo apt-get install ros-kinetic-openni-camera ros-kinetic-openni-launch
```
I use freenect_launch
```
sudo apt-get install ros-kinetic-freenect-camera ros-kinetic-freenect-stack ros-kinetic-freenect-launch
```
# 3. Building
## Prepare Workspace 
```
source /opt/ros/indigo/setup.bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ~/catkin_ws/
catkin_make
source devel/setup.bash 
```
## Get save_rgbd
```
cd ~/catkin_ws/src
git clone https://github.com/ZhenghuaHIT/save_rgbd.git
cd ~/catkin_ws/
```
## Install
```
rosdep update
catkin_make
```
# 4. Usage
1. Modify save path.
The default save path is:
```
/home/hou/data/rgbddata
```
2. Kinect different drivers, need to modify different nodes in **save_depth.cpp**.
```
roslaunch freenect_launch freenect-registered-xyzrgb.launch
image_transport::Subscriber sub = it.subscribe("camera/depth_registered/image", 1000, imageCallBack);
```
```
**roslaunch openni_launch openni.launch
image_transport::Subscriber sub = it.subscribe("/camera/depth_registered/sw_registered/image_rect", 1000, imageCallBack);
```
3. Create the **/depth** and **/rgb** folders under the save file directory **rgbddata**  
```
cd /home/hou/data/rgbddata
mkdir rgb
cd ..
mkdir depth
```
4. Star **ROS**
```
roscore
```
5. Turn on the camera driver.
```
roslaunch freenect_launch freenect-registered-xyzrgb.launch
```
6. Start recording pictures.
```
cd catkin_ws/src/save_rgbd/launch/
roslaunch record.launch
```
