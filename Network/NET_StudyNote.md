# 컴퓨터 네트워크 - 강의 정리

## 목차
### 1. 네트워크 기본 및 계층별 구조
- [네트워크 개요](#네트워크-개요)
- [애플리케이션 레이어](#애플리케이션-레이어)
- [트랜스포트 레이어](#트랜스포트-레이어)
- [네트워크 레이어](#네트워크-레이어)

### 2. 라우팅 알고리즘
- [라우팅 알고리즘 종류](#라우팅-알고리즘-종류)

### 3. 링크레이어 및 Wireless and Mobile Network
- [링크 레이어](#link-layer-링크레이어)
- [CDN](#유튜브-같은-스트리밍-서비스의-cdn-작동-흐름-요약-정리)
- [보안](#보안)
---

### 네트워크 개요
- 네트워크 개요

    - 네트워크 구조
        
        - 네트워크 엣지 (Network Edge)

            - 클라이언트(Client): 데이터를 요청하는 주체 (예: 웹 브라우저 스마트폰)
            - 서버(Server): 요청을 처리하고 응답을 제공하는 주체
        
        - 네트워크 코어 (Network Core)

            - 라우터(Router): 네트워크를 구성하는 핵심 장비로 패킷을 목적지로 전달하는 역할을 수행 
            - 스위치(Switch): 로컬 네트워크에서 패킷을 전송하는 장비 (L2 스위치: MAC 주소 기반 L3 스위치: IP 기반)
    
    - 통신 방식
        
        - 패킷 기반 통신(Packet Switching)
            - 데이터를 작은 단위(패킷)로 쪼개어 전송
            - 패킷들은 독립적으로 경로를 결정하며 최적의 경로를 선택 가능
            - 여러 사용자가 동시에 통신 가능  대역폭 효율적 활용
            - 단점: 패킷 손실(Packet Loss) 지연(Delay) 발생 가능

    - 네트워크에서 발생하는 지연(Delay)
        
        - 딜레이 유형
            
            - 프로세싱 딜레이 (Processing Delay)

                - 라우터가 패킷을 수신한 후 헤더를 검사하고 적절한 경로를 찾는 데 걸리는 시간
            
            - 큐잉 딜레이 (Queuing Delay)

                - 패킷이 전송 대기열(Queue)에 쌓여서 기다리는 시간 (네트워크 트래픽이 많을수록 증가)
            
            - 트랜스미션 딜레이 (Transmission Delay)

                - 패킷을 링크로 전송하는 데 걸리는 시간
                - 계산: L(bits) / R(bps) (L  패킷 크기 R  링크 속도)
            
            - 프로파게이션 딜레이 (Propagation Delay)

                - 패킷이 물리적인 매체를 통해 이동하는 데 걸리는 시간
                - 계산: d / s (d  거리 s  신호 전파 속도)
            
            - 추가 개념: 패킷 드랍(Packet Drop)
                
                - 라우터의 버퍼(Queue)가 가득 차서 더 이상 패킷을 수용할 수 없을 때 발생
                - 네트워크 혼잡(Congestion)의 주요 원인


---

### 애플리케이션 레이어

- HTTP (HyperText Transfer Protocol)
    - TCP 기반으로 동작  신뢰성 있는 전송 보장

    - 서버는 상태(State)를 유지하지 않음 (Stateless)

    - HTTP 1.1 기본 동작 방식

        - Non-Persistent HTTP: 매번 새로운 TCP 연결 생성  비효율적
        - Persistent HTTP (기본 설정): 기존 TCP 연결을 유지하여 여러 개의 요청 처리 가능

    - 3-way Handshake 과정 (TCP 기반 통신)

        - 클라이언트  서버: SYN (연결 요청)
        - 서버  클라이언트: SYN-ACK (요청 수락)
        - 클라이언트  서버: ACK (연결 확립)

- DNS
    - 도메인 이름을 IP 주소로 변환하는 시스템

    - 계층적 구조
        - Root DNS  TLD DNS (.com .org .kr 등)  Authoritative DNS
    
    - 캐싱(Caching)을 활용하여 성능 최적화

---

### 트랜스포트 레이어
- UDP (User Datagram Protocol)
    
    - 비연결형(Connectionless) 단순한 헤더 구조  빠름
    - 신뢰성이 없음 (순서 보장 X 패킷 손실 가능)
    - 용도: 실시간 스트리밍 VoIP DNS

- TCP (Transmission Control Protocol)

    - 신뢰성 보장 (데이터 손실 복구 흐름 제어 혼잡 제어)
    - 스트림 기반(데이터를 순차적으로 전송 및 재조립)
    
    - TCP의 주요 개념
        - Send Buffers / Receive Buffers

            - 송신 및 수신 측에서 데이터를 임시 저장하는 공간

- TCP 세그먼트 (TCP Segment)

    - SEQ(Sequence Number): 패킷의 순서를 나타냄 (흩어져서 전송되는 데이터 조각의 순서를 보장)000
    - ACK(Acknowledgment Number): 수신 확인 응답

- TCP의 주요 문제 및 해결 방법
    - 패킷 에러 (Packet Error)

        - 검출 (Error Detection)  체크섬 사용
        - 재전송 (Retransmission)  손실된 패킷만 다시 전송
    
    - 패킷 손실 (Packet Loss)

        - Timeout 발생 시 패킷 재전송

- TCP 파이프라이닝 기법
    - Go-Back-N

        - 연속된 패킷을 전송하지만 하나라도 손실되면 이후 모든 패킷을 다시 전송
        - 구현이 간단하지만 비효율적
    
    - Selective Repeat

        - 손실된 패킷만 재전송  효율적
        - 구현이 복잡하고 추가적인 버퍼 필요

- 혼잡 제어 (Congestion Control)

    - Slow Start: 처음에는 작은 윈도우 크기로 시작 후 점진적 증가
    - Additive Increase: 안정적인 상태에서 윈도우 크기를 서서히 증가
    - Multiplicative Decrease: 혼잡 발생 시 윈도우 크기를 급격히 줄임

- TCP 버전 비교
    - TCP Tahoe
        - 패킷 손실 시 Slow Start로 돌아감
    - TCP Reno
        - 패킷 손실 시 Fast Recovery를 사용하여 성능 향상

---

### 네트워크 레이어

- IP (Internet Protocol)

    - 비신뢰성(Unreliable) 최선형 서비스(Best-Effort Service) 제공
    - 데이터그램 방식(각 패킷이 독립적으로 라우팅됨)

- 라우터 (Router)

    - Forwarding: 패킷을 올바른 경로로 전달하는 과정
    - 포워딩 테이블 (Forwarding Table) 활용 : 라우팅 알고리즘을 통해 생성된다.
    - Longest Prefix Matching: 최적의 경로를 찾기 위해 가장 긴 공통 프리픽스를 가진 경로 선택

- NAT 개념
    - 내부 네트워크에서 임의의 IP 주소를 사용하다가
    - 외부로 통신할 때는 공인 IP 주소로 변환하여 사용.
    - IP 주소 부족 문제 해결을 위해 임시 방편으로 도입된 기술.

- NAT 도입 배경
    - IPv4의 한계: 1970년대 설계  현재 기기 수요를 감당하지 못함.
    - IPv6 전환의 어려움:
        - 이미 자리 잡은 레거시 시스템 때문에 전환이 지연.
        - 전환 비용 호환성 문제 등 현실적 장애물이 존재.
        - 그래서 NAT를 채택하여 빠른 해결책을 마련했으나 이는 임시방편에 불과.

- NAT의 부작용 및 문제점
    - 종단 간 연결성(end-to-end connectivity) 저하
    - 내부에서 외부로는 통신이 쉬워도
    - 외부에서 NAT 내부 서버로 접근하기 어렵다.
    
    - OSI 계층 구조 위반
        - 라우터는 원래 헤더(header)만 참조해야 하지만
        - NAT는 데이터 영역까지 수정해 계층 간 경계를 침범.
        - 전송 계층(TCP/UDP)과 네트워크 계층(IP) 정보를 동시에 변경함.
    
    - 서비스 및 프로토콜 호환성 문제
        - 특정 P2P 서비스 화상회의 온라인 게임에서 통신 지연이나 연결 문제 발생.
        - 서버를 NAT 뒤에서 열기 위해선 추가적인 NAT Traversal 기술이 필요.

- ICMP : internet control message protocol 
    - 패킷이 TTL 이 0 이 되는 등의 이유로 유실되었을 때 본인이 드랍되었다고 알려줄 필요가 있어서 나온 프로토콜
    - TTL : Time to Live
    - traceroute  ICMP 의 홉을 1개씩 증가시켜 라우터 경로 파악


  네트워크 - 라우팅 알고리즘 정리

라우팅 알고리즘은 네트워크에서 패킷이 목적지까지 도달하기 위해 최적의 경로를 찾는 방법을 제공합니다. 크게 두 가지 주요 방식이 있습니다:

---

### 라우팅 알고리즘 종류

1. Link State Algorithms (링크 상태 알고리즘)  
    - 전체 네트워크 토폴로지를 알고 경로를 찾는 방식  

    - 각 라우터는 링크 상태 정보를 모든 라우터에 브로드캐스트하여 네트워크 전체 지도를 작성합니다.  
    - 최단 경로 계산에 주로 다익스트라 알고리즘 사용  

- 다익스트라 알고리즘
    - 시간 복잡도: O(n2) (n: 노드 수)  
    - 작동 원리:  
        1. 출발 노드에서 인접한 노드들의 비용을 초기화  
        2. 가장 짧은 경로를 가진 노드부터 선택  
        3. 선택한 노드를 기준으로 인접 노드들의 최소 비용 갱신  
        4. 모든 노드의 최단 경로가 확정될 때까지 반복  
        5. 백트래킹을 통해 실제 최단 경로 추적  

    - 특징:  
        - 단순하고 직관적  
        - 초기 비용 계산 후 빠른 경로 탐색 가능  
    - 단점:  
        - 트래픽 불안정성: 트래픽이 한쪽으로 쏠렸다가 다른 쪽으로 이동하는 현상 발생  
        - 확장성 문제:  
            - 네트워크 규모가 커지면 브로드캐스트 오버헤드 증가  
            - 현실적으로 큰 네트워크에서는 비효율적  
            - 일반적으로 하나의 네트워크 단위로만 실행  

---

2. Distance Vector Algorithms (거리 벡터 알고리즘)  
    - 각 라우터가 이웃 라우터로부터 거리 정보를 주고받아 경로를 찾는 방식  

    - 분산 처리 기반: 라우터는 자신의 거리 벡터만 인접 라우터에 전달  
    - 네트워크 전체 정보를 직접 알 필요 없음  

- 벨만-포드 방정식 (Bellman-Ford Equation)  
    - 동적 계획법(Dynamic Programming) 기반  
    - 재귀(Recursion) 사용  

수식  
```txt
let
  d_x(y) : cost of least-cost path from node x to node y
then
  d_x(y)  min  c(xv)  d_v(y)  for all neighbors v of x
```




---

### Link Layer 링크레이어
- 네트워크 인터페이스 카드에 있음.
- 우리는 데이터를 보낼 때 패킷을 제일 먼저 게이트웨이 라우터로 보낸다.
- Broadcast medium 방식이기 때문에 그 상황에서 여러개의 패킷이 보내지게 된다면 COLLISION 즉 충돌이 발생하게 된다. 그 현상을 핸들링하기 위한 것이 링크레이어의 존재의의 이다.

- Multiple access protocol
- Medium Access Control (MAC) protocol

    - TDMA : time division multiple access
    - FDMA : frequncy division multiple access
    - RANDOM access protocols :
        - ALOHA
        - CSMA (Listen before transmit) : 
        한번 들어보고 아무도 전송하고있지 않으면 전송시작 그러나
        브로드캐스트 되기까지의 시간동안(거희동시) 충돌발생가능성이있음. 그러나 충돌되어도 둘다 끝까지 전송하기에 매체의 낭비
        - CSMA/CD(유선) : collision 감지되면 바로 중단 그런데 충돌시 따라야할 규칙은
            - binary backoff : 012...2n-1 중에 하나를 골라서 그 시간 후에 다시 전송
            - n 은 충돌 회수가 늘어날 수록 범위가 증가.
            - 48bit 크기의 프레임 전송
        - CSMA/CA(무선) : Ack 가 존재 (TCP의 Ack와는 다르다)  충돌이 발생해도 데이터전송을 멈추지않고 끝까지 보낸다. (피해가 크다.)
        - RTS/CTS 의 등장 : 돌다리도 두들겨보고 건너자. 재전송은 7회까지


### Wireless and Mobile Network

- Wireless : ap 포인트에서 벗어나지않고 선이 없는 것
- Mobility : 하나의 서브넷 등을 벗어나며 이동하면서 사용하는 경우

- 문제 : 기존의 유선 MAC 프로토콜으로 COLLISION DETECT 불가.

- IEEE 802.11 Wi-Fi

    - passive scanning : 비콘 프레임에 AP를 담아 주기적으로 보낸다.

    - AP 는 호스트 입장에서는 MAC 주소가 있는 링크레이어의 기기로 인식 외부 라우터에서 올 때는 그저 스위치로 인식된다.

---

### 유튜브 같은 스트리밍 서비스의 CDN 작동 흐름 (요약 정리)
1. Manifest
    - 영상의 조각(chunk) 구성 정보를 담은 메타파일
    - 예: manifest.mpd (DASH) master.m3u8 (HLS)

- 포함 정보:

    비디오의 인코딩 레벨 (360p 720p 1080p)

    각 화질 별 chunk 목록 (segment1 segment2 )

    각 chunk의 재생 시간 순서 등

    클라이언트는 이걸 읽고 chunk를 순서대로 요청함  버퍼링 최소화

2. CDN은 정적 파일만 서빙
    manifest 파일과 chunk 파일은 모두 정적 파일

    클라이언트가 chunk 요청  CDN은 그냥 빠르게 보내주기만 하면 됨

    실제 영상 처리(인코딩 디코딩)는 클라이언트에서 수행
.

3. 왜 전세계에 CDN을 배치하는가
    사용자와 가까운 서버에서 콘텐츠 전송  지연 감소 속도 증가

    트래픽을 본 서버에 집중시키지 않고 분산  혼잡 방지

    영상 chunk는 수백 MB씩 갈 수도 있기 때문에 물리적 거리 줄이는 게 핵심
.
4. CDN 서버는 어떻게 선택되는가

    - GeoDNS
        클라이언트 IP 위치를 기반으로 가장 가까운 CDN IP를 반환

        예: youtube.com  서울 사용자는 203.0.113.45 (서울 POP) IP 받음

    - Anycast DNS
        같은 IP 주소를 여러 서버가 가짐

    - BGP(라우팅 프로토콜) 덕분에 경로상 가장 가까운 노드로 요청 전달됨

        즉 물리적으로 가까운 서버  네트워크 경로상 가까운 서버
        최적의 CDN으로 연결

    - 전체 흐름
        ```
        사용자  youtube.com 요청
                
        GeoDNS  위치 기반으로 CDN IP 반환
                
        Anycast  경로상 가장 가까운 CDN 노드로 연결
                
        CDN  manifest  chunk 파일 빠르게 전달
                
        클라이언트  버퍼링 최소화된 스트리밍
       ```

---

### 보안
용어 정리
- WireShark (실습해보기)
    - 네트워크 패킷 캡쳐 및 분석이 가능한 패킷 스니퍼 도구
    - TCP  UDP  HTTP 등 다양한 프로토콜 분석 가능
    - 네트워크 트래픽 문제 해결 및 보안 분석 시 유용함.

- Proxy
    - 클라이언트 - 서버 사이에 위치해 요청을 중계하는 서버

- VPN
    - Virtual Private Network
    - 공용 인터넷을 통해 암호화된 사설 네트워크 처럼 사용하는 기술
        - 보안 통신 가능하게 함
        
- 대칭키 (Symmetric Key)    AES DES
    - 빠르고 구현이 간단하다.
    - 하나의 공통 키를 사용하여 암호화된 통신
    - 키를 안전하게 공유하는게 어려움

- 공개키 (Public Key)   RSA
    - 느리다 why 공개키와 개인키를 조합하는 과정이 존재하기 때문
    - 구현이 복잡하다.


- 생각정리

```
대칭키를 생성 후 보내는 쪽이 상대방의 공개키를 가져와서 암호화 한 후 키를 보내면 상대방은 자신의 개인키로 그걸 복호화해서 키를 획득한다.
그 후로는 속도가 빠른 대칭키를 활용하여 보안 소통을 시작.
이 공개키를 믿을 수 있는 이유는 인증서를 믿어야 동작하는 시스템 구조이기 때문이다.
```

- SSL (TLS)  HTTPS  SSH

    - SSL : 어플리케이션 레이어와 트랜스포트 레이어 사이에 위치하여 message 를 record 로 감싸서 암호화시킨다.
        - SSL 에서는 MAC 이 담기게 되는데 이 MAC은 링크레이어의 MAC이 아닌 다른 개념
            - MAC(Message Authentication Code) : 시퀀스번호  레코드타입  버전  길이  플레인메세지 ...
                - 구조 : 헤더  플레인메시지  MAC
    
    - HTTPS : 기존 HTTP 프로토콜에서 SSL 이 첨가된 기법

    - SSH : 원격으로 서버에 로그인해서 조작할 수 있는 기법  보안수준이 높다.
        - SSL 과 비슷한 흐름 ( 비대칭키(RSA등) 기반 대칭키 생성 - 그 후로는 대칭키(AES 등) 통신 으로 속도 확보 )