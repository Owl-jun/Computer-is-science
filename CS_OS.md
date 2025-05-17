# 운영체제 - 최린 교수님 강의 정리

#### 목차
1. OS Overview
2. Process
3. Thread
4. Mutual Exclusion and Synchronization
5. Deadlock and Starvation
6. Memory Management
7. Virtual Memory
8. Uniprocessor Scheduling
9. Multiprocessor and Realtime Scheduling
10. IO
11. File Management
12. Virtual Machine
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
        ```

    - Dispatcher , Process Execution and Traces
        ```txt
        ```

    - Process Creation and Termination
        ```txt
        ```

    - fork
        ```txt 
        ```

    - Five-State Process Model
        ```txt
        ```
    
    - Suspended Processes
        ```txt
        Swapping : 
        ```
    
    - **Two Suspend State (7-state Process Model)**
        
        <img src="." width=600>

        ```txt
        ```

    - **Interrupt / Exception**
        ```txt
        Interrupt : 외부적인 이벤트 (external , Asynchronous)
            키보드 input , 전원버튼 누르기 등등 ...
        Exception : 프로그램 실행 중에 예외가 발생 (internal , Synchronous)
            Faults  : 명령어를 마치지 못함(page miss)
            Traps   : 명령어를 마치고 발생(Debug, system call)
            Aborts  : 프로그램을 종료해야할 만큼 심각한 오류.
        
        인터럽트 / 익셉션 이벤트가 발생 -> 이벤트 핸들러 실행됨 (OS보단 펌웨어에 가까운 개념)
        ```