/*
문제 설명
아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.
이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법 중 
N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

제한사항
N은 1 이상 9 이하입니다.
number는 1 이상 32,000 이하입니다.
수식에는 괄호와 사칙연산만 가능하며 나누기 연산에서 나머지는 무시합니다.
최솟값이 8보다 크면 -1을 return 합니다.

입출력 예
N	number	return
5	12	4
2	11	3

입출력 예 설명
예제 #1
문제에 나온 예와 같습니다.

예제 #2
11 = 22 / 2와 같이 2를 3번만 사용하여 표현할 수 있습니다.

*/

/* ING */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

int solution(int N, int number) {
    // 최솟값이 8보다 크면 -1을 리턴하므로, 8개까지의 집합을 관리합니다.
    // s[i]는 N을 i번 사용하여 만들 수 있는 모든 숫자들의 집합입니다.
    vector<unordered_set<int>> s(9);

    // 1. 각 단계별로 'N을 연달아 붙인 수'를 기본값으로 넣습니다 (5, 55, 555...)
    int base_num = 0;
    for (int i = 1; i <= 8; ++i) {
        base_num = base_num * 10 + N;
        s[i].insert(base_num);
    }

    // 2. DP 진행: N을 k번 사용하는 경우 계산
    for (int k = 1; k <= 8; ++k) {
        // k를 만들기 위한 조합 (i개 사용한 결과) op (k-i개 사용한 결과)
        for (int i = 1; i < k; ++i) {
            for (int op1 : s[i]) {
                for (int op2 : s[k - i]) {
                    // 사칙연산 수행
                    s[k].insert(op1 + op2);
                    s[k].insert(op1 - op2);
                    s[k].insert(op1 * op2);
                    
                    // 0으로 나누기 방지
                    if (op2 != 0) {
                        s[k].insert(op1 / op2);
                    }
                }
            }
        }

        // 3. 현재 단계(k번 사용)에서 목표 숫자(number)를 찾았다면 바로 k 리턴
        // 처음 발견된 k가 무조건 최솟값입니다.
        if (s[k].find(number) != s[k].end()) {
            return k;
        }
    }

    // 8번까지 사용했는데도 찾지 못했다면 -1 리턴
    return -1;
}

// 테스트를 위한 메인 함수
int main() {
    cout << "예제 1 (N=5, num=12): " << solution(5, 12) << endl; // 결과: 4
    cout << "예제 2 (N=2, num=11): " << solution(2, 11) << endl; // 결과: 3
    return 0;
}