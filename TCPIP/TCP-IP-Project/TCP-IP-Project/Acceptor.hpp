#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

class Acceptor {
private:
	SOCKET soc;
public:
	Acceptor(short PORT, std::string IP = "ANY")
	{
		sockaddr_in servAddr = {};
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		if (IP == "ANY") { servAddr.sin_addr.s_addr = htonl(INADDR_ANY); }
		else { inet_pton(AF_INET, IP.c_str(), &servAddr.sin_addr); }
		servAddr.sin_port = htons(PORT);

		soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (soc == INVALID_SOCKET) {
			std::cout << "SOCKET 생성 실패!" << std::endl;
			throw std::runtime_error("socket create failed");
			return;
		}

		if (bind(soc, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
			std::cerr << "bind 실패 : " << WSAGetLastError() << "\n";
			throw std::runtime_error("bind failed");
		}
	}

	void listen_clients(int bl = 0) {
		if (bl == 0)
			listen(soc, SOMAXCONN);
		else
			listen(soc, bl);
	}

	SOCKET accept_clients() {
		sockaddr_in tempAddr = {};
		int size = sizeof(tempAddr);
		SOCKET sock = accept(soc, (sockaddr*)&tempAddr, &size);
		return sock;
	}

	~Acceptor()
	{
		closesocket(soc);
		if (soc != INVALID_SOCKET)
			soc = INVALID_SOCKET;
	}

	SOCKET get_soc() { return soc; }

private:
	Acceptor(const Acceptor&) = delete;
	Acceptor& operator=(const Acceptor&) = delete;

	Acceptor(Acceptor&& other) noexcept : soc(other.soc) {
		other.soc = INVALID_SOCKET;
	}
	Acceptor& operator=(Acceptor&& other) noexcept {
		if (this != &other) {
			closesocket(soc);
			soc = other.soc;
			other.soc = INVALID_SOCKET;
		}
		return *this;
	}
};