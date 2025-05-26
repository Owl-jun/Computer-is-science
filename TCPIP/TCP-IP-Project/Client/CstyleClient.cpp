// 클라이언트 (Connect)

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h> // inet_pton
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 1024
int main() {

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartup 실패" << std::endl;
		return 1;
	}

	char message[BUF_SIZE];
	int str_len;

	SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in servAddr = {};
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

	// bind 생략

	int result = connect(soc, (sockaddr*)&servAddr, sizeof(servAddr)); // 여기서 soc 에 정보 bind 됨
	if (result == SOCKET_ERROR) {
		std::cout << "서버 접속 실패" << std::endl;
	}
	std::cout << "서버 접속 완료!" << std::endl;

	while (true)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);
		if (!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
		{
			break;
		}

		str_len = send(soc, message, strlen(message), 0);
		
		int recv_len = 0;
		int recv_cnt;
		while (recv_len < str_len) {
			recv_cnt= recv(soc, message, BUF_SIZE - 1, 0);
			if (recv_cnt == -1) { break; }
			recv_len += recv_cnt;
		}
		message[str_len] = 0;
		printf("Message from server: %s", message);
	}
	closesocket(soc);
	WSACleanup();
	return 0;
}