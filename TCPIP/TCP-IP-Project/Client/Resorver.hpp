#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

class Resorver {
private:
	SOCKET soc;
	sockaddr_in servAddr;
public:
	Resorver(short PORT, std::string IP)
	{
		servAddr = {};
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		inet_pton(AF_INET, IP.c_str(), &servAddr.sin_addr);
		servAddr.sin_port = htons(PORT);

		soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (soc == INVALID_SOCKET) {
			std::cout << "SOCKET 积己 角菩!" << std::endl;
			throw std::runtime_error("socket create failed");
			return;
		}
	}


	SOCKET connect_server() {
		int result = connect(soc, (sockaddr*)&servAddr, sizeof(servAddr));
		if (result == SOCKET_ERROR) {
			std::cout << "立加 角菩!" << std::endl;
			return INVALID_SOCKET;
		}
		else {
			return soc;
		}
	}

	~Resorver()
	{
		closesocket(soc);
		if (soc != INVALID_SOCKET)
			soc = INVALID_SOCKET;
	}

	SOCKET get_soc() { return soc; }

private:
	Resorver(const Resorver&) = delete;
	Resorver& operator=(const Resorver&) = delete;

	Resorver(Resorver&& other) noexcept : soc(other.soc) {
		other.soc = INVALID_SOCKET;
	}

	Resorver& operator=(Resorver&& other) noexcept {
		if (this != &other) {
			closesocket(soc);
			soc = other.soc;
			other.soc = INVALID_SOCKET;
		}
		return *this;
	}
};