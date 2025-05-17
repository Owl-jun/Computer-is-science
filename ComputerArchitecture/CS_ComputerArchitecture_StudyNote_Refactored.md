# 컴퓨터 구조 - 강의 정리

## 목차
### 1. 컴퓨터 시스템 기초
- [컴퓨터는 어떻게 동작할까?](#컴퓨터는-어떻게-동작할까)
- [변수가 저장되는 곳](#변수가-저장되는-곳)
- [자료형 및 bit/byte 등 기초 + 부동소수점 정리](#자료형-및-bit/byte-등-기초-+-부동소수점-정리)

### 2. 명령어 체계와 아키텍처
- [Machine Language](#machine-language)
- [ISA (Instruction Set Architecture)](#isa-instruction-set-architecture)
- [RISC (Reduced Instruction Set Computer)](#risc-reduced-instruction-set-computer)
- [CISC (Complex Instruction Set Computer)](#cisc-complex-instruction-set-computer)
- [MIPS (RISC 계열 CPU 아키텍처)](#mips-risc-계열-cpu-아키텍처)
- [MIPS 명령어 형식 (Instruction Format)](#mips-명령어-형식-instruction-format)
- [Linker](#linker)

### 3. 파이프라인과 성능 요소
- [컴퓨터 구조 - 파이프라인, 밴드윗, 레이턴시 요약](#컴퓨터-구조---파이프라인-밴드윗-레이턴시-요약)
- [파이프라인(Pipeline)](#파이프라인pipeline)
- [밴드윗(Bandwidth) vs 레이턴시(Latency)](#밴드윗bandwidth-vs-레이턴시latency)
- [Bandwidth 공식](#bandwidth-공식)
- [Latency 공식 (메모리)](#latency-공식-메모리)
- [스칼라 vs 슈퍼스칼라](#스칼라-vs-슈퍼스칼라)
- [의존성(Dependency)과 스톨](#의존성dependency과-스톨)
- [클럭 속도와 클럭 주기](#클럭-속도와-클럭-주기)
- [정리 키워드](#정리-키워드)
- [Out-Of-Order Pipeline](#out-of-order-pipeline)

### 4. 캐시와 메모리 계층
- [CPU Cache 및 매핑 방식 정리](#cpu-cache-및-매핑-방식-정리)
- [캐시(Cache)란?](#캐시cache란)
- [캐시 쓰기 정책 (Write Policy)](#캐시-쓰기-정책-write-policy)
- [캐시 매핑 방식 (Mapping Policy)](#캐시-매핑-방식-mapping-policy)
- [1. Direct-Mapped Cache](#1-direct-mapped-cache)
- [2. Fully Associative Cache](#2-fully-associative-cache)
- [3. Set-Associative Cache (현실에서 가장 많이 씀)](#3-set-associative-cache-현실에서-가장-많이-씀)
- [Direct-Mapped의 한계와 개선 방법](#direct-mapped의-한계와-개선-방법)
- [오해 방지: Direct-mapped는 "4곳만 쓰는 것"이 아니다!](#오해-방지-direct-mapped는-4곳만-쓰는-것이-아니다!)
- [캐시 설계에서 자주 나오는 키워드 요약](#캐시-설계에서-자주-나오는-키워드-요약)

### 5. 예외와 인터럽트
- [Page](#page)
- [Exception (내부사건)](#exception-내부사건)
- [Interrupt (외부사건)](#interrupt-외부사건)


---

 컴퓨터는 어떻게 동작할까 

- CPU  레지스터 / 메모리(RAM) / IO ...
    - CPU : RAM과 함께 사람으로 치면 뇌의 역할을 한다.
        - 레지스터 : CPU가 연산을 할 때 필요한 값을 저장하는 초고속 저장소 이다.
            - CPU가 연산할 데이터를 RAM  캐시 메모리  레지스터 순으로 가져온다.

        - OS의 ISA(인스트럭션 셋 아키텍쳐 즉 컴퓨터 자체의 명령어(기계어))가 32비트 64비트 여부에 따라 레지스터가 한번에 수행할 수 있는 용량이 달라진다.
        - 예를 들어 64비트 CPU는 한 번에 64비트(8바이트) 크기의 데이터를 처리할 수 있다. 하지만 연산의 종류에 따라 8바이트보다 적거나 많을 수도 있다.
            - 코어 는 CPU 안에서 연산을 수행하는 처리장치다.
            - 궁금증 그렇다면 코어가 많다면 한번에 코어수 x 8byte 만큼 수행이 가능한건가
                - 해결 프로그램이 싱글코어만 사용하도록 프로그래밍 되어 있다면 멀티코어는 아무 쓸모가 없어진다.
                - 하지만 병렬처리 / 멀티스레딩 처리가 되어있다면 여러코어를 동시에 활용 할 수 있다.

        - 그 외 : ALU(산술)  CU(제어)  FPU(부동소수점)  캐시메모리(RAM보다 빠른 고속 메모리 자주 사용하는 데이터를 저장 하여 CPU 속도향상에 도움)

    - RAM : 프로세스 (프로그램)을 실행하면 저장소(하드디스크) 에서 프로그램을 가져와 올려 실행하는 곳
        - RAM 공간이 부족하다면
            - 가상메모리 활용  하드디스크의 일부분을 스왑 영역으로 이동시켜 사용할 수 있다.        
                - 가상메모리  스왑 동작 방식 간단요약
                    - 프로그램 실행 - RAM 에 올림 - RAM이 부족함 - 사용하지않는 데이터를 하드로 보내기 (스왑) - 필요하면 다시 RAM으로 가져옴 but 속도는 굉장히 느려질 수 있다.


- 우리가 코드를 짜고 실행시키면 하드디스크 - RAM - 캐시 - 레지스터 - CPU 연산 수행 .... 순으로 실행된다.


python
value  3

- 위 코드의 의미.
    - 메모리 공간에 int 자료형을 표현할 수 있는 공간 만큼 자리를 확보하고 거기에 3 이라는 값을 저장한다.

- 우리가 쓴 코드는 어떻게 동작하는가.
    - 아래 코드를 살펴보자.

---

 변수가 저장되는 곳

- 위 코드 학습
    - 1. 맨 위 value 변수와 def function() 안의 변수는 같은 변수인가 다른 변수인가
    - 2. 중간의 i 와 for i in  안의 i는 같은 변수인가 다른 변수인가
    - 3. value  6 은 무엇을 의미할까
    - 4. for i in range(i 20) 은 어떤 의미인가
    - 5. range(startendsteps) 함수는 어떤 자료형을 리턴하는가

---

 자료형 및 bit/byte 등 기초  부동소수점 정리

- 예전 공부할 때 정리 해놓은 글
    
    - 블로그바로가기(https://blog.naver.com/beatspermymind/223571398078)

---

 Machine Language

 ISA (Instruction Set Architecture)

- CPU가 이해할 수 있는 명령어의 종류와 그 형식들을 정의한 규칙 모음

    - 하드웨어(CPU 설계자)와 소프트웨어(컴파일러 운영체제 프로그래머) 사이의 약속이자 인터페이스

 RISC (Reduced Instruction Set Computer)
단순하고 빠른 명령어로 이루어진 CPU 설계 방식

명령어들이 한 사이클 안에 실행됨

하드웨어 기준 Reduce : 단순한설계
예: ARM MIPS 등이 대표적인 RISC CPU

 CISC (Complex Instruction Set Computer)
복잡한 명령어도 하드웨어가 직접 처리하는 방식

명령어 하나가 여러 일을 함

하드웨어 기준 Complex : 복잡한설계
예: 인텔의 x86 계열 CPU

 MIPS (RISC 계열 CPU 아키텍처)
학습용/교육용으로 많이 쓰임

명령어 구조가 단순하고 규칙적

명령어 길이는 항상 32비트 (고정형)


 MIPS 명령어 형식 (Instruction Format)
- MIPS는 명령어를 3가지로 구분

    -  1. R-type (Register type)
        레지스터끼리 연산

    필드	크기 (bit)	의미
    :--::--::--:
    opcode	6	연산 종류
    rs	5	첫 번째 레지스터
    rt	5	두 번째 레지스터
    rd	5	결과 저장 레지스터
    shamt	5	shift할 때만 사용 (보통 0)
    funct	6	연산 세부 정보 (ADD SUB 등)

    예: add t0 t1 t2  t0  t1  t2

    -  2. I-type (Immediate type)
        레지스터  즉시 값 또는 메모리 관련

        필드	크기 (bit)	의미
        :--::--::--:
        opcode	6	연산 종류
        rs	5	기준 레지스터
        rt	5	결과 저장 또는 대상 레지스터
        immediate	16	상수 or 주소 오프셋

        예: 
        - addi t0 t1 10  t0  t1  10
        - lw t0 4(t1)  t0  메모리t1  4

        C 언어의 메모리 연산과 유사한 형태
        lw sw 같은 명령어는 포인터를 이용한 메모리 접근(C 스타일)과 흡사.

    -  3. J-type (Jump type)
        코드 흐름을 점프(이동) 시킬 때 사용

        필드	크기 (bit)	의미
        :--::--::--:
        opcode	6	연산 종류 (보통 jump)
        address	26	이동할 주소 (jump target)

        예: j 10000  프로그램을 10000번지로 점프


- 기타 핵심 용어

용어	뜻
:--::--:
Opcode	operation code. 어떤 연산을 수행할지 지정 (예: add sub lw 등)
rs rt rd각각 소스 레지스터 / 타겟 레지스터 / 결과 레지스터
Immediate	명령어에 직접 들어 있는 숫자 (상수값)
Jump	프로그램 흐름을 특정 위치로 이동시키는 명령 (함수 호출이나 반복문 구현에 사용)

- 왜 instruction을 나누는가
CPU는 명령어를 32비트씩 받아 처리함
명령어의 종류에 따라 필요한 정보가 다르니까 그에 맞춰 R / I / J 형식으로 나눔
구조가 명확하면 파이프라인 처리와 하드웨어 설계가 쉬워짐 (RISC 설계의 장점)


- 요약 정리

타입	설명	예시
:--::--::--:
R-type	레지스터 연산	add t0 t1 t2
I-type	상수 연산 메모리 접근	addi lw sw
J-type	코드 흐름 변경 (점프)	j 10000


---

 Linker

- Static Linking
    - 필요한 라이브러리 등을 실행 파일에 그대로 복사해서 포함
    - 실행 파일이 굉장히 커지지만 실행시 외부 파일이 필요가없음

    - but 간단한 수정 한번에 전체 리빌드 실행파일이 굉장히 커짐

- Dynamic Linking
    - 필요한 라이브러리를 실행 파일에 링크정보만 남겨두고 런타임에서 (dllso)등을 로딩해서 사용
    - 메모리 절약 라이브러리 수정으로 전체 프로그램 개선 가능

    - 실행 환경 맞추기가 어려움


- 여태 신경도 쓰지않고 써왔던 Visual Studio 에서 내가 작성한 코드들은 전부 동적 링크(Dynamic link) 였다.
- 설정에서 /MT (정적 링크) 로 교체해준다면 내가 include 한것들은 exe파일로 와장창 복사될 것이다.
- /MD (동적 링크)를 사용하였기에 내가 사용할 함수만 dll 에서 가져온다.

- 그렇다면 정적링크를 써야하는 상황은
    - 임베디드 / 펌웨어 : 하나의 바이너리로 완성시켜야함  외부 DLL 이 없음
    - 보안이 중요한 프로그램 : 외부 DLL 바꿔치기나 버전충돌 등 위험을 배제하기 위해
    - 휴대용 프로그램 : 외부에 DLL 설치가 불가
    - 운영체제 커널/드라이버
    - 네이티브 크로스 플랫폼 배포


- 리틀 앤디안
    - LSB (제일 작은 것)을 우선순위로 메모리 주소가 낮은 쪽 부터 배치한다.
    - 0x 12 34 56 78 : 4바이트 정수
    - 리틀 앤디안 변환 - (0번지)78 (1번지)56 (2번지)34 (3번지)12

- 빅 앤디안
    - MSB 를 우선순위로 메모리 주소가 낮은 쪽 부터 배치한다.
    - 0x 12 34 56 78 : 4바이트 정수
    - 빅 앤디안 - 12 34 56 78

- 주의 : 여기서 작다 라는 표현은 메모리 주소가 낮다 라는 것. 즉 제일 우측에 있는 LSB를 상상해보면 된다.
- 빅 앤디안으로 메모리 주소를 학습했다면 그것을 뒤집은 것이 리틀앤디안 이라는 개념이다.

- 리틀 앤디안 : intel x86 x86-64  AMD / intel 기반 시스템  ARM  Windows  Linux(x86기반)
- 빅 앤디안 : 네트워크 프로토콜 (TCP/IP UDP  HTTP)  서버용 CPU 일부

- 다른 장비와 통신할 때 엔디안을 확인하고 순서를 바꿔주는 등의 작업이 필요하다.

- 실제로 리틀앤디안에서 int 1 은 00000001 00000000 00000000 00000000 이렇게 저장되어있다.
- 이걸 우리가 포인터로 접근했을때 리틀앤디안 CPU는 맨처음 값이 LSB라 생각하고 읽기 때문에(해석할때 순서를 반대로 조합하기 때문에) 0x00000001 이 된다.


- 기타 등등 

    - 리로케이션 텍스트 (linker symbols)
        - 컴파일된 파일 중 자신의 지역이 아닌 곳에 위치한 심볼(변수함수)을 만났을 때  와 같은 리로케이션 텍스트로 대체하여 obj 파일을 만든다.
        - 링커가 심볼을 보고 실제 구현된 파일을 찾아서 심볼에 실제 주소를 바인딩 해준다.

    - 데이터 세그먼트
        - .bss: 초기화되지 않은 전역/static 변수 저장 ( 실행 시 0으로 초기화)
        - .data: 초기화된 전역/static 변수 저장

    - ( strong / weak ) Symbols
        - strong  모든 func  procedure 이름은 strong 이다 또 선언과 동시에 초기화되는 변수도 strong이다.
            - 특징 : 중복 변수명을 허용하지 않는다.
            - weak 심볼과 중복 되었을 때 무조건 링커는 strong을 선택한다.
            - 예) int a  30  void func1()

        - weak  선언만 된 변수명 중복이 허용된다.
            - 특징 : 중복을 허용하나 링커가 무엇을 선택할지 알 수 없다.( 중복시 위험하다 . )
            - 예) int b
        
        - Rule 
            1. strong vs strong : link error
            2. strong vs weak   : strong win
            3. weak vs weak : 어떤 것을 선택한다 ( 이 때 double vs int 와 같이 바이트가 다른 자료형이 오게되면 다른 변수영역까지 침범위험)

    - Entry Point (진입점)
        - 아래 두개는 약간 다르지만 순서는 _start - main() 이런 느낌
        - ELF : 보안성과 유연한 메모리 설계를 고려해서 고정주소가 아님 유동성 있음
        - EXE : 옛날에는 고정된 주소를 사용했으나(성능보장  속도를 위해) 보안 등의 이유로 ELF의 ASLR  PIE 과 비슷한게 도입되어 재배치 가능함.

    - 프로그램 실행 흐름도
    less
    하드디스크
    
      (더블클릭 / ./a.out)
    V
    OS 커널
     프로세스 생성 (fork execve CreateProcess)
     가상메모리 공간 생성 (스택 힙 코드 라이브러리)
     실행파일 파싱 (ELF/PE 포맷 분석)
         필요한 섹션만 DRAM에 매핑 (Demand Paging mmap)
     e_entry / EntryPoint로 점프 (실행 시작 주소)
        
    CPU가 명령어 실행 시작  _start  main()
    


---

  컴퓨터 구조 - 파이프라인 밴드윗 레이턴시 요약

  파이프라인(Pipeline)

- 과거 CPU(예: 386)는 명령어가 순차적으로 한 싸이클씩 처리되었음
- 파이프라인 도입 이후 명령어의 단계(fetch decode execute...)를 겹쳐서 실행
- 동시에 여러 명령어가 다른 단계에 존재할 수 있음  성능 향상

  예시  
 - 세탁기 공정: 빨래 넣기 / 비누칠 / 헹굼을 동시에 다른 빨래에 적용  
 - IF  ID  EX  MEM  WB 등 5단계 파이프라인 구조

---

  밴드윗(Bandwidth) vs 레이턴시(Latency)

 항목  의미  단위  목표 
------------------------
 Bandwidth  초당 전송 가능한 데이터 양  GB/s  높을수록 좋음 
 Latency  1개의 요청이 완료될 때까지의 시간  ns  낮을수록 좋음 

  Bandwidth 공식

 예:  
 - Bus Width: 64bit  8Byte  
 - Clock: 1600MHz  
 - Transfers: 2 (DDR)  
  8  1600  2  25.6 GB/s
Bandwidth  Bus Width  Clock Frequency  Transfers per Clock
---

  Latency 공식 (메모리)

 예:  
 - CL  16  
 - Data Rate  3200 MT/s  
  (16  2000) / 3200  10 ns
Latency(ns)  (CL  2000) / DataRate(MT/s)
---

  스칼라 vs 슈퍼스칼라

 항목  Scalar  Superscalar 
---------------------------
 실행 개수  명령어 1개씩  명령어 여러 개 병렬 실행 
 구조  파이프라인 1줄  파이프라인 여러 줄 
 병렬성  없음  있음 
 전제 조건  단순  명령어 의존성 분석  유닛 분화 필요 

  Superscalar CPU는 동시에 여러 명령어를 처리할 수 있는 여러 실행 유닛 (INT FP Load/Store) 를 가짐

---

  의존성(Dependency)과 스톨

1. RAW (Read After Write): 앞 명령의 결과가 필요
2. WAR (Write After Read): 뒤 명령이 먼저 쓰면 안 됨
3. WAW (Write After Write): 둘 다 같은 레지스터에 쓰려고 함

 해결 방법:  
 - Forwarding: 결과를 바로 다음 단계로 넘김  
 - Stalling: 대기  
 - Register Renaming: 물리적 레지스터 이름 바꿔서 충돌 회피  
 - Out-of-Order Execution: 순서 바꿔 처리

---

  클럭 속도와 클럭 주기

- 클럭 주기(ns)  1 / 클럭 속도(Hz)
- 3.33GHz  1 / 3.33e9  0.3003ns

 클럭 속도  클럭 주기 
-----------------------
 1GHz       1.0ns      
 2GHz       0.5ns      
 3.33GHz    0.3ns      

---

  정리 키워드

- 파이프라인: 겹쳐서 실행하는 구조
- 밴드윗: 한 번에 얼마나 많이 처리
- 레이턴시: 한번 처리하는데 얼마나 걸려
- 슈퍼스칼라: 동시에 명령어 여러 개
- 클럭: 한 싸이클당 처리 시간 (ns 단위)

---


---

 Out-Of-Order Pipeline
- bypass (Forwarding)
    - 연산 결과가 레지스터에 기록되지 않아도 필요한 후속 명령어에게 결과를 우회해서 바로 전달
    - 데이터 해저드 줄이는데 필수적인 요소

- Scoreboard
    - 명령어 실행을 제어하는 중앙 제어 장치
    - 명령어 간 데이터 의존성 자원사용여부 완료여부 등을 추적하여 실행 타이밍을 조절
    - 명령어 발행(issue) 실행(execute) 쓰기(write) 타이밍을 따로 관리
    - 구조가 복잡하고 확장성 제한적인 단점

- Tomasulos Algorithm 아웃오브오더 파이프라인의 뼈대 
    - 명령어 레벨 병렬성 (ILP)을 최대한 활용하기 위한 알고리즘
    - 3 ideas
        - Reservation Stations (RS)
            - 명령어 임시 저장 버퍼
            - 피연산자 값이 도착할 때 까지 대기
            - 준비되면 즉시 실행 가능 (오퍼랜드 준비되었는지 여부가 핵심)
        - Register Renaming (레지스터 이름 바꾸기)
            - WAW WAR 해저드 피하기 위해 실 레지스터 대신 Reservation Station을 활용하여 가상레지스터 부여
        - Common Data Bus (CDB)
            - 실행 경과를 모든 대기 중인 유닛/레지스터로 브로드캐스트
            - 연산 결과가 필요한 모든 곳으로 한 번에 전달 - bypass 역할도 포함
            - 동시에 여러결과를 쓸 수 없기 때문에 버스 자원이 제한사항이 될 수도 있음
    
    - Issue 단계: 명령어를 Reservation Station에 넣음
    - Execute 단계: 피연산자들이 모두 준비되면 실행
    - Write Result 단계: CDB로 결과를 브로드캐스트  레지스터 or RS 대기중인 명령어에게 전달



---

 CPU Cache 및 매핑 방식 정리

 캐시(Cache)란
- CPU와 메인 메모리(RAM) 사이에 위치한 작고 빠른 저장소
- 자주 접근하는 데이터를 임시로 저장하여 성능을 향상시킴

---

 캐시 쓰기 정책 (Write Policy)

 정책  설명  장점  단점 
------------------------
 Write-back  캐시에만 먼저 쓰고 나중에 메모리에 반영  빠름 메모리 접근 줄음  데이터 불일치 가능성 
 Write-through  캐시와 메모리에 동시에 씀  항상 일관된 상태  느림 
 Write-around  캐시를 건너뛰고 메모리에만 씀  캐시 오염 방지  캐시 미스 증가 

 현대 CPU 대부분은 Write-back  Write-allocate 사용

---

 캐시 매핑 방식 (Mapping Policy)

 1. Direct-Mapped Cache
- 메모리 블록  캐시의 정해진 위치(1곳)에만 저장 가능
- 구조 단순하고 빠르지만 충돌(conflict miss)이 자주 발생

 2. Fully Associative Cache
- 메모리 블록  캐시 아무 곳에나 저장 가능
- 적중률은 높지만 구현이 복잡하고 느림

 3. Set-Associative Cache (현실에서 가장 많이 씀)
- 캐시를 여러 Set으로 나누고 각 Set에 여러 개 Block을 가짐
- 예: 4-way set-associative  하나의 Set에 최대 4개 Block
- 성능과 구현 복잡도 간의 밸런스가 좋음

---

 Direct-Mapped의 한계와 개선 방법

 문제점  개선 방법  설명 
-------------------------
 충돌 발생  Set-Associative Cache  한 index에 여러 개 block 저장 가능 
 교체 블록 낭비  Victim Cache  최근 교체된 블록을 임시로 보관 
 낮은 적중률  Pseudo-associative Cache  다른 후보 위치도 체크 
 단순 교체 정책  Smart Replacement  LRU Random LFU 등 사용 

---

 오해 방지: Direct-mapped는 4곳만 쓰는 것이 아니다

- Direct-mapped cache는 전체 메모리 커버 가능
- 단지 같은 index에 여러 메모리 주소가 매핑되면 덮어쓰기 충돌이 자주 발생
- 충돌을 줄이기 위한 다양한 기법들이 존재함

---

 캐시 설계에서 자주 나오는 키워드 요약

 용어  설명 
------------
 Index  캐시 내 위치를 찾기 위한 식별자 
 Tag  메모리 블록을 식별하기 위한 상위 비트 
 Hit  캐시에 원하는 데이터가 있음 
 Miss  캐시에 데이터가 없어 메모리에서 가져옴 
 Dirty Bit  캐시 내용이 메모리와 달라졌는지 여부 

---

  참고
- 현대 CPU (Intel AMD)는 대부분 L1: 48-way L2/L3: 820 way set-associative 사용
- Write-back  Write-allocate 구조를 기본 채택



---

 Page

- 가상메모리 생성시  물리 메모리(DRAM) 의 공간이 연속적으로 존재하는 보장이 없기 때문에 이 떨어진 공간들을 연속적이다 라고 인식하게 만드는 기법
- 페이지 테이블을 활용하여 연속적임을 보장한다(속인다).
- 페이지 테이블이 많아 읽는데 시간이 걸리는 것을 방지하기 위해 멀티레벨 페이지 테이블이 있다.
- TLB 라는 캐시를 통해 자주사용하는 테이블을 관리해서 접근 속도를 높힌다.

- 32bit OS 의 경우 가상메모리는 232 bit (4GB)
    - 페이지의 크기는 212 bit (4KB) 232 / 212  220 개의 페이지보관


---

 Exception (내부사건)

- CPU 내부에서 발생한 동기적 이벤트

    - Fault (재실행 가능한 예외)
        - 명령 실행 전 발생하는 예외로 고칠 수 있는 결함이다.
        - ex) 페이지 폴트 : 메모리 접근했는데 캐시에 페이지 없어서 미스 OS가 와서 처리해줌

    - Trap (알림 느낌)
        - 명령 실행은 정상적으로 끝남 끝나자마자 예외 발생
        - 복구 가능하며 다음 명령으로 점프한다.
        - ex) 디버깅용 중단점 (브레이크포인트)

    - Abort (되돌릴수 없어 ...)
        - 복구 불가한 심각한 오류
        - 시스템 구조 자체가 망가졌거나 예측 못함
        - ex) 스택 오버플로우 패리티오류

 Interrupt (외부사건)

- 외부에서 발생한 비동기적 신호 (네트워크 패킷 도착  타이머 키보드입력 등)

    - 하드웨어 인터럽트
        - 외부 입력 독립적

    - 소프트웨어 인터럽트
        - Trap 과 유사 명령어로 호출 제어 가능
        
    - NMI
        - Abort와 유사 치명적 상황 대응 용
