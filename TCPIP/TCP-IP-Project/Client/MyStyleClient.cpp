#include "Resorver.hpp"
#include "ClientSocket.hpp"
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main() {

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartup 실패" << std::endl;
		return 1;
	}

	Resorver r(12345, "127.0.0.1");
	ClientSocket sock = r.connect_server();
	if (sock.get_sock() != INVALID_SOCKET)
		std::cout << "서버 연결 완료" << std::endl;

	std::string msg;
	while (true)
	{
		std::cin >> msg;
		if (!strcmp(msg.c_str(), "q") || !strcmp(msg.c_str(), "Q")) { break; }
		sock.Send_Until(msg + '\n');
		sock.Read();
	}

	return 0;
}