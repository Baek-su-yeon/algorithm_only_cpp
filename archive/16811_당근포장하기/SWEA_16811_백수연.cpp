#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;
using std::min;
using std::max;

void solve(tc)
{
    int N;
    std::cin >> N

    vector<int> carrots(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> carrots[i];
    }

    // 1. 당근 크기 오름차순 정렬
    sort(carrots.begin(), carrots.end());

    int min_diff = 1001; // 최댓값으로 초기화 (N이 1000이므로)

    // 2. 두 개의 경계선(i, j)을 정해서 세 구간으로 나눔
    // i: 소 상자의 마지막 인덱스
    // j: 중 상자의 마지막 인덱스
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            
            // 조건 1: 같은 크기의 당근은 같은 상자에 있어야 함
            // 즉, 경계선 바로 다음 당근과 크기가 같으면 안 됨
            if (carrots[i] == carrots[i + 1]) continue;
            if (carrots[j] == carrots[j + 1]) continue;

            // 각 상자에 든 당근 개수 계산
            int small = i + 1;
            int medium = j - i;
            int large = N - 1 - j;

            // 조건 2: 한 상자에 N/2개를 초과하면 안 됨
            int limit = N / 2;
            if (small > limit || medium > limit || large > limit) continue;

            // 조건 3: 비어 있는 상자가 있으면 안 됨 (i, j 범위 설정으로 이미 보장됨)

            // 개수 차이의 최솟값 갱신
            int current_max = max({small, medium, large});
            int current_min = min({small, medium, large});
            int diff = current_max - current_min;

            if (diff < min_diff)
            {
                min_diff = diff;
            }
        }
    }

    // 3. 결과 출력 (포장할 수 없는 경우 -1)
    if (min_diff == 1001)
    {
        std::cout << "#" << tc << " -1" << std::endl;
    } 
    else
    {
        std::cout << "#" << tc << " " << min_diff << std::endl;
    }
}

int main ()
{
    // 입출력 최적화
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;

    for (int i = 1; i < T+1; i++)
    {
        solve(i);
    }

    return 0;
}