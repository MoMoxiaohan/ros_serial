#include<iostream>
#include"ros/ros.h"
#include"../include/ros_boost_pj/serialport.h"
#include<thread>
#include<chrono>

static SerialPort port;
void callback1(const ros::TimerEvent &event)
{
    uint8_t array[8];
    int a=123,b=456;
    memcpy(array,&a,4);
    memcpy(array+4,&b,4);
    port.Send_Cmd_Data(0,array,8);
}
int main(int argc,char** argv)
{
    ros::init(argc,argv,"testnode02");
    ros::NodeHandle nh;
    port.init("/dev/pts/5",115200);
    port.justice();
    ros::Timer timer=nh.createTimer(ros::Duration(0.02),callback1);
    ros::spin();
    port.close();
    return 0;
}