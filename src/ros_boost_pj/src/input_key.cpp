// #include"../include/ros_boost_pj/serialport.h"
// #include"../include/ros_boost_pj/Task_Data_pack.h"
// #include"ros/ros.h"
// #include<iostream>
// #include<ros/console.h>
// #include<geometry_msgs/Twist.h>
// #include"std_msgs/UInt8.h"
// #include <termios.h>
// #include <unistd.h>
// #include<unistd.h>
// #include <thread>
// #include <atomic>
// #include <ncurses.h>
// int main(int argc, char** argv) {
//     setlocale(LC_ALL,"");
//     ros::init(argc, argv, "keyboard_control");
//     ros::NodeHandle nh;
//     ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

//     geometry_msgs::Twist twist;

//     // 初始化 ncurses
//     initscr();
//     cbreak();  // 禁用行缓冲
//     noecho();  // 禁止回显输入字符
//     timeout(100);  // 设置 getch() 为非阻塞模式，等待 100 ms
//     keypad(stdscr, TRUE);  // 启用特殊键（如方向键）

//     printw("使用键盘控制机器人移动：\n");
//     printw("w - 前进\ns - 后退\na - 左转\nd - 右转\n空格 - 停止\nq - 退出\n");

//     while (ros::ok()) {
//         int key = getch();  // 获取按键输入（非阻塞）

//         // 根据键盘输入设置运动速度
//         switch (key) {
//             case 'w':  // 前进
//                 twist.linear.x = 1.0;
//                 twist.angular.z = 0.0;
//                 break;
//             case 's':  // 后退
//                 twist.linear.x = -1.0;
//                 twist.angular.z = 0.0;
//                 break;
//             case 'a':  // 左转
//                 twist.linear.x = 0.0;
//                 twist.angular.z = 2.0;
//                 break;
//             case 'd':  // 右转
//                 twist.linear.x = 0.0;
//                 twist.angular.z = -2.0;
//                 break;
//             case ' ':  // 停止
//                 twist.linear.x = 0.0;
//                 twist.angular.z = 0.0;
//                 break;
//             case 'q':  // 退出程序
//                 endwin();  // 结束 ncurses 模式
//                 ros::shutdown();
//                 return 0;
//             default:
//                 continue;  // 忽略其他按键
//         }

//         pub.publish(twist);  // 发布消息
//         ros::spinOnce();
//     }

//     // 结束 ncurses 模式
//     endwin();
//     return 0;
// }
#include<iostream>
#include"ros/ros.h"
int main(int argc,char** argv)
{
    ros::init(argc,argv,"testnode01");
    return 0;
}