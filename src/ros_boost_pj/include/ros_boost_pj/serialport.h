#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H
#include<iostream>
#include<ros/ros.h>
#include <serial/serial.h>
#include<string>
#include"string.h"
#include<thread>
#include<memory>
#include<vector>



//static serial::Serial sp;



class SerialPort
{
public:
    SerialPort();
    ~SerialPort();
    bool init(std::string port_name,int baud_rate);
    void runService();
    void close();
 

    //void handleRead(const boost::system::error_code& ec, size_t byte_read);
    bool open();

    void SendByte(uint8_t date[]);
    void Send(uint8_t data[],size_t data_size); 
    void Send_Cmd_Data(uint8_t cmd, const uint8_t* datas, uint8_t len);
   //void Send_timly(int times);
    uint16_t CRC16_Check(const uint8_t* data, uint8_t len);

    std::vector<int> save_data(uint8_t* data,int length);
    std::vector<int> got_data();
    void save_data();
    int got_length();
    void startAsyncRead();
    void Data_Analysis(uint8_t cmd,uint8_t* datas, uint8_t len);
    void Receive(uint8_t bytedata);
    int got_baudRate();
    void justice();

private:
    
    //io_service io;
    serial::Serial sp;
    std::string portName;
    int baudRate;
    uint8_t*result_data;
    std::vector<int> result_vec;
    //uint8_t data_pre[];
    int data_length;
    //uint8_t data_now[];
    //static uint8_t receiveData[1024];
};


// void Serial_Init(std::string port_name,int port_rate);
// void sendByte(uint8_t data[]);
// void send(uint8_t data[],size_t data_size);
// void justice();


#endif 