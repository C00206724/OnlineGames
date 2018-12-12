#pragma once
#include <iostream>
#include <vector>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client();
	void sendMessage(std::string msg);
	void close();
	void receive();
	bool run();

	std::string ipAddress = "149.153.106.158";			// IP Address of the server
	int port = 54000;	
	SOCKET sock;
	sockaddr_in hint;
	std::string returnMessage;
	std::vector<float> positionVec;

	char buf[4096];
	int number = 0;
	bool join = false;
	bool collide = false;
};

