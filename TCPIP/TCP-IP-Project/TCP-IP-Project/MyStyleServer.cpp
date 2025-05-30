#include "Acceptor.hpp"
#include "ClientSocket.hpp"
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <hiocp.hpp>
#pragma comment(lib, "ws2_32.lib")

int main() {

	hiocp::NetSystem netinIt;
	//WSADATA wsaData;
	//if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	//	std::cout << "WSAStartup 실패" << std::endl;
	//	return 1;
	//}

	// Socket
	Acceptor listenSoc(12345);
	listenSoc.listen_clients();
	ClientSocket sock = listenSoc.accept_clients();
	if (sock.get_sock() != INVALID_SOCKET)
		std::cout << "클라이언트 연결완료" << std::endl;

	while (true)
	{
		sock.Read();
	}


	return 0;
}



