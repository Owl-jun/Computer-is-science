# 운영체제 - 최린 교수님 강의 정리

#### 목차
1. [OS Overview](#1-os-overview)
2. [Process](#2-process)
3. [Thread](#3-threads)
4. **[Mutual Exclusion and Synchronization](#4-mutual-exclusion-and-synchronization)**
5. [Deadlock and Starvation](#5-deadlock-and-starvation)
6. [Memory Management](#6-memory-management)
7. [Virtual Memory](#7-virtual-memory)
8. [Uniprocessor Scheduling](#8-scheduling)
9. [Multiprocessor and Realtime Scheduling](#9-multiprocessor-and-real-time-scheduling)
10. [IO](#10-io)
11. [File Management](#11-file-management)
12. [Virtual Machine]
---
### 1. OS Overview

- 1강(250515)
    - 디지털 시스템이 컴퓨터가 되기 위한 조건?
        ```txt
        " 조건 -> 계산 -> 판단을 할 수 있는 CPU 같은 장치가 존재하며 프로세싱이 가능해야한다. "
        " 상태 값을 가져야한다. "

        - 쉽게 설명해보기
        : 컴퓨팅 (연산, 상태값 저장 등을 하는 행위) 작업이 가능해야한다.
        즉, 사람처럼 어떠한 기준으로 판단을 할 수  있어야한다. 
        (조건에 따라 다른 동작을 할 수 있어야 한다)
        그걸 할 수 있게 해주는 것이 CPU 와 같은 장치이다.
        ```
    - 컴퓨터 시스템에서 OS란 무엇이냐?
        ```txt
        " 하드웨어 리소스를 쉽게 조작할 수 있도록 도움을 주고, "
        " 하드웨어와 유저레벨 사이에서 인터페이스를 제공해주는 것이다. "

        - 쉽게 설명해보기
        : 우리가 컴퓨터를 조작하기위해 본체를 뜯어서 전기신호를 직접 주지않고 
        키보드, 마우스 등의 입력, 출력 장치를 가지고 조작할 수 있는 이유이다.
        Windows , Linux , MacOS , UNIX 등이 있다.
        ```

- 2강(250516)
    - Compute vs I/O , CPU 가용률을 높혀라
        ```txt
        아래와 같이 Task가 있을 때,
        Task 1 : I/O 15us
        Task 2 : Compute 1us
        Task 3 : I/O 15us
        CPU 가동률은 1/31 ~=> 3.23%

        순차적 Task 실행은 값 비싼 CPU 를 너무 활용못하는게 아닐까?
        `멀티 태스킹`개념이 도입된 배경이다.
        ```

---
### 2. Process
- 2강(250516)
    - 프로세스란 ?
        ```txt
        " 프로그램의 인스턴스 "
        > 하나의 프로그램 (명령어와 데이터들의 뭉치) 을 기반으로 찍어낸 인스턴스이다.
        > 여러 프로세스가 실행 중이어도 각 프로세스는 자신이 단독으로 실행되는 것처럼 느낀다 (일루전).
        ```

    - Private Address Spaces
        ```txt
        프로세스가 가지는 주소공간 (가상 메모리)
        여기 있는 주소를 물리적 메모리(DRAM)의 주소로 변환하여 사용한다.
        이는 컴퓨터에 자기 혼자 존재하는것 같은 일루전을 제공한다.
        ```

    - Life vs scope
        ```txt
        이를 이해하기 위해서는 변수와 메모리구조에 대한 이해가 필요한데, SKIP하도록 하겠다.
        Life :  스택메모리에 저장된 변수들과 같이 지역변수가 스택이 해제되었을 때 소멸하는 등 
                변수의 생명주기를 뜻한다.
        scope : '생존한' 변수들에게 접근 가능한 영역범위, 예로, Func1 , Func2 두가지 영역이 있을 때,
                Func1 스택메모리 스코프를 가지고 있을 때, Func2 의 변수에 접근하지 못한다.

        Life 하지만 scope 가 불가능하다. 는 존재하지만
        Life 하지 않고 scope 가 가능하다는 말이 안됨.
        ```

    - **Context Swiching**
        ```txt
        Context : 프로세스가 실행되던 시점의 CPU 레지스터 값, 스택 포인터, 프로그램 카운터 등의 정보 집합

        어떠한 시스템콜에 의하여 실행중인 프로세스의 context를 저장하고 다른 프로세스를 cpu로 올리는 작업
        대표적으로 타임 스케쥴링기반으로 실행되는 컴퓨터에서 타임 인터럽트가 발생하는 순간, 
        혹은 IO작업 발생시
        실행중인 Context를 저장하고 다른 프로세스를 올리는 작업을 하게된다.
        ```

    - 시스템 콜, 그리고 커널 
        ```txt
        시스템 콜 : 사용자 프로그램이 커널 모드로 진입하기 위해 의도적으로 발생시키는 소프트웨어 인터럽트

        커널: 유저 모드에서 실행 중인 프로그램이 하드웨어에 직접 접근하지 못하게 막고, 
        그 요청을 대신 처리해주는 관리자.
        운영체제의 핵심이자, 하드웨어와 소프트웨어를 연결하는 다리 역할을 한다.
        ```

- 3강 (250517)
    - Process Control Block
        ```txt
        OS가 각 프로세스를 구분 및 관리하기위해 메모리에 저장하는 `데이터 구조체`
        하나의 프로세스는 하나의 PCB 를 가지며 커널영역 메모리에 저장된다.

        구성 정보는 아래와 같다.
        PID : 프로세스 고유번호
        state : 현재 프로세스의 상태 (ready, block ...)
        PC : 프로그램 카운터
        레지스터 : 연산 도중 보관해야할 레지스터 값들 (컨텍스트 스위칭 시 덮어씌워지니까)
        메모리 : 코드 데이터 스택 힙 등의 위치정보 (가상메모리 정보)
        I/O 상태 : 어떤 파일 및 입출력 장치를 사용하는가
        계정정보 : 유저ID , 권한 등
        우선순위 : 스케쥴링 시 사용
        ```

    - Dispatcher , Process Execution and Traces
        ```txt
        Dispatcher : 프로세스 간 전환(switch)을 담당하는 OS 구성요소
                     컨텍스트 스위칭 수행, 타이머 시작
                     스케쥴러가 다음 프로세스를 고른다면, 디스패쳐는 전환을 실제로 수행한다.
        Process Excecution : OS가 프로세스를 생성하고, 실행상태로 진입시키고, 종료하는 전체과정을 의미
                        예)  NEW -> READY -> RUNNING -> WAITING -> READY -> RUNNING -> TERMINATED
        Traces : 프로세스가 실행되는 동안 수행한 명령어 주소의 시퀀스 (흔적) 실행 로그와 같은 것으로 이해
        ```

    - Process Creation and Termination
        ```txt
        Process Creation : 새로운 프로세스를 생성하는 작업, 부모 프로세스가 자식 프로세스를 만들어
                           새로운 작업을 맡기는 형태로 이루어진다.
                           fork() 생성 -> exec() 다른 프로그램으로 덮어씀
        Termination : 실행이 끝나거나, 강제종료되는 상황. OS는 프로세스를 clean-up 해줘야함.
               흐름 : PCB 제거준비 -> 리소스 반납 -> state : ZOMBIE -> 부모가 wait() 호출

        흥미로운 점, 
            모든 프로세스는 부팅시 생성되는 조상 프로세스의 후손들이다, 모두가 이어져있다는 사실
        ```

    - fork
        ```txt 
        현재 실행 중인 프로세스를 복제해서, 똑같은 새 프로세스를 하나 더 만드는 시스템 콜

        사용하는 이유 ?
            병렬 작업 , 백그라운드 작업 분리 , exec()와 함께 새 프로그램 실행
        
        어떤 복사가 일어날까,
            Copy-on-Write(CoW) 기술 사용.
                처음엔 부모와 자식이 같은 메모리 페이지를 공유
                누군가 데이터를 변경할 때 깊은 복사가 일어남 -> 성능 최적화

        리턴값
        부모 프로세스 : 자식의 PID
        자식 프로세스 : 0
        실패          : -1
        ```

    - Five-State Process Model

        <img src="../img/OS0002.png" width=600>

        ```txt
        OS가 프로세스의 상태를 추적하고 관리하기 위해 사용하는 5가지 상태모델
        ```
    
    - Suspended Processes
        ```txt
        프로세스가 일시적으로 메모리에서 제거되고, 디스크로 스왑되어 대기 상태가 되는 것.
        Swapping : 메모리 부족으로 인해 프로세스를 메모리 밖으로 쫓아내는 작업

        메모리에 프로세스가 많이 올라와있으나, IO작업 등으로 인해 모든 프로세스가 
        block 상태가 되어 있다면 CPU는 띵가띵가 놀고있음, 효율을 위해 메모리 밖으로 쫓아내고
        새로운 프로세스를 들여온다.
        ```
    
    - **Two Suspend State (7-state Process Model)**
        
        <img src="../img/OS0001.png" width=600>

        ```txt
        이해 부족 부분 정리
        New -> Admit 상황 : 이는 물리적으로 메모리 공간이 있다 라는 의미가 아닌 그저 PCB 만들고 입장허용한 상태임.
        그래서 분기가 나뉘게 된다.
        1. 메모리 여유 : New -> Ready
        2. 메모리 부족 : New -> Suspended Ready

        Suspended Ready : 스케쥴러의 선택을 못받아 Ready 도중 메모리에서 쫓겨남
        Suspended Blocked : IO 요청 기다리다가 메모리에서 쫓겨남
        Running -> Suspended Ready : 실행 도중 kill() 혹은 메모리 부족으로 인해 쫓겨남 (심각한 상황)
        ```

    - **Interrupt / Exception**
        ```txt
        User Mode <-[Interrupt||Exception]-> Kernel Mode

        Interrupt : 외부적인 이벤트 (external , Asynchronous)
            #INT : 일반적인 인터럽트
            #NMI : None Maskable Interrupt -> 인터럽트가 disable 되어도 실행되는 인터럽트
            return to next

        Exception : 프로그램 실행 중에 예외가 발생 (internal , Synchronous)
            Faults  : 명령어를 마치지 못함(page miss ...)(의도적이지않음, Return to next)
            Traps   : 명령어를 마치고 발생(Debug, system call ...)(의도적임)
            Aborts  : 프로그램을 종료해야할 만큼 심각한 오류. (parity error...)
        
        인터럽트 / 예외 이벤트가 발생 → OS의 커널이 등록한 이벤트 핸들러(ISR)가 실행된다.
        이벤트(인터럽트)는 하드웨어/펌웨어에서 발생하지만,
        그 처리는 OS 커널이 수행하며, 핸들러 코드는 OS에 존재한다.
        
        즉, 이벤트는 하드웨어/펌웨어가 발생시키고, 핸들러는 커널에 있다.
        ```

- 4강 (250518)
    - UNIX System V Process Management

    <img src="../img/OS0003.jpg" width=700>

### 3. Threads
- 4강 (250518)
    - 들어가며
        ```txt
        기본적인 Thread : OS의 스레드

        하드웨어의 Thread(하이퍼스레딩 ...) 
            : ProgramCounter 가 두개, 독립적인 프로세스라 할 수 있음, OS의 스레드와 다르다. 
            : 간단히만 알고있자.
        ```

    - Multithreaded Process Model
        
        <img src="../img/OS0005.png" width=600>

    - 멀티 프로세싱 vs 멀티 스레딩
        <img src="../img/OS0006.png" width = 600>
        ```txt
        멀티 프로세싱
            각 프로세스별로 PCB 생성, 각각의 리소스,IO ... 자원이 모두 독립적임
            스케쥴링 단위가 프로세스임
            무겁고 복잡하다.
            하지만 성능 희생을 감수하고라도 격리성과 안정성이 필요한 곳에 쓸 수 있다.

        멀티 스레딩
            한 프로세스의 PCB를 공유, 리소스,IO ... 자원을 공유함
            스케쥴링 단위가 스레드가 되기 때문에
            스레드별 스레드컨트롤블락(스택포인터, 컨택스트정보, state저장)이 생김
            가볍고 효율적이다, 허나 공유 자원 접근에 대한 동기화 및 디버깅이 어려운 단점이 있다.
            위 그림에서 보이다 싶이, 하나의 운명 공동체 이다.

        컴퓨터세계의 방법론 중에서 무조건 이게 정답이다! 는 없다고 본다.
        상황에 맞추어 사용하기위해 둘 다 잘 알아놓자.
        ```


    - Process Characteristics
        ```txt
        Resource ownership : 리소스의 주체가 프로세스 단위임
        scheduling unit : 스케쥴링이 되는 단위 -> 기존 Process
        Two characteristics are independent
            : 스케쥴링 단위만 -> thread 단위로 (Lightweight process)
        ```
    
    - Multithreading
        ```txt
        멀티스레딩을 사용하는 이유

            빠른 응답
            병렬 처리
            효율적인 메모리, 리소스 공유
            성능 가성비가 좋다.

        멀티스레딩을 위해 필요한 것들

            thread execution state : Ready, Run
            thread context : 스레드 별 상태정보
            thread execution stack : 스레드 별 스택메모리 공간

        특징
            `스레드들은 하나의 운명 공동체` 이기 때문에
            Suspend 시 모든 스레드가 쫓겨남
            kill 시 모든 스레드가 좀비가 됨

        멀티스레딩 프로세스 예시

            Foreground and background jobs
            Asynchronous processing
            Batch processing
        ```

- 5강 (250519)
    - User Level Threads (ULTs)
        ```txt
        유저 레벨에서의 스레드, 멀티스레딩인척하는 눈속임이 아닐까?
            장점 
                Application 자체적으로 스케쥴을 한다. -> 커널진입이 없음으로 가볍다.
                맞춤형 스케쥴링이 가능하다.
                커널을 필요로하지 않기 때문에 어디서나 실행이 가능하다.
            단점
                프로세스가 Block 이 되면 모든 스레드가 Block이 된다.
                하나의 프로세스에서 하나의 프로세서만 이용가능하다.
                즉, 멀티 스레딩의 장점을 이용할 수 없다.
            왜 필요할까?
        ```

    - Kernel Level Threads (KLTs)
        ```txt
        OS 레벨에서의 스레드, 찐 스레드
            장점
                멀티 스레딩의 장점을 모두 이용가능하다.
            단점
                Context Switching 비용이 발생, 오버헤드가 ULT 보다 비교적 크다.
                스레드 생성/소멸 비용이 큼
                OS 스케줄러가 유저 의도대로 움직이지 않음 (맞춤 스케줄링 불가)

            왜 필요할까?
                멀티코어 활용이나 비동기 IO 처리 등의 상황에서
                병렬성 확보와 블로킹 회피를 위해 필요하다
        ```

    - Combined Approach
        ```txt
        ULT 와 KLT 의 장점을 모두 살리고싶은 욕심쟁이의 접근법

            여러 개의 ULT → 적은 수의 KLT에 매핑 (M:N)
            각 KLT가 여러 ULT를 감싸는 구조

        스레드 풀 개념과 유사한 점
            KLT 수 제한 → 스레드 풀처럼 자원 관리함
            내부에 유저 스레드들을 매핑해서 효율적으로 돌림
        ```
    
    - Performance Impact of Multicores
        ```txt
        암달의 법칙
            : 멀티 스레드 에서 병렬처리가 불가능한 직렬적인 작업들이 성능과 직결된다.
            
                1 / ((병렬 / 코어수) + (직렬 작업)) = 스피드업  
            
            즉, 병렬처리가 불가능한 직렬 작업(inherently serial)이 속도를 결정하는데 크게 기여한다.
        ```
    
    - Solaris 에서의 용어
        ```txt
        Process             : 프로세스
        User-level thread   : ULT
        Lightweight process : ULT 를 KLT 에 매핑 (Combined 접근)
        Kernel thread       : 매핑되지 않은 OS 커널 스레드
        ```

---

### 4. Mutual Exclusion and Synchronization
- 5강(250519)
    - Process Interaction
        ```txt
        Mutual exclusion 
            : 두 프로세스가 하나의 프린터를 필요로 할 때
            -> 원하지 않는 결과가 나올 수 있다.
            -> 한번에 한 프로세스만 접근할 수 있도록 크리티컬 섹션으로 보호해줘야한다.
            how ? 한 프로세스가 크리티컬 섹션에서 작업중일 때 컨텍스트 스위칭을 멈춘다면?
        Deadlock
            : 리소스 R1, R2가 둘다 있어야 작업이 가능할 때, 한명이 R1을 , 한명이 R2를 들고있는 상황
            -> 그 누구도 양보할 생각이 없음.
            -> 평생 기다림.
        Starvation
            : 인싸들이 계속 리소스를 사용해서 왕따 당하는 녀석에게 리소스가 들어오지 않는 상황
            -> 스케쥴러로 인해, 어떤 프로세스에게 리소스가 할당되지 않는 상황
        Race condition
            : 전역 데이터에 두 프로세스 이상 접근하여 서로 교차하여 실행되는 상황
            -> 예상하지 못한 결과가 나올 수 있다.
        ```

- 6강(250520)
    - Critical section
        ```txt
        하나의 리소스를 둘 이상의 스레드가 동시에 접근하면 문제가 생기므로, 
        "상호 배제(Mutual Exclusion)" 가 필요하다.

        이를 보장하는 영역이 바로 Critical Section

        어떻게 구현할까?
            : 인터럽트를 disable 하는 방식은 싱글 코어에선 유효할지 몰라도, 멀티스레딩 상황에선 성립하지않는다.
            , 또 CS 자체가 막히기 때문에 CPU 사용률 측면에서도 불리할 것이다. 그렇다면 어떻게 해결가능할까.
            -> 먼저 Atomic Operation을 알아야한다.
        ```
    
    - Atomic Operation
        ```txt
        "All or Nothing" 이라는 속성 덕분에 중간에 끼어들 수 없으므로 동기화에 적합.
        
        대표 예시:
            Test-and-Set
            Compare-and-Swap
            Fetch-and-Add

        2개이상의 명령어를 하나의 Atomic operation 으로 정의 해놓은 것.
        ```

    - HW Support for Mutex
        ```txt
        하드웨어단 에서 Special machine instructions 제공
            Test-and-set , fetch-and-add, compare-and-swap ... -> Atomic Operation
        Problem
            Busy Waiting : 계속해서 test-and-set , compare ... 연산을 하기 때문에 CPU 낭비가 생기는 현상
            Deadlock and Starvation can also happen ...
        ```
    
    - Critical Section by Compare-and-Swap , Exchange
        ```txt
        무한 루프 돌면서 lock 획득 경쟁하는 과정
        누군가 작업중이라면 lock state = 1
        작업이 끝난다면 lock state = 0

        state 가 0 일 때 경쟁중인 스레드중 하나가 락을 쥐고(1로 만들고) 작업을 진행한다.
        ```
        ```cpp
        bool CompareAndSwap(int* addr, int expected, int new_val) {
            if (*addr == expected) {
                *addr = new_val;
                return true;
            }
            return false;
        }
        ```

    - 특별한 명령어(Atomic Oper)의 장점과 단점
        ```txt
        장점
            멀티 프로세서 환경에서도 크리티컬 섹션 보장
            쉽고 간단하다.
            리소스 당 크리티컬 섹션을 부여할 수 있다.
        단점
            Busy-waiting
            Starvation 발생가능
            Deadlock 발생가능
        ```
    
    - Semaphore
        - 예시 흐름 T1 ~ T4 스레드 4개가 순차적으로 세마포어 진입

        | 시점 | 동작 | S 값 변화 | 대기 큐 | 설명 |
        |:----:|:----:|:---------:|:-------:|:----:|
        | 0 | Init | 1 | [] | 자원 1개 준비 |
        | 1 | T1 P() | 0 | [] | T1 실행 시작 |
        | 2 | T2 P() | -1 | [T2] | 자원 없음 → Block |
        | 3 | T3 P() | -2 | [T2, T3] | Block |
        | 4 | T4 P() | -3 | [T2, T3, T4] | Block |
        | 5 | T1 V() | -2 → -2 | [T3, T4] | T2 깨움 → 바로 실행, 값은 그대로 |
        | 6 | T2 V() | -1 → -1 | [T4] | T3 깨움 |
        | 7 | T3 V() | 0 | [] | T4 깨움 |
        | 8 | T4 V() | 1 | [] | 자원 반납 완료 |

        ```txt
        리소스 접근을 관리해주는 특별한 변수

        initialized operation
            : non-negative integer value

        V operation ("signal")
            : Increment the semaphore , wait Queue 에 스레드가 있다면 깨움
            : 분기 1. 레디큐에 스레드존재 -> 스레드 깨움 -> s++;
                   2. 레디큐가 비었음 -> s++;

        P operation ("wait")
            : Decrement the semaphore , 자원이 없다면 Block
            : 일단 s-- , s < 0 이라면 레디큐로 들어감.

        Type of semaphores
            Binary semaphore (Mutex 대용으로 사용가능)
                - Have a value of 0 or 1
                    0 (locked)
                    1 (unlocked)
            Counting semaphore
                - Can have an arbitrary resource count

            Strong semaphore
                - FIFO 보장 (큐 사용)
            Weak semaphore
                - 큐를 사용하지 않음
        ```

- 7강 (250521)
    - Producer/Consumer Problem
        ```txt
        프로듀서 - 공유 버퍼 - 컨슈머 구조
            공유 버퍼 동기화가 필요함. (크리티컬 섹션으로 보호)
            * 중요 : 버퍼가 비었을 때 컨슈머의 접근을 막아줘야함. (데드락 발생)

        흐름 설명 (의도):
            n : 세마포어 (버퍼에 남은 공간 or 아이템 개수 추적용)
            s : 크리티컬 섹션 보호용 (Mutex 역할)

        produce()
            wait(n)           // 자원이 남았는지 확인 (ex: 버퍼 공간)
            wait(s)           // 공유 버퍼 접근 진입 (mutex lock)
            append()          // 생산된 아이템 버퍼에 넣기
            signal(s)         // mutex unlock

        consume()
            wait(s)           // 공유 버퍼 접근
            take()            // 아이템 가져오기
            signal(s)         // unlock

            signal(n)         // 버퍼 공간 하나 확보됨
            consume()         // 실제 소비 처리

        n은 버퍼 공간 or 아이템 개수 추적용 세마포어
        s는 mutex 역할
        하지만 이런 방식은 데드락에 취약하고 복잡 
        -> 그래서 고수준 동기화 도구(모니터, 메시지 패싱)가 등장하게 됨
        ```
    
    - Monitor
        ```txt
        구성 요소:
            - Mutex lock          (상호배제)
            - Condition Variable  (조건 대기)
            - 대기 큐             (자동 관리)

        API:
            - cwait(c): 조건 만족할 때까지 대기 (wait)
            - csignal(c): 조건 만족됨을 알림 (notify)

        프로듀서:
            if (버퍼가 꽉참) 
                cwait(full)
            else 
                append()

        컨슈머:
            if (버퍼가 비었음)
                cwait(empty)
            else
                take()
        ```

    - Message Passing
        ```txt
        프로세스 간 통신(IPC) 모델

        제공 기능:
            1. Mutual exclusion (자원 동시 접근 방지)
            2. Synchronization  (타이밍 맞춤)
            3. Communication     (데이터 교환)

        메서드:
            send(dest, message)      // 메시지를 보냄
            receive(source, message) // 메시지를 받음
        ```

    - Synchronization
        ```txt
        [보내기 시점]

        - blocking send: 수신자가 준비될 때까지 기다림 (안전하지만 느림)
        - non-blocking send: 보내고 바로 리턴 (빠름, 실패 가능성 있음)

        [받기 시점]

        - blocking receive: 메시지 도착할 때까지 기다림
        - non-blocking receive: 수신 가능한 메시지가 있으면 바로 처리, 없으면 넘김
        ```


### 5. Deadlock and Starvation
- 8강(250522)
    - Deadlock
        ```txt
        실생활에서 데드락의 예시
            두가지 상황
                재사용 가능한 리소스(도로)를 사용할 때
                    사거리에서 모든 방향의 차가 앞으로 전진하려고 할 때.

                소비가 가능한 리소스(선물)를 사용할 때
                    친구와 서로 먼저 선물을 받으면 선물을 줘야지 하고 있을 때.
        
        ```
    
    - Deadlock 발생 조건
        ```txt
        Mutual exclusion
            하나의 자원은 오직 한 프로세스만 접근 가능
        Hold and wait
            하나의 자원을 가지고 또 다른 자원을 기다리고 있을 때
        No preemption
            누가 가진 자원을 뺏어갈 수 없을 때

        Circular wait
            프로세스들이 서로를 원형으로 기다림

            위 3가지가 모두 충족되어도 데드락은 발생하지 않는다, 허나 Circular Wait 이 발생하면
            데드락이 발생됨. 
        ```

    - 3 Approaches for Deadlocks(방지대책)
        ```txt
        Deadlock prevention
            Deadlock 발생 조건 중 하나 이상을 사전에 막음
                보수적, 자원 낭비 가능

        Deadlock avoidance
            Deadlock이 발생할 가능성이 있는 상황을 미리 피함
                시스템 상태 정보 필요
                    bankers's algorithm
                        자원 요청이 시스템의 안전 상태를 유지하는지 확인

        Deadlock detection
            Deadlock이 발생한 후 이를 탐지하고 해결
                가장 유연하지만 위험
        ```

- 9강 (250523)
    - Deadlock avoidance algorithm
        ```txt
        Banker's Algorithm 
            각 프로세스가 최대 요구량을 명시해야 함
            시스템이 안전 상태(safe state) 에서만 자원 할당
            안전 상태란: 모든 프로세스가 정상적으로 종료 가능한 자원 상태
        ```

    - Deadlock detection algorithm
        ```txt
        교착 상태가 이미 발생한 후, 이를 탐지하는 방법.

        Resource Allocation Graph (RAG) + Cycle Detection
            자원-프로세스 관계를 그래프로 나타냄
            사이클이 생기면 Deadlock 발생 가능성 있음
            다중 인스턴스 자원은 추가적인 탐지 알고리즘 필요


        ```

    - Deadlock Recovery
        ```txt
        1. 모든 교착 프로세스 강제 종료 (abort all)
        2. Checkpoint를 이용해 이전 상태로 복구 (rollback)
        3. 하나씩 프로세스 종료 → 교착 해소될 때까지 (successive abort)
        4. 하나씩 자원 강제 회수 (preemption)
        ```

    - Deining Philosophers Problem
        ```txt
        Deadlock과 Concurrency 문제를 설명하는 고전적 예제.
            N명의 철학자가 원형 테이블에 앉아 있음
            각 철학자 왼쪽과 오른쪽에 포크가 하나씩 있음 (총 N개)
            철학자는 생각 -> 먹기(양쪽 포크 필요)를 반복함

        모든 철학자가 동시에 왼쪽 포크를 집고 기다리면 교착 상태 발생
            비대칭 자원 요청 (짝수는 왼쪽→오른쪽, 홀수는 오른쪽→왼쪽)
            하나씩만 포크 들게 제한 (최대 N-1명만 식사 가능)
            Arbitrator(중재자) 프로세스를 둠
            tryLock 방식 사용 (자원 미확보 시 포기)
        ```

- 10강 (250524)
    - UNIX Concurrency Mechanisms
        - Signals
            ```txt
            - 기존: 예외(Exception)가 발생하면 프로세스는 무조건 terminate.
            - 개선: 유저가 signal handler를 등록하면, 해당 시그널을 받아 커스텀 처리 가능.

            예)
            SIGINT  (Ctrl+C)  
            SIGTERM (종료 요청)  
            SIGSEGV (잘못된 메모리 접근)

            → signal() 또는 sigaction() 함수로 핸들러 등록 가능
            ```

### 6. Memory Management

- 10강 (250524)
    - 용어 정리
        ```txt
        Frame   : 메인 메모리의 고정된 물리적 블록 (RAM 단위)
        Page    : 디스크(보조 저장장치)의 고정된 블록 (Swap-in/out 단위)
        Segment : 프로그램 구조적 단위: .text, .data, .bss, .heap, .stack 등

        Relocation  : 프로세스가 메모리에서 다른 위치로 이동될 수 있음 (ex. 스와핑 발생 시)
        Protection  : 각 메모리 영역에 대해 읽기/쓰기/실행 권한 설정 필요, Segmentation Fault는 protection 위반 시 발생
        Sharing     : 라이브러리 코드(.text) 등은 여러 프로세스가 공유 가능, 메모리 절약 + 중복 로딩 방지 효과
        ```
    
    - Memory Organization
        ```txt
        Logical organization
            - 프로그램이 모듈화되어 로딩됨 (예: 함수 단위, 라이브러리 단위)
            - 컴파일러/링커/로더 관점에서 관리
        Physical organization
            - DRAM, Flash, 캐시 등 하드웨어 관점에서 메모리 배치
        Memory management techniques involve
            - Paging : 고정 크기 단위로 메모리 관리
            - Segmentation : 의미 단위(코드, 데이터 등)로 분할 관리
            - Virtual Memory : 논리 주소 → 물리 주소 매핑 + 필요한 페이지만 메모리에 올림
        ```

- 11강 (250525)
    - 파티셔닝
        ```txt
        프로세스는 가상메모리를 사용하지만 실제 메모리 공간은 파티션으로 나뉘어져 공간이 할당된다.
        그 파티션 개 수 만큼 실행될 수 있는 전체 프로세스의 수가 결정된다.
        파티션보다 프로그램 사이즈가 더 클 때 오버레이(swap)가 적용된다.

        Internal fragmentation
            - Equal-Size 파티션일 때
            - 파티션 블록 안에 남는 공간을 칭함.
        
        Dynamic partitioning
            - Equal-Size 파티션을 사용하니 단점이 생각 보다 큼 (큰 파티션 내 작은 프로그램이 차지 -> 낭비)
            - 프로그램 사이즈에 맞춰서 동적 할당해줌
            - But, 파티션이 생성되었다가 사라지고를 반복하면서 빈 공간이 생기게 됨
            - 그것을 External fragmentation : 홀(hole) 이라 칭함.
            - 그 공간을 메우기위해 다시 정렬하는 과정을 Compaction(메모리를 한쪽으로 밀어붙여 hole을 제거) 이라 한다.
        ```
    
    - 페이징
        ```txt
        파티셔닝 vs Simple Paging vs 가상메모리
            : 파티셔닝은 전체가 통으로 메모리로 올라온다.
            : 심플 페이징은 페이지 단위로 잘라진게 모두 올라옴 
            : 가상메모리는 부분부분 올라온다.

        Paging (단일 레벨 페이징, 4MB 페이지 기준)
            [ 가상 주소 32비트 ]  
            = [ 10비트 페이지 번호 ] + [ 22비트 오프셋 (페이지하나의 크기)]  
            = [ 전체 중 몇 번째 페이지? ] + [ 그 페이지 내부 몇 번째 위치? ]

            - 페이지 오프셋 비트 수가 22비트 → 페이지 크기는 2^22 = 4MB
            - 페이지 번호 비트 수는 10비트 → 총 2^10 = 1024개의 페이지 존재
        ```

### 7. Virtual Memory

- 11강 (250525)
    - 맛보기
        ```txt
        가상 메모리를 이해하기 위해서 짚고 넘어갈 내용

        Locality principle
            - Spatial Locality : 한번 Acces 된 주소는 근처 주소를 참조할 확률이 높다 -> 한번에 근처 블록까지 가져오기
            - Temporal Locality : 같은 참조가 여러번 일어날 확률이 높다 (캐싱)

        Memory Hierarchy
            속도 vs 용량 트레이드 오프 (용량이 작을 수록, CPU와 가까울수록 속도가 빠름)
            - 레지스터
            - Cache L1  hit 96%
            - Cache L2  hit 99%
            - Cache L3  hit 99.9%
            - DRAM      hit 99.99999%
            - SSD       
            - CLOUD ...
        ```

- 12강 (250526)
    - Cache
        ```txt

        Fully Associative Cache
            정의: 메모리의 어떤 블록이든 캐시의 모든 라인에 저장 가능
            주소 구성: [Tag | Offset] (Index 없음)
            장점: 캐시 활용도 극대화 (Miss 최소화)
            단점: 비교 대상이 많아서 비용↑, 구현 복잡↑
            용도: 소규모 고성능 캐시에 적합 (예: TLB)

        Direct Mapped Cache
            정의: 메모리 블록이 딱 하나의 캐시 라인에만 매핑됨
            주소 구성: [Tag | Index | Offset]
            장점: 단순하고 빠름
            단점: **충돌(Collision)**이 잦음 → 서로 다른 블록이 같은 캐시 라인에 자꾸 덮어씀
            주의: 성능 안 나올 수 있음 (빈도 높은 데이터끼리 충돌 시)

        Set Associative Cache
            정의: 캐시를 여러 Set으로 나누고, 각 Set 내에서 Fully Associative 구조를 가짐
            (예: 4-way set associative → 각 Set에 4개의 블록 저장 가능)
            주소 구성: [Tag | Set Index | Offset]
            장점: 충돌 줄이면서도 비교 비용을 완전연관보다 줄임
            트레이드오프: 구현 난이도, 비교 비용

        ---
        Cache Block Replacement
            캐시가 꽉 찼을 때, 어떤 블록을 내보낼지 정하는 전략
            LRU (Least Recently Used): 가장 오래 안 쓰인 블록 교체 → 현실적이지만 구현 복잡
            FIFO (First In First Out): 먼저 들어온 놈부터 제거 → 구현 간단
            Random: 랜덤하게 제거 → 구현 가장 간단, 하지만 성능 예측 어려움
            LFU (Least Frequently Used): 가장 적게 사용된 블록 제거 → 캐시 특성상 잘 안 씀

        ---
        3+1 Types of Cache Misses
            캐시가 해당 데이터를 갖고 있지 않아 메모리 접근이 발생하는 경우

            1. Compulsory Miss (필연적 미스)
            처음 보는 블록 → 아직 캐시에 없음
            aka Cold Miss
            2. Capacity Miss (용량 부족 미스)
            캐시 용량이 작아서 블록을 다 담지 못할 때 발생
            3. Conflict Miss (충돌 미스)
            서로 다른 블록이 같은 캐시 라인/셋에 매핑되면서 덮어씌워지는 경우
            (→ 주로 Direct Mapped / 낮은 Set 수에서 자주 발생)
            (+1) Coherence Miss (일관성 미스)
            멀티코어 환경에서 다른 프로세서가 캐시를 무효화한 경우 발생
            → MESI 등 캐시 일관성 프로토콜과 연관

            소프트웨어 캐시도 결국은 "데이터를 빠르게 접근하기 위한 계층적 메모리 설계" 이다.
            하드웨어 캐시의 설계 원리는 곧 소프트웨어 캐시의 성능 튜닝 바이블이다.
        ```

- 13강 (250527)

    - Virtual Memory
        ```txt
        실제 프로그램이 캐시,ram,disk 어디에 있던 프로그래머가 신경 안써도 되게끔
        해주는 가상메모리.

        이로인해 프로그래머는 레지스터와 가상메모리만 신경쓰면 된다.

        Memory allocation (Placement)
            - 어떤 프레임이던 가상메모리에 올라올 수 있다.
        Memory deallocation (Replacement)
            - LRU , Clock algorithm (어떤 프레임을 쫓아낼 것인가)
        Memory mapping (Translation)
            - 가상페이지 <-> 실제저장소 매핑
        ```

    - TLB (MMU)
        ```txt
        페이지 테이블 캐시
        Translation Lookaside Buffer

        역할
            CPU가 가상 주소 → 물리 주소 변환할 때
            매번 RAM의 페이지 테이블을 참조하면 느림

            그래서 자주 쓰는 매핑은 TLB (작은 캐시)에 저장해두고
            거기서 먼저 찾아본다 (캐시 히트)

            | 구성 요소                    | 역할         |
            | -----------------------------| ------------ |
            | 가상 페이지 번호             | 입력 (key)   |
            | 물리 프레임 번호             | 출력 (value) |
            | valid bit, protection bit 등 | 메타 정보    |

        [프로그램 실행]
            → 주소 참조 (0xABCD...)

            → MMU가 TLB 먼저 참조
                ↳ TLB Hit → 바로 물리주소 반환
                ↳ TLB Miss → 페이지 테이블 참조
                    ↳ 없다 → Page Fault → 디스크에서 로딩
                    ↳ 있다 → 물리주소 반환

            → 해당 페이지가 없으면 → Page Fault → RAM에 올려야 함
                ↳ RAM이 꽉 참 → Victim page 골라서 쫓아냄 (LRU, Clock 등)

        ```

- 14강 (250528)
    - Page Size
        ```txt
        페이지 크기 설정은 트레이드오프다.

            작은 페이지의 장점
                내부 단편화 감소: 실제 필요한 메모리 크기와 유사
                더 정밀한 페이지 교체 가능
            작은 페이지의 단점
                페이지 테이블 크기 증가
                관리 오버헤드 증가
            큰 페이지의 장점
                페이지 테이블 작아짐
                디스크 I/O 효율 증가
            큰 페이지의 단점
                내부 단편화 증가
                불필요한 데이터까지 메모리에 올릴 가능성

            적정 페이지 크기 선택은 하드웨어 특성과 응용의 메모리 접근 패턴에 따라 결정됨
        ```
    - Segment Organization
        ```txt
        세그먼트 = 논리적 단위 (코드, 데이터, 스택)
        → 주소 공간을 논리 단위로 분리하고, 각기 다른 보호 및 크기 설정 가능

        각 세그먼트는 **베이스(시작 주소)**와 **리미트(길이)**로 관리됨
        논리 주소 = (세그먼트 번호, 오프셋) → 물리 주소 = 베이스 + 오프셋
        장점:
            메모리 보호 용이
            코드 공유 및 동적 로딩에 유리
        단점:
            외부 단편화 발생 가능
            다소 복잡한 메모리 관리
        ```
    - Virtual Memory Policies
        ```txt
        가상 메모리에서의 교체 정책, 페이지 로딩 방식, 쓰기 정책 등

        1. Page Fetch Policy
            Demand Paging (지연 적재): 필요할 때만 페이지를 메모리에 로드
            Prepaging (사전 적재): 근접한 미래에 필요할 페이지를 미리 로드

        2. Replacement Policy
            FIFO, LRU, Clock, Optimal
            현실에선 LRU 근사 알고리즘(Clock, Aging 등)이 주로 사용됨

        3. Cleaning Policy
            Demand Cleaning: 쓸 때만 디스크에 쓰기
            Precleaning: 미리 백그라운드에서 dirty page를 디스크에 기록
        ```

    - Combined Examples
        ```txt
        페이징 + 세그먼트 + 가상 메모리 정책이 실제로 어떻게 결합되어 동작하는가 예시

        예) x86 아키텍처:
            세그먼트 → 페이징 → 물리 주소 순서로 메모리 접근
            즉, 세그먼트 테이블 → 페이지 테이블 → 메모리
        정책 결합 사례:
            LRU 기반 페이지 교체 + 사전 적재 + 세그먼트 보호
            실제 시스템은 트레이드오프를 기반으로 적절한 정책을 혼합
        ```

    - Page Buffering
        ```txt
        페이지 교체 시 교체된 페이지를 바로 버리지 않고 임시 저장하는 방식

        Page Buffering 목적
            최근 제거된 페이지를 버퍼에 보관 → 다시 필요할 경우 빠르게 복구
            디스크 I/O 횟수 최소화
        전략:
            Free page list, Modified page list 등으로 분리 관리
            자주 접근되는 페이지는 재활용 기회 제공
        ```

- 15강 (250530)

    - Working Set Managerment
        ```txt
        OS는 무조건 얼만큼의 페이지를 가져올지 결정해야한다.

        방법
            Fixed allocation
                프로세스당 고정된 수의 프레임을 할당한다.

            Variable allocation
                프로세스에 맞춘 크기의 프레임을 할당한다.
        ```

    - Replacement Scope
        ```txt
        Local Scope
            Fixed Allocation
            : 할당이 적으면 페이지 폴트가 증가하고, 너무 크면 남는 공간이 커진다.
            Variable Allocation
            : 시작은 작게, 점점 필요한 만큼 increase 하는 전략

        Global Scope
            Variable Allocation
            : 폴트가 발생하는 프로세스의 크기를 점점 키워줌.
        ```

### 8. Scheduling

- Scheduling
    ```txt
    시스템 리소스를 할당하는 행위

    3 - types of processor scheduling
        Long-term scheduling(admission scheduler)
            : 새 프로세스를 시스템에 admit 해 줄 것인가?
        
        Mid-term scheduling(Swapper)
            : swap-in , out 담당

        Short-term scheduling(Dispatcher)
            : CPU 할당 담당
    
    그렇다면 Long-term은 디스크의 프로그램을 들일지 말지 결정하고 (Admit)
    mid-term 스케쥴링이 admit 된 프로세스를 메모리에 올려놓고 (Ready or Block + Suspened)
    디스패쳐가 실제 실행을 결정하겠군 (Running)
    ```


- Fair-Share Scheduling
    ```txt
    프로세스A , 프로세스B가 있을 때,
    A는 스레드가 총 10개 , B는 1개를 사용하고있다.
    그렇다면 A에게는 스케쥴링 기회를 좀 적게, B에게는 많이 주어서
    균등한 스케쥴링을 위한 우선순위 할당을 목표로 한다;.
    ```

### 9. Multiprocessor and Real-Time Scheduling

- 16강 (250601)

    - Classification of Multiprocessors
        ```txt
        Shared-Memory Multiprocessors
            : 일반적인 개인용 컴퓨터
        Distributed - Memory Multiprocessors
            : 슈퍼 컴퓨터 , 컴퓨터들의 집단(군)
        Heterogeneous Multiprocessors 
            : 모바일 등 휴대폰에 들어가는 프로세서
        ```
    
    - Parallelism and Synchronization Granularity
        |Grain Size|Description|Synchronization Interval|
        |:--:|:--:|:--:|
        |Fine|Parallelism inherent in a single instruction stream|< 20|
        |**Medium**|Parallel processing or multitasking within a single application|20-200|
        |Coarse|Multiprocessing of concurrent processes in a multiprogramming environment|200-2000|
        |Very Coarse|Distributed processing across network nodes to form a single computing environment|2000-1M|
        |Independent|Multiple unrelated processes|not applicable|

- 17강 (250603)

    - Various Secheduling Policies
        ```txt
        FCFS
            : 선입선출
            : 스로풋 -> 낮을 수 있다. (1빠따가 선점 후 Job을 안끝내는 경우)
            : 리스폰타임 -> 오래 걸림. (하나씩 줄서서 앞에사람 끝날때까지 기다려야하니까)

        Round robin
            : 타임퀀텀을 기반으로 균등하게 실행 시켜 주는 것
            : 스로풋 -> 일반적으론 괜찮, 퀀텀이 짧으면 안좋을수 있음
            : 리스폰타임 -> Good

        SPN (Shortest Job First)
            : 짦은 Job 부터 먼저하렴, 일단 실행 중이면 도중에 못바꿈(Non-Preemtive)
            : 스로풋 -> Good
            : 리스폰타임 -> Good
            : 오버헤드가 좀 있으며, 긴 Job 은 스타베이션 걸릴 위험

        SRT (Shortes Remaining Time)
            : 더 짧은 Job이 들어오면 다른 Job이 실행중이어도 즉시 바꿔치기 (Preemtive)
            : 스로풋 -> Good
            : 리스폰타임 -> Good
            : 오버헤드 -> 큼 , 스타베이션 위험
        
        HRRN
            : Non-Preemtive
            : SRT 의 스타베이션 문제를 해결하기 위해 구현됨
            : Good balance

        Feedback
            : Multilevel feedback queue
        ```

- 18강 (250609)

    - Thread Scheduling
        ```txt
        Approach

        ✅ 1. Load Sharing (or Load Balancing)
            스레드들을 전체 CPU에 자유롭게 분배하는 방식
            핵심 개념: CPU 간 작업량이 균등하게 되도록 하는 전역 큐 구조
            모든 CPU가 같은 ready queue를 공유하며, 빈 CPU는 아무 작업이나 뽑아 처리
            📌 장점: 유휴 CPU가 줄고, 시스템 전체 부하가 균등
            ⚠️ 단점: 캐시 미스 증가 (thread migration 발생), lock contention 심화 가능
            예시: "나 CPU0에서 돌다가 CPU2에서 이어서 돌자!" → context migration

        ✅ 2. Dedicated Processor Assignment
            프로세스를 특정 CPU에 고정해 할당하는 방식
            각 프로세스 또는 스레드에 고정된 CPU를 지정
            **캐시 적중률(Cache Locality)**이 높음 → 성능 좋음
            📌 장점: context 이동 없음, 캐시 일관성 확보
            ⚠️ 단점: 특정 CPU가 과부하되면 부하 불균형 발생 가능
            SMP 구조에서 CPU affinity (CPU 고정 실행)로 구현되는 방식

        ✅ 3. Dynamic Scheduling (or Adaptive, Hybrid)
            로드 상태와 시스템 상황을 모니터링하여, 유동적으로 CPU에 배정
            현재 시스템 부하, 우선순위, 캐시 정보 등을 고려해 스마트한 스케줄링
            대부분의 최신 OS가 이 전략을 사용함
            📌 장점: 캐시 적중률 + 부하 균형 모두 고려한 절충안
            ⚠️ 단점: 구현 복잡, 정책 튜닝 어려움
            예시: Windows, Linux의 CFS(Completely Fair Scheduler) 등

        ✅ 4. Gang Scheduling
            여러 개의 관련 스레드(또는 프로세스)를 하나의 그룹(gang)으로 묶어 동시에 스케줄링
            "스레드 묶음 단위로 CPU 자원을 동시에 할당"
            보통 병렬 프로그램에서 사용 (OpenMP, MPI 등에서 등장)
            모든 스레드가 같은 시간 슬롯(time slice) 동안 실행됨
            📌 장점:
                통신/동기화 지연 최소화
                스레드 간 진행률 불균형 해결
                병렬성 보장
            ⚠️ 단점:
                자원 낭비 가능 (일부 스레드가 유휴 상태일 때도 전체 gang이 실행됨)
                멀티코어 자원 배분 비효율
                예시: 게임의 렌더링 엔진에서, 4개의 연산 스레드가 같이 스케줄링되어야 한다면 Gang이 적합
        ✅ 5. Co-Scheduling (Peer Scheduling 포함)
            서로 협력하거나 동기화가 필요한 스레드들끼리 같은 시간에 스케줄링
            Gang Scheduling의 느슨한 형태
            반드시 "모든 스레드를 동시에" 실행하지 않아도 됨 (조율만 함)
            협력적 태스크 간의 지연 방지 목적
            📌 Peer Scheduling은 Co-Scheduling의 하위 개념으로,
            특정 peer(짝) 스레드들과 동기화가 필요한 시점에서만 동시 실행되도록 맞추는 기법.
            📌 장점:
                Gang보다 유연함
                통신 비용 줄이면서 효율 증가
            ⚠️ 단점:
                스케줄러 설계 복잡
                정확한 동기 타이밍 계산 필요
        ```

- 19강 (250610)
    - Real-Time System
        ```txt
        정의: 
            작업의 정확한 결과뿐 아니라, 결과를 **정해진 시간 안에** 내는 것이 중요한 시스템
            일반 OS와 달리 "언제 끝났느냐"가 성공/실패 판단 기준이 됨

            예시: 
                - 항공기 제어 시스템
                - 의료기기(심장 박동기)
                - 자동차 ABS
                - 산업용 로봇 제어
                - 온라인 게임 서버의 물리 연산 처리

            종류:
            | **Hard Real-Time** | 마감 시간 초과 → 시스템 실패 | 항공 제어, 핵발전소 |
            | **Soft Real-Time** | 마감 초과 허용, 품질만 저하 | 영상 스트리밍, 온라인 게임 |
            | **Firm Real-Time** | 결과는 무시되지만 시스템은 계속 작동 | 센서 데이터, 일부 금융 시스템 |

            특징:
                - 우선순위 기반 스케줄링 지원
                - 지연 시간(Latency) 최소화
                - 시간 결정성(Determinism) 중요
                - 일반 OS와 달리 Throughput보다 Deadline을 중시
                - Interrupt, Preemption, Timer, Task Deadline 기능이 강화됨

            알고리즘:
                📌 Rate Monotonic Scheduling (RMS)
                    - **짧은 주기의 작업에 높은 우선순위 부여**
                    - 고정 우선순위
                    - CPU Utilization ≤ 69% 보장

                📌 Earliest Deadline First (EDF)
                    - **가장 마감기한이 가까운 작업부터 수행**
                    - 동적 우선순위
                    - CPU 이용률 100%까지 이론적 보장

            일반 OS vs Real-Time OS
            | 항목 | 일반 OS (Linux, Windows) | RTOS (VxWorks, FreeRTOS) |
            |------|---------------------------|---------------------------|
            | 목적 | 사용자 편의, 다양한 기능 | 정확한 시간 응답 |
            | 스케줄링 | Round-Robin, CFS 등 | RMS, EDF 등 |
            | 응답 시간 | 예측 불가 | 예측 가능 (Deterministic) |
            | 신뢰성 | 상대적 낮음 | 매우 높음 |
            | 예시 | 데스크탑, 서버 | 로봇, 임베디드 기기 |

            실제 응용
            - 게임 서버: 
                - Soft Real-Time 성격  
                - TPS / 프레임 동기화 / 클라이언트 위치 처리

            - 임베디드 IoT 장비:
                - FreeRTOS, RTEMS 등 사용  
                - 센서 입력 → 일정 시간 내 처리 → 하드웨어 응답


            심화 포인트

            - `Timer Interrupt` 기반의 Task Preemption
            - RTOS에서는 `malloc`, `new` 금지하는 경우도 많음 → `Static Allocation` 권장
            - `Priority Inversion` 문제 및 **Priority Inheritance Protocol** 필요


            기억할 것

            실시간 시스템에서는 "정확한 결과"보다 "**정해진 시간 안의 결과**"가 더 중요하다.
        ```

### 10. I/O

- 20강 (250611)
    - IO , Buffering
        ```txt
        1. I/O 개념
            정의
                I/O는 컴퓨터가 외부 장치와 데이터를 주고받는 작업.
                OS는 이걸 효율적으로 관리해야 시스템 성능이 보장됨.

        2. I/O Buffering: 왜 필요한가?
            개념
                “요청이 들어오기 전에 데이터를 미리 읽어두자.”

                디스크나 네트워크처럼 느린 장치에서 데이터를 읽을 때,
                CPU가 놀지 않게 하려면 **중간 메모리 공간(buffer)**을 활용해야 함.

            목적
                입출력 속도차 보완
                    CPU는 빠른데, I/O 장치는 느리니까 중간 완충 역할

                연속적인 처리 가능
                    I/O 요청이 끝나길 기다리지 않고 다음 연산 준비 가능

        Perform data transfers in advance of requests

        Block-oriented device
            고정 크기의 블록단위로 I/O 처리 : HDD, SDD 등

        Stream-oriented device
            바이트 단위로 연속적인 스트림 처리 : 키보드, 마우스, 마이크 ...


        I/O Buffering Schemes
            Single Buffer
                메모리에 하나의 버퍼만 사용
                데이터가 채워질 때까지 CPU 대기

            Double Buffer
                버퍼 2개를 번갈아 사용
                한쪽은 OS가 읽는 중, 다른 한쪽은 장치가 채우는 중
                CPU와 장치가 동시에 일함 → 성능 향상

            Circular Buffer (Ring Buffer)
                버퍼를 원형 구조로 만들어 다수의 버퍼 공간을 순환 사용
                실시간 처리 시스템이나 네트워크 통신에 많이 쓰임
        ```

- 21강 (250612)
    - Disk Scheduling Algorithms
        ```txt
        디스크 I/O 요청은 CPU보다 수천 배 느리기 때문에, 
        효율적인 스케줄링이 시스템 성능에 큰 영향을 미침.
        주 목적: 헤드 이동 거리 최소화 → 탐색 시간 최소화
        알고리즘
            FCFS : 도착 순서대로 처리
            SSTF : 현재 위치에서 가장 가까운 요청 먼저
            SCAN (전통적 전철 스캔 방식) : 한 방향으로 끝까지 이동하며 요청 처리, 끝 도달 후 반대방향
            LOOK : SCAN과 유사하나 끝까지 안 가고 마지막 요청까지만 이동
            C-SCAN (Circular SCAN) : 한 방향으로만 진행, 끝 도달 시 시작으로 점프
            C-LOOK : LOOK + C-SCAN: 마지막 요청까지만 진행 후 처음 요청으로 점프
        ```
    
    - RAID
        ```txt
        여러 개의 디스크를 조합하여 성능과 신뢰성을 동시에 향상시키는 기술
        ```
    | RAID Level        | 방식               | 장점          | 단점                 |
    | ----------------- | ---------------- | ----------- | ------------------ |
    | **RAID 0**        | 스트라이핑 (striping) | 성능 ↑        | **복구 불가**, 장애 허용 X |
    | **RAID 1**        | 미러링 (mirroring)  | 안정성 ↑       | 디스크 2배 필요          |
    | **RAID 5**        | 블록 + 패리티 (분산 저장) | 성능+안정성 절충   | 패리티 연산 → 쓰기 성능 ↓   |
    | **RAID 6**        | RAID 5 + 이중 패리티  | 이중 장애 대비 가능 | 성능, 복잡도 ↑          |
    | **RAID 10 (1+0)** | 미러링 + 스트라이핑      | 성능+복구 모두 ↑  | 고비용 구조             |


### 11. File Management 
- 22강 (250613)

    🔹 1. 파일 시스템의 기본 개념
    파일(File): 연관된 데이터의 모음. OS는 파일 단위로 데이터를 관리한다.

    파일 속성

    이름(name)

    식별자(identifier): 시스템 내부 식별용

    위치(location)

    크기(size)

    보호 정보(protection): 접근 권한

    시간 정보(times): 생성/수정/접근 시각 등

    🔹 2. 파일 연산 (File Operations)
    연산	설명
    create	새 파일 생성
    write	파일에 데이터 쓰기
    read	파일에서 데이터 읽기
    reposition	파일 오프셋 이동 (seek)
    delete	파일 삭제
    truncate	파일 내용 삭제하고 크기 0으로

    🔹 3. 파일 접근 방식
    Sequential Access: 앞에서부터 차례대로 읽고/쓰기 (ex. 텍스트 파일)

    Direct Access: 특정 위치로 점프 가능 (ex. DB파일)

    Indexed Access: 인덱스를 통해 접근 (ex. inode 기반 시스템)

    🔹 4. 디렉토리 구조
    Single-level Directory: 한 디렉토리에 모든 파일

    Two-level Directory: 사용자별 하위 디렉토리 존재

    Tree-structured Directory: 계층적 구조 (일반적)

    Acyclic Graph Directory: 파일 공유 허용 (하드 링크 등)

    General Graph Directory: 순환 가능 (소프트 링크)

    🔹 5. 파일 시스템 구현
    ✔️ 파일 제어 블록 (FCB: File Control Block)
    각 파일에 대한 메타데이터 저장

    파일 위치, 접근 권한, 소유자, 크기 등

    ✔️ OS 내부 자료구조
    Open File Table (시스템 전체)

    Per-process Open File Table (프로세스마다)

    fd (file descriptor) → 해당 테이블의 인덱스

    🔹 6. 저장공간 할당 방식
    방식	특징	장점	단점
    Contiguous Allocation	연속된 공간	빠른 접근	단편화, 파일 크기 예측 필요
    Linked Allocation	각 블록이 다음 포인터	단편화 없음	느린 접근
    Indexed Allocation	인덱스 블록 사용	빠른 접근, 유연함	인덱스 블록 오버헤드

    🔹 7. 자유 공간 관리 (Free Space Management)
    Bit Map: 비트로 블록 상태 저장

    Linked List: 사용 가능한 블록 연결

    Grouping: N개 묶어 리스트 형태

    Counting: 연속된 블록의 수까지 저장

    🔹 8. 디렉토리 구현
    선형 리스트: 간단하지만 느림

    해시 테이블: 빠른 검색

    🔹 9. 파일 공유 및 보호
    공유 방법: 하드링크, 소프트링크

    보호 기법: 접근 권한(읽기/쓰기/실행), ACL, 사용자/그룹/기타 구분

    🔹 10. 파일 시스템 예시
    UNIX의 inode 구조

    Windows NTFS

    보안, 저널링 지원

    FAT32, ext4: 각각의 설계 목적과 성능 차이 있음

