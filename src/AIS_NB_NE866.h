#ifndef AIS_NB_NE866_h
#define AIS_NB_NE866_h

#include <Arduino.h>
#include <Stream.h>
#include <Wire.h>

#define MODE_STRING 		0x00
#define MODE_STRING_HEX 	0x01

struct AIS_NB_NE866_RES{
	unsigned char status;
	String data;
	String temp;
};

struct signal{
	String csq;
	String rssi;
	String ber;
};

struct UDPSend{
	bool status;
	String strsend;
	unsigned char socket;
	unsigned int length;
};

struct UDPReceive{
	unsigned char socket;
	String ip_address;
	unsigned int port;
	unsigned int length;
	String data;
	unsigned int remaining_length;
};
struct pingRESP{
	bool status;
	String addr;
	String ttl;
	String rtt;
};
class AIS_NB_NE866{
public:
	AIS_NB_NE866();
	//bool debug = true;
	bool debug;
	unsigned char send_mode = MODE_STRING;

	void (*Event_debug)(char *data);
	void setEchoOff();
	void reset();
	void rebootModule();
	bool waitReady();
	bool setPhoneFunction(unsigned char mode);

	//General
	String getFirmwareVersion();
	String getIMEI();
    String getIMSI();
	pingRESP pingIP(String IP);

	//Network
	bool setAutoConnectOn();
	bool setAutoConnectOff();
	String getAutoConnect();
	String getNetworkStatus();
    //bool setAPN(String apn);
	String getAPN();


	bool sgact(unsigned char mode);
	bool getNBConnect();
	
	void setupDevice(Stream* serial, String serverPort, String addressI);
	bool attachNB();
	bool detachNB();

	String getDeviceIP();
	signal getSignal();
	signal getSignal(int state);

	void createUDPSocket();

    UDPSend sendUDPmsg(String data);
	UDPSend sendUDPmsg(unsigned int len,char *data);
	
	bool closeUDPSocket();

	void clearBuffer();
	UDPReceive waitResponse();

	void printHEX(char *str);
	String str2HexStr(String strin);
	char char_to_byte(char c);
	
	void receive_UDP(UDPReceive rx);

private:
	AIS_NB_NE866_RES wait_rx_bc(long tout,String str_wait);
	String serverIP;
	String serverPort;
	bool socketCreated = false;

protected:
	Stream *_Serial;	
};

#endif