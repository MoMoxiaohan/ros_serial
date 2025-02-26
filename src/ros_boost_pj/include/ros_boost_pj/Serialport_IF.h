#pragma once
#ifndef SERIALPORT_IF_H
#define SERIALPORT_IF_H
#include<iostream>

class SerialIF {
public:
virtual ~SerialIF() {}
virtual void write(uint8_t& data) = 0;
};
#endif
