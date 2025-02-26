#include "../include/ros_boost_pj/serialport.h"
// #include"../include/ros_boost_pj/Task_Data_pack.h"
//#include <iomanip>//测试使用



//shared_ptr<serial::Serial> SerialPort::sp = nullptr;
//uint8_t SerialPort::receiveData[] = { 0 };
SerialPort::SerialPort() :
    portName("COM1"),
    baudRate(115200)
    {

    }

SerialPort::~SerialPort()
{

    sp.close();
}

bool SerialPort::init(string port_name, int baud_rate)
{
    this->portName = port_name;
    this->baudRate = baud_rate;

    return open();
}

void SerialPort::runService()
{
    startAsyncRead();
   
}

bool SerialPort::open()
{
    serial::Timeout to = serial::Timeout::simpleTimeout(100);//创建timeout
	serial::parity_t pt = serial::parity_t::parity_none;//创建校验位为0位
	serial::bytesize_t bt = serial::bytesize_t::eightbits;//创建发送字节数为8位
	serial::flowcontrol_t ft = serial::flowcontrol_t::flowcontrol_none;//创建数据流控制，不使用
	serial::stopbits_t st = serial::stopbits_t::stopbits_one;//创建终止位为1位
    
    sp.setPort(SerialPort::portName);//设置要打开的串口名称
    sp.setBaudrate(SerialPort::baudRate);//设置串口通信的波特率
    sp.setParity(pt);//设置校验位
    sp.setFlowcontrol(ft);//设置数据流控制
    sp.setStopbits(st);//设置终止位
    sp.setTimeout(to);//串口设置timeout
    try
    {
        //打开串口
        sp.open();
        return true;
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return false; 
    }
    
}

void SerialPort::startAsyncRead()
{
    //memset(receiveData, 0, sizeof(receiveData));
    // sp->async_read_some(boost::asio::buffer(receiveData),
    //     boost::bind(&SerialPort::handleRead, this,
    //         boost::asio::placeholders::error,
    //         boost::asio::placeholders::bytes_transferred));
    while(true)
    {
		
        if(sp.available())
        {
            size_t bytes_available=sp.available();
            if( bytes_available!=0)
            {
                uint8_t data[100000];
                bytes_available=sp.read(data,bytes_available);
                //std::cout<<bytes_available<<std::endl;
                for(int i=0; i<bytes_available; i++)
                {
                    Receive(data[i]);
                }
            }
            

        }
    }
}

void SerialPort::close()
{
    sp.close();
}

void SerialPort::SendByte(uint8_t date[])
{
	sp.write(date,1);
}
void SerialPort::Send(uint8_t data[],size_t data_size)
{
    uint8_t i;
    for(i=0;i<data_size;i++)
    {
        SendByte(&data[i]);

    }
}
void SerialPort::Send_Cmd_Data(uint8_t cmd, const uint8_t* datas, uint8_t len)
{

	uint8_t buf[300], i, cnt = 0;
	uint16_t crc16;
	buf[cnt++] = 0xA5;
	buf[cnt++] = 0x5A;
	buf[cnt++] = len;
	buf[cnt++] = cmd;
	for (i = 0; i < len; i++)
	{
		buf[cnt++] = datas[i];
	}
	crc16 = CRC16_Check(buf, len + 4);
	buf[cnt++] = crc16 >> 8;
	buf[cnt++] = crc16 & 0xFF;
	buf[cnt++] = 0xFF;
	Send(buf, cnt); 





}
uint16_t SerialPort::CRC16_Check(const uint8_t* data, uint8_t len)
{
	uint16_t CRC16 = 0xFFFF;
	uint8_t state, i, j;
	for (i = 0; i < len; i++)
	{
		CRC16 ^= data[i];
		for (j = 0; j < 8; j++)
		{
			state = CRC16 & 0x01;
			CRC16 >>= 1;
			if (state)
			{
				CRC16 ^= 0xA001;
			}
		}  
	}
	return CRC16;
}
void SerialPort::Data_Analysis(uint8_t cmd,uint8_t* datas, uint8_t len)
{
	
	//uint8_t*data_now;
	switch (cmd)
	{
	case 0x00:
		// for(int i=0;i<(len/4);i++)
        // {
        //     memcpy(&data_now[i],&datas[i],4);
        // }
		//this->result_data=datas;
        for(int i=0;i<(len/4);i++)
        {
			int a;
			memcpy(&a,datas+4*i,4);
            std::cout<<a<<" ";
			//datas++;
        }
        std::cout<<std::endl;
		break;
	default:
		std::cerr << "Unknown command: " << cmd << std::endl;

		break;
	}

}

void SerialPort::Receive(uint8_t bytedata)
{
	
	static uint8_t step = 0; 
	static uint8_t cnt = 0, Buf[300], len, cmd, * data_ptr;
	static uint16_t   crc16;
   

	switch (step)
	{
	case 0: 
		if (bytedata == 0xA5)
		{
			step++;
			cnt = 0;
			Buf[cnt++] = bytedata;
		}
		break;
	case 1: 
		if (bytedata == 0x5A)
		{
			step++;
			Buf[cnt++] = bytedata;
		}
		else if (bytedata == 0xA5)
		{
			step = 1;
		}
		else
		{
			step = 0;
		}
		break;
	case 2: 
		step++;
		Buf[cnt++] = bytedata;
		len = bytedata;
		break;
	case 3: 
		step++;
		Buf[cnt++] = bytedata;
		cmd = bytedata;
		data_ptr = &Buf[cnt]; 
		if (len == 0)
			step++; 
		break;
	case 4: 
		Buf[cnt++] = bytedata;
		if (data_ptr + len == &Buf[cnt]) 
		{
			step++;
		}
		break;
	case 5: 
		step++;
		crc16 = bytedata;
		break;
	case 6: 
		crc16 <<= 8;
		crc16 += bytedata;
		if (crc16 == CRC16_Check(Buf, cnt)) 
		{
			step++;
		}
		else if (bytedata == 0xA5)
		{
			step = 1;
		}
		else
		{
			step = 0;
		}
		break;
	case 7:			     
		if (bytedata == 0xFF) 
		{
			//data=Data_Analysis(cmd, data_ptr);
            Data_Analysis(cmd,data_ptr,len);
			step = 0;
			
		}
		else if (bytedata == 0xA5)
		{
			step = 1;
		}
		else
		{
			step = 0;
		}
		break;
	default:
		step = 0;
		break; 
	}
}
void SerialPort::justice()
{
    if(sp.isOpen())
    {
        cout<<"port open successful!"<<endl;
    }
    else
    {
        cout<<"port gg"<<endl;
        return ;
    }

}
