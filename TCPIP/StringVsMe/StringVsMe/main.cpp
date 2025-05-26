#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void Delimiter_stringStyle(SOCKET& sock);
void Delimiter_CStyle(SOCKET& sock);

int main() {

	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == -1)
	{
		cout << "WSA 초기화 실패 , 종료합니다." << endl;
		return 1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "소켓 생성 실패\n";
		return 1;
	}

	sockaddr_in info;
	memset(&info, 0, sizeof(info));
	info.sin_family = AF_INET;
	info.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &info.sin_addr);

	connect(sock, (sockaddr*)&info, sizeof(info));

	// Packet Parsing ----

	// 1-1. delimiter string Style
	//Delimiter_stringStyle(sock);

	// 1-2. delimiter C Style
	Delimiter_CStyle(sock);

	// 2-1. type + length + payload string Style
	tlPayload_stringStyle(sock);	
	
	// 2-2. type + length + payload C Style
	tlPayload_CStyle(sock);


	return 0;
}

void Delimiter_stringStyle(SOCKET& sock) {
	char buf[1024];
	string sendBuf, recvBuf;
	int recvCnt;
	while (true)
	{
		getline(cin, sendBuf);
		sendBuf += '\n';
		send(sock, sendBuf.c_str(), sendBuf.size(), 0);

		recvCnt = recv(sock, buf, 1024, 0);
		if (recvCnt == 0) {
			cout << "서버 종료됨\n";
			break;
		}
		if (recvCnt < 0) {
			cout << "recv 에러\n";
			break;
		}
		if (recvCnt > 0) {
			recvBuf.append(buf, recvCnt);
			size_t pos;
			while ((pos = recvBuf.find('\n')) != string::npos) {
				string line = recvBuf.substr(0, pos + 1);
				recvBuf.erase(0, pos + 1);
				cout << "> " << line;
			}
		}
	}
}

void Delimiter_CStyle(SOCKET& sock) {
	char buf[1024];
	char sendBuf[1024];
	char recvBuf[2048] = { 0 };
	int recvLenTotal = 0;

	while (1) {
		fgets(sendBuf, sizeof(sendBuf), stdin);
		send(sock, sendBuf, strlen(sendBuf), 0);

		int len = recv(sock, buf, sizeof(buf), 0);
		if (len == 0) {
			printf("서버 종료됨\n");
			break;
		}
		if (len < 0) {
			printf("recv 에러\n");
			break;
		}

		memcpy(recvBuf + recvLenTotal, buf, len);
		recvLenTotal += len;

		int lineStart = 0;
		for (int i = 0; i < recvLenTotal; ++i) {
			if (recvBuf[i] == '\n') {
				int lineLen = i - lineStart + 1;
				char line[1024] = { 0 };
				memcpy(line, recvBuf + lineStart, lineLen);
				line[lineLen] = '\0';

				printf("> %s", line);
				lineStart = i + 1;
			}
		}

		if (lineStart < recvLenTotal) {
			memmove(recvBuf, recvBuf + lineStart, recvLenTotal - lineStart);
			recvLenTotal -= lineStart;
		}
		else {
			recvLenTotal = 0;
		}
	}
}

void tlPayload_stringStyle(SOCKET sock) {



}

void tlPayload_CStyle(SOCKET sock) {



}