#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;
using std::max;

// 전역 변수
int N; // 숫자 개수
int PLUS, MINUS, MUL, DIVIDE; // 각 연산자의 개수
vector<int> NUMBERS(N);
int MIN = 100000000;
int MAX = -100000000;

// 재귀를 이용한 완전탐색
void calculator (int idx, int sum)
{
    // 종료조건
    if (idx == N)
    {
        MIN = min(MIN, sum);
        MAX = max(MAX, sum);
        return;
    }
    
    // 연산자 따라서 계산
    if (PLUS > 0)
    {
        PLUS--;
        calculator (idx + 1, sum + NUMBERS[idx]);
        PLUS++;
    }
    if (MINUS > 0)
    {
        MINUS--;
        calculator (idx + 1, sum - NUMBERS[idx]);
        MINUS++;
    }
    if (MUL > 0)
    {
        MUL--;
        calculator (idx + 1, sum * NUMBERS[idx]);
        MUL++;
    }
    if (DIVIDE > 0)
    {
        DIVIDE--;
        calculator (idx + 1, sum / NUMBERS[idx]);
        DIVIDE++;
    }
}

// 문제 해결부
void solve (int tc)
{
    std::cin >> N;

    std::cin >> PLUS >> MINUS >> MUL >> DIVIDE;

    NUMBERS.resize(N);
    for (int i = 0; i < N; i++)
    {
        int num;
        std::cin >> num;
        NUMBERS[i] = num;
    }

    int sum = NUMBERS[0];
    calculator(1, sum);

    std::cout << '#' << tc << ' ' << MAX - MIN << '\n';

}


// 테스트 케이스 입력부
int main ()
{
    int T;
    std::cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);

        // 초기화
        MIN = 100000000;
        MAX = -100000000;
    }

    return 0;
}