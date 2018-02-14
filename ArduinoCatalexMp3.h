
#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h> 
//////////////////////////////////////////////////////////////////////////////////// 
//all the commands needed in the datasheet(http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf) 
static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string 
                                //0X7E FF 06 command 00 00 00 EF;(if command =01 next song order)  
#define NEXT_SONG 0X01  
#define PREV_SONG 0X02  
#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song) 
#define VOLUME_UP_ONE 0X04 
#define VOLUME_DOWN_ONE 0X05 
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E)) 
#define SET_DAC 0X17 
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song) 
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED 
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED 
#define SLEEP_MODE_START 0X0A 
#define SLEEP_MODE_WAKEUP 0X0B 
#define CMD_RESET 0X0C//CHIP RESET 
#define CMD_PLAY 0X0D //RESUME PLAYBACK 
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED 
#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3 
#define STOP_PLAY 0X16 
#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care) 
#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close 
#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output 
//////////////////////////////////////////////////////////////////////////////////// 


#define ARDUINO_RX 5//should connect to TX of the Serial MP3 Player module 
#define ARDUINO_TX 6//connect to RX of the module 
class ArduinoCatalexMp3
{
public:

	ArduinoCatalexMp3(int16_t RXPort, int16_t TXPort);
	void sendCommand(int8_t command, int16_t dat);
	void playTrack(int8_t dat);
	void playTrack(int8_t songIndex, int8_t folderIndex);
private:
	SoftwareSerial* mySerial;//init the serial protocol, tell to myserial wich pins are TX and RX 
};