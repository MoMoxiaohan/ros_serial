#include<iostream>
#include"ros/ros.h"
#include"../include/ros_boost_pj/serialport.h"
int main(int argc,char** argv)
{
    ros::init(argc,argv,"testnode03");
    SerialPort port;
    port.init("/dev/pts/6",115200);
    port.runService();
    port.close();
    return 0;
}