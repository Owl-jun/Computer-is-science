// 클라이언트 (Connect)

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h> // inet_pton
#pragma comment(lib, "ws2_32.lib")

int main() {

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartup 실패" << std::endl;
		return 1;
	}

	SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in servAddr = {};
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

	// bind 생략

	int result = connect(soc, (sockaddr*)&servAddr, sizeof(servAddr)); // 여기서 soc 에 정보 bind 됨
	if (result == SOCKET_ERROR) {
		std::cout << "서버 접속 실패" << std::endl;
	}
	std::cout << "서버 접속 완료!" << std::endl;

}