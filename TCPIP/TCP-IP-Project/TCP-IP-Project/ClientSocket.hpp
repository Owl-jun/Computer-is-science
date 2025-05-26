#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

class ClientSocket {
private:
	SOCKET soc;
	char buffer[1024];
	std::string recvBuffer;
public:

	void Read() {
		int recvLen = recv(soc, buffer, 1024, 0);
		if (recvLen > 0) {
			recvBuffer.append(buffer, recvLen);

			size_t pos;
			while ((pos = recvBuffer.find('\n')) != std::string::npos) {
				std::string line = recvBuffer.substr(0, pos + 1);  
				recvBuffer.erase(0, pos + 1);     
				Send_Until(line);
				break;
			}
		}
	}

	void Send_Until(std::string msg, const char target = '\n') {
		size_t pos = msg.find(target);
		if (pos == std::string::npos) {
			std::cerr << "target string not found!\n";
			return;
		}

		const char* data = msg.data();
		int len = static_cast<int>(pos+1);

		int sent = 0;
		while (sent <= len) {
			int chunk = send(soc, data + sent, len - sent, 0);
			if (chunk <= 0) {
				break;
			}
			sent += chunk;
		}
	}

	SOCKET get_sock() {
		return soc;
	}

	ClientSocket(const ClientSocket&) = delete;
	ClientSocket& operator=(const ClientSocket&) = delete;
	ClientSocket(ClientSocket&& other) noexcept : soc(other.soc) {
		other.soc = INVALID_SOCKET;
	}
	ClientSocket& operator=(ClientSocket&& other) noexcept {
		if (this != &other) {
			closesocket(soc);
			soc = other.soc;
			other.soc = INVALID_SOCKET;
		}
		return *this;
	}

	ClientSocket(SOCKET _soc)
		: soc(_soc)
	{
	}

	~ClientSocket() {
		if (soc != INVALID_SOCKET)
			closesocket(soc);
	}

};