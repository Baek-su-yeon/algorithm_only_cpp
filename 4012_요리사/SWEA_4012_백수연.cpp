#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::ios;
using std::abs;

int synergy[16][16]; // 최대 식재료 수만큼 만들어두기
int tastemin = 2147483647;

int calcultor(int cnt, int* group)
{
    int sum = 0;

    for (int i = 0; i < cnt; i++)
    {
        for (int j = 0; j < cnt; j++) sum += synergy[group[i]][group[j]];
    }

    return sum;
}


void choice(int N)
{
    int cnt = N / 2;
    int maxbit = pow(2, N) / 2; // {1, 2}, {3, 4}로 뽑힌거랑 {3, 4}, {1, 2}는 같은 조합이라서 반만 보기
    
    // 0부터 2**N - 1까지 비트 확인
    // N = 4이면 0000 ~ 1111까지 보는거이므로 0 ~ 15까지 보는거랑 똑같음
    for (int i = 0; i < maxbit; i++)
    {
        // 식재료 뽑기
        int bitcnt = __builtin_popcount(i); // 비트에 1의 개수 cpu 단에서 계산

        // 식재료 나누기
        if (bitcnt == cnt)
        {
            int A[8], B[8]; // 최대 재료수에 맞춰 선언
            int idxA = 0, idxB = 0; // 각 배열 인덱스 관리

            for (int j = 0; j < N; j++)
            {
                if (i & (1 << j)) A[idxA++] = j; // 비트가 1이면 A
                else B[idxB++] = j; // 비트가 0이면 B
            }

            int tasteA = calcultor(cnt, A);
            int tasteB = calcultor(cnt, B);

            if (tastemin > abs(tasteA - tasteB)) tastemin = abs(tasteA - tasteB);
        }

        bitcnt = 0;
    }
}

void solve (int tc)
{
    tastemin = 2147483647; // 초기화
    int N;
    cin >> N;

    // 시너지 입력 받기
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) cin >> synergy[i][j]; 
    }
    
    choice(N);

    cout << '#' << tc << ' ' << tastemin << '\n';
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++) {
        solve(i);
    }

    return 0;
}