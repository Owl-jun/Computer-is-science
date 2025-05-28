#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define BUF_SIZE 512

struct IOContext {
	IOContext(HANDLE& event, SOCKET sock)
	{
		overlapped.hEvent = event;
		wsaBuf = { sizeof(buffer),buffer };
		Socket = sock;
	}
	OVERLAPPED overlapped = {};
	char buffer[BUF_SIZE] = {};
	WSABUF wsaBuf;
	SOCKET Socket;
	DWORD byte = 0;
	DWORD flag = 0;
};

int main() {

	// start
	//////////////////////////////////////////
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) == -1) {
		cout << "WSAStartup Failed!" << endl;
	}

	sockaddr_in myAddr;
	memset(&myAddr, 0, sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(12345);
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// accept
	//////////////////////////////////////////
	SOCKET acceptor = socket(AF_INET, SOCK_STREAM, 0);
	if (acceptor == -1) {
		cout << "socket() Failed" << endl;
	}
	if (bind(acceptor, (sockaddr*)&myAddr, sizeof(myAddr)) == -1)
	{
		cout << "bind Error" << endl;
	}
	listen(acceptor, SOMAXCONN);
	SOCKET c_sock = accept(acceptor, NULL, NULL);
	if (c_sock == -1) {
		cout << "accept Error" << endl;
	}

	// logic
	//////////////////////////////////////////
	HANDLE hrEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hsEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	IOContext recvCtx(hrEvent, c_sock);
	IOContext sendCtx(hsEvent, c_sock);
	
	while (1)
	{
		int result = WSARecv(recvCtx.Socket, &recvCtx.wsaBuf, 1, &recvCtx.byte, &recvCtx.flag, &recvCtx.overlapped, NULL);
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSA_IO_PENDING)
			{
				printf("비동기 수신 대기 중 ..\n");
				WaitForSingleObject(recvCtx.overlapped.hEvent, INFINITE);

				WSAGetOverlappedResult(recvCtx.Socket, &recvCtx.overlapped, &recvCtx.byte, FALSE, &recvCtx.flag);
				memcpy(sendCtx.buffer, recvCtx.buffer, strlen(recvCtx.buffer));
				sendCtx.wsaBuf.len = recvCtx.byte;
				WSASend(sendCtx.Socket, &sendCtx.wsaBuf, 1, NULL, 0, &sendCtx.overlapped, NULL);
				WaitForSingleObject(sendCtx.overlapped.hEvent, INFINITE);
			}
		}
		ResetEvent(recvCtx.overlapped.hEvent);
		ResetEvent(sendCtx.overlapped.hEvent);
		ZeroMemory(&recvCtx.overlapped, sizeof(recvCtx.overlapped));
		recvCtx.overlapped.hEvent = hrEvent;
		ZeroMemory(&sendCtx.overlapped, sizeof(sendCtx.overlapped));
		sendCtx.overlapped.hEvent = hsEvent;

	}
	return 0;
}