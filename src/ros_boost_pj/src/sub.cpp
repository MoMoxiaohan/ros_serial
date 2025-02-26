// #include<ros/ros.h>
// #include <serial/serial.h>
// #include <iostream>
// #include<string>
// using namespace std;

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "serial_port_sub");
//     std::string portname="/dev/pts/9";
//     //创建句柄（虽然后面没用到这个句柄，但如果不创建，运行时进程会出错）
//     ros::NodeHandle nh;
    
//     //创建一个serial类
//     serial::Serial sp;
//     //创建timeout
//     serial::Timeout to = serial::Timeout::simpleTimeout(100);
//     //设置要打开的串口名称
//     sp.setPort(portname);
//     //设置串口通信的波特率
//     sp.setBaudrate(9600);
//     //串口设置timeout
//     sp.setTimeout(to);
 
//     try
//     {
//         //打开串口
//         sp.open();
//     }
//     catch(serial::IOException& e)
//     {
//         ROS_ERROR_STREAM("Unable to open port.");
//         return -1;
//     }
    
//     //判断串口是否打开成功
//     if(sp.isOpen())
//     {
//         ROS_INFO_STREAM(portname+"is opened.");
//     }
//     else
//     {
//         return -1;
//     }
    
//     ros::Rate loop_rate(10);
//     while(ros::ok())
//     {
//         //获取缓冲区内的字节数
//         size_t n = sp.available();
//         if(n!=0)
//         {
//             uint8_t buffer[1024];
//             //读出数据
//             n = sp.read(buffer, n);
            
//             for(int i=0; i<n; i++)
//             {
//                 //16进制的方式打印到屏幕
//                 std::cout << std::hex << (buffer[i] & 0xff) << " "<<std::endl;
//             }
//             //std::cout << std::endl;
//             //把数据发送回去
//             //sp.write(buffer, n);
            
//         }
//         loop_rate.sleep();
//     }
    
//     //关闭串口
//     sp.close();
 
//     return 0;
// }
#include<iostream>
#include"ros/ros.h"
int main(int argc,char** argv)
{
    ros::init(argc,argv,"testnode04");
    return 0;
}