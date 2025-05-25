// Ŭ���̾�Ʈ (Connect)

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h> // inet_pton
#pragma comment(lib, "ws2_32.lib")

int main() {

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartup ����" << std::endl;
		return 1;
	}

	SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in servAddr = {};
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

	// bind ����

	int result = connect(soc, (sockaddr*)&servAddr, sizeof(servAddr)); // ���⼭ soc �� ���� bind ��
	if (result == SOCKET_ERROR) {
		std::cout << "���� ���� ����" << std::endl;
	}
	std::cout << "���� ���� �Ϸ�!" << std::endl;

}