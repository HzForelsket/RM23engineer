#pragma once
#include <cstdint>
class CRC_CHECK
{
	//crc8 generator polynomial:G(x)=x8+x5+x4+1 
	static const unsigned char CRC8_INIT = 0xff;
	static const unsigned char CRC8_TAB[256];
	static const uint16_t CRC_INIT;
	static const uint16_t wCRC_Table[256];
public:
	static unsigned char Get_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength, unsigned char ucCRC8);
	/*
	** Descriptions: CRC8 Verify function
	** Input: Data to Verify,Stream length = Data + checksum
	** Output: True or False (CRC Verify Result)
	*/
	static unsigned int Verify_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength);
	/*
	** Descriptions: append CRC8 to the end of data
	** Input: Data to CRC and append,Stream length = Data + checksum
	** Output: True or False (CRC Verify Result)
	*/
	static void Append_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength);
	
	/*
	** Descriptions: CRC16 checksum function
	** Input: Data to check,Stream length, initialized checksum
	** Output: CRC checksum
	*/
	static uint16_t Get_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength, uint16_t wCRC);
	/*
	** Descriptions: CRC16 Verify function
	** Input: Data to Verify,Stream length = Data + checksum
	** Output: True or False (CRC Verify Result)
	*/
	static uint32_t Verify_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength);
	/*
	** Descriptions: append CRC16 to the end of data
	** Input: Data to CRC and append,Stream length = Data + checksum
	** Output: True or False (CRC Verify Result)
	*/
	static void Append_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength);
};

