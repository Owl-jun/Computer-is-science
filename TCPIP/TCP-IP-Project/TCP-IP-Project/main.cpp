// ���� (Accept)

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h> // inet_pton
#pragma comment(lib, "ws2_32.lib")  // ��ũ ���� ���� �� ��

int main() {

    WSADATA wsaData; // WSA ����ü �ʱ�ȭ �� ���� ��� Ȱ��ȭ
    // ���� ���̺귯�� �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {    // Version 2.2 , �ν��Ͻ� �Ҵ�
        std::cout << "WSAStartup ����" << std::endl;
        return 1;
    }

    // �ּ����� ����ü sockaddr , ���⿡ �����ͻ����� ���� sockaddr_in
    sockaddr_in servAddr = {};
    servAddr.sin_family = AF_INET;                      // AF_INET : IPv4
    servAddr.sin_port = htons(12345);                   // ��Ʈ    , htons = short , htonl = long : ��Ʋ�ص�� -> ��ص��
    inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr); // IP , ���ڿ� -> ���̳ʸ�


    // socket ����
    SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET : IPv4 , SOCK_STREAM : ���Ἲ | SOCK_DGRAM : �񿬰Ἲ , IPPROTO_TCP : TCP ��������
    if (soc == INVALID_SOCKET) {
        std::cout << "socket ���� ����" << std::endl;
        WSACleanup();
        return 1;
    }
    std::cout << "���� ���� ����!" << std::endl;

    bind(soc, (sockaddr*)&servAddr, sizeof(servAddr));  // ���Ͽ� IP:PORT�� �Ҵ� (�ּ� ���� ���), �� ��° ���ڴ� ����ü ũ��
    listen(soc, SOMAXCONN);                             // backlog = accept() ȣ�� ������ Ŀ���� �޾Ƴ��� �� �ִ� ���� ��û ��


    sockaddr_in clientAddr = {};                        // �� ���� �ּ����� ����ü
    int clientAddrSize = sizeof(clientAddr);
    SOCKET cliSock = accept(soc, (sockaddr*)&clientAddr, &clientAddrSize);   // soc ���� Ŭ���û ���� �������� clientAddr�� ���� �������ְڴ�.
    std::cout << "Ŭ���̾�Ʈ ����!" << std::endl;


    // 3. ������
    closesocket(soc);
    WSACleanup();
    return 0;
}
