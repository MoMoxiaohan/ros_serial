#include<iostream>
#include"ros/ros.h"
#include"geometry_msgs/Twist.h"
#include"../include/ros_boost_pj/serialport.h"
#include<thread>
#include<chrono>
static uint8_t array1[12];
static SerialPort port;
void double2array(float a1,float a2,float a3,uint8_t*array)
{
    memcpy(array, &a1, sizeof(float));
    memcpy(array + sizeof(float), &a2, sizeof(float));
    memcpy(array + 2 * sizeof(float), &a3, sizeof(float));

}
void callback(const ros::TimerEvent &event)
{
    uint8_t array[8];
    int a=123,b=456;
    memcpy(array,&a,4);
    memcpy(array+4,&b,4);
    port.Send_Cmd_Data(0,array,8);
}
void callback_v(const geometry_msgs::Twist::ConstPtr &msg)
{
    double lx=msg->linear.x;
    double ly=msg->linear.y;
    double z=msg->angular.z;
    ROS_INFO("当前的速度是:x:%f y:%f w:%f",lx,ly,z );
    double2array(3*float(ly),3*float(lx),3*float(z),array1);
    port.Send_Cmd_Data(0,array1,12);
}
ros::Subscriber sub;
int main(int argc,char** argv)
{
    ros::init(argc,argv,"ros_serial");
    ros::NodeHandle nh;
    std::string port_name;
    int port_rate;
    int send_rate;
    
    nh.param<std::string>("port_name",port_name,"/dev/ttyUSB0");
    nh.param<int>("port_rate",port_rate,115200);
    nh.param<int>("send_rate",send_rate,1);
    ros::Rate rate(send_rate);
    port.init(port_name,port_rate);
    port.justice();
    sub=nh.subscribe("/smooth_cmd_vel",1000,callback_v);
    //ros::Timer timer=nh.createTimer(ros::Duration(send_rate),callback);
    //ros::spin();
    while(ros::ok())
    {
        rate.sleep();
        ros::spinOnce();
    }
    port.close();
    return 0;
}