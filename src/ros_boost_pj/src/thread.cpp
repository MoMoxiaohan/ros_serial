// #include"../include/ros_boost_pj/serialport.h"
// #include<std_srvs/Empty.h>
// #include<std_srvs/SetBool.h>

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "serial_port_thread_pub");
//     ros::NodeHandle nh;

//     string port_name="/dev/pts/7";
//     int port_rate=115200;

//     Serial_Init(port_name,port_rate);
//     uint8_t datas[] = { 0x11,0x15 };
//     justice();
//     ros::Rate loop_rate(10);

//     while(ros::ok())
//     {
//         send(datas,2);
        
//         if(datas!=nullptr)
//         {
//             ROS_INFO_STREAM("DATA SEND SUCCESSFULLY!");
//         }
//         else
//         {
//             ROS_WARN_STREAM("NO DATA SEND");
//         }

//     }
//     sp.close();


// }
#include<iostream>
#include"ros/ros.h"
int main(int argc,char** argv)
{
    ros::init(argc,argv,"testnode05");
    return 0;
}