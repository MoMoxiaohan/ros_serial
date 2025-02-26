#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H
#include<iostream>
#include<iostream>
#include<ros/ros.h>
#include <serial/serial.h>
#include<string>
#include"string.h"
#include<thread>
#include<memory>
using namespace std;


//static serial::Serial sp;



class SerialPort
{
public:
    SerialPort();
    ~SerialPort();
    bool init(string port_name,int baud_rate);
    void runService();
    void close();
 
    void startAsyncRead();
    //void handleRead(const boost::system::error_code& ec, size_t byte_read);
    bool open();

    void SendByte(uint8_t date[]);
    void Send(uint8_t data[],size_t data_size); 
    void Send_Cmd_Data(uint8_t cmd, const uint8_t* datas, uint8_t len);
   //void Send_timly(int times);
    uint16_t CRC16_Check(const uint8_t* data, uint8_t len);

    void Data_Analysis(uint8_t cmd,uint8_t* datas, uint8_t len);
    void Receive(uint8_t bytedata);
    void justice();

private:
    
    //io_service io;
    serial::Serial sp;
    string portName;
    int baudRate;
    uint8_t*result_data;
    //static uint8_t receiveData[1024];
};


// void Serial_Init(std::string port_name,int port_rate);
// void sendByte(uint8_t data[]);
// void send(uint8_t data[],size_t data_size);
// void justice();


#endif 