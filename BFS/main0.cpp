/* 문제 상황수빈이의 위치: $X$ (0 ~ 100,000)
동생의 위치: $K$ (0 ~ 100,000)
수빈이가 1초 동안 할 수 있는 행동 (3가지):
걷기: $X-1$ 로 이동
걷기: $X+1$ 로 이동
순간이동: $2 * X$ 로 이동
질문: 수빈이가 동생을 찾을 수 있는 **가장 빠른 시간(초)**은 몇 초인가? 
TC
1. N(5) K(17)       4           5->10->9->18->17
2. N(1) K(10)       4           1->2->4->5->10
3. N(10)K(10)       0           same
*/

#include <iostream>
#include <memory.h>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

void clearQueue(void);

int gField[100001];
queue<pair<int,int>> gOpers;

int solution(int _n, int _k)
{   
    int iAnswer = -1;
    memset(&gField, -1, sizeof(gField));
    
    int iCurrPos = _n;
    gOpers.push(make_pair(iCurrPos, 0U));

    while(!gOpers.empty())
    {
        auto [pos, cnt] = gOpers.front(); gOpers.pop();

        if (pos == _k)
        {
            iAnswer = cnt;
            break;
        }
        
        int nextPositions[3] = {pos + 1, pos - 1, pos * 2};

        for (int next : nextPositions) {
            if (next >= 0 && next <= 100000) {
                if (gField[next] == -1) {
                    gField[next] = pos; 
                    gOpers.push(make_pair(next, cnt + 1));
                }
            }
        }
    }
    clearQueue();
    
    if (iAnswer == 0 || iAnswer == -1)
    {
        cout << "Can't approach your sister";
    }
    else
    {
        int idx = _k;
        stack<int> stkHistory;
        stkHistory.push(idx);
        while(gField[idx] != _n)
        {
            stkHistory.push(gField[idx]);
            idx = gField[idx];
        }
        stkHistory.push(_n);
        while(!stkHistory.empty())
        {
            if (stkHistory.top() == _k)
            {
                cout << stkHistory.top();    
            }
            else
            {
                cout << stkHistory.top() << " -> ";
            }
            stkHistory.pop();
        }

    }

    cout << endl;
    return iAnswer;
}

void clearQueue(void)
{
    while (!gOpers.empty())
    {
        gOpers.pop();
    }
}

int main()
{
    int iTc1Ans = solution(5,17);
    int iTc2Ans = solution(1,10);
    int iTc3Ans = solution(10,10);
    int iTc4Ans = solution(0,10);

    return 0;
}
