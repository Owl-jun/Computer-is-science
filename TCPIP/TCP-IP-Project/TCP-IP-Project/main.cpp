// 서버 (Accept)

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h> // inet_pton
#pragma comment(lib, "ws2_32.lib")  // 링크 설정 잊지 말 것

int main() {

    WSADATA wsaData; // WSA 구조체 초기화 및 소켓 기능 활성화
    // 소켓 라이브러리 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {    // Version 2.2 , 인스턴스 할당
        std::cout << "WSAStartup 실패" << std::endl;
        return 1;
    }

    // 주소정보 구조체 sockaddr , 여기에 데이터삽입을 위한 sockaddr_in
    sockaddr_in servAddr = {};
    servAddr.sin_family = AF_INET;                      // AF_INET : IPv4
    servAddr.sin_port = htons(12345);                   // 포트    , htons = short , htonl = long : 리틀앤디안 -> 빅앤디안
    inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr); // IP , 문자열 -> 바이너리


    // socket 생성
    SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET : IPv4 , SOCK_STREAM : 연결성 | SOCK_DGRAM : 비연결성 , IPPROTO_TCP : TCP 프로토콜
    if (soc == INVALID_SOCKET) {
        std::cout << "socket 생성 실패" << std::endl;
        WSACleanup();
        return 1;
    }
    std::cout << "소켓 생성 성공!" << std::endl;

    bind(soc, (sockaddr*)&servAddr, sizeof(servAddr));  // 소켓에 IP:PORT를 할당 (주소 정보 등록), 세 번째 인자는 구조체 크기
    listen(soc, SOMAXCONN);                             // backlog = accept() 호출 전까지 커널이 받아놓을 수 있는 연결 요청 수


    sockaddr_in clientAddr = {};                        // 빈 소켓 주소정보 구조체
    int clientAddrSize = sizeof(clientAddr);
    SOCKET cliSock = accept(soc, (sockaddr*)&clientAddr, &clientAddrSize);   // soc 으로 클라요청 오면 소켓정보 clientAddr에 만들어서 생성해주겠다.
    std::cout << "클라이언트 연결!" << std::endl;


    // 3. 마무리
    closesocket(soc);
    WSACleanup();
    return 0;
}
