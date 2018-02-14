#include <ArduinoCatalexMp3.h>
	ArduinoCatalexMp3::ArduinoCatalexMp3(int16_t RXPort, int16_t TXPort){
		mySerial = new SoftwareSerial(RXPort, TXPort);
			mySerial->begin(9600);//Start our Serial coms for our serial monitor! 
		delay(500);//Wait chip initialization is complete 
		  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card   
		delay(200);//wait for 200ms 
	}

	void ArduinoCatalexMp3::sendCommand(int8_t command, int16_t dat) 
	{ 
		delay(20); 
		Send_buf[0] = 0x7e; //starting byte 
		Send_buf[1] = 0xff; //version 
		Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte 
		Send_buf[3] = command; // 
		Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback 
		Send_buf[5] = (int8_t)(dat >> 8);//datah 
		Send_buf[6] = (int8_t)(dat); //datal 
		Send_buf[7] = 0xef; //ending byte 
		for(uint8_t i=0; i<8; i++)// 
		{ 
		  mySerial->write(Send_buf[i]) ; 
		} 
	}

	void ArduinoCatalexMp3::playTrack(int8_t dat)
	{
		this->sendCommand(CMD_PLAY_WITHVOLUME, 0xFF00 | dat);
	}

	void ArduinoCatalexMp3::playTrack(int8_t songIndex, int8_t folderIndex)
	{
		this->sendCommand(CMD_PLAY_WITHFOLDER, folderIndex << 8 | songIndex);
	}
