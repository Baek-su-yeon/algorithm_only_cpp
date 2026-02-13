#include <iostream>
#include <vector>

using std::vector;

int N; // 수식에 사용되는 숫자 개수
int PLUS, MINUS, MUL, DIVIDE; // 각 연산자의 개수
int MIN = 100000000;
int MAX = -100000000;

// 재귀로 돌아갈 함수
int calculater(int idx, int oper)
{
    // 종료 조건
    if (idx == N || oper == 0)
    {   
        
        return; 
    }
}

void solve (int tc)
{   
    std::cin >> N;
    std::cin >> PLUS >> MINUS >> MUL >> DIVIDE;

    vector<int> numbers(N);

    calculater(0);

    return;
}

int main ()
{
    int T;
    std::cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}