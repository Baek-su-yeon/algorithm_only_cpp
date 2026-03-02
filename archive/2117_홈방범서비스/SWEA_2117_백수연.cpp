#include <iostream>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::vector;
using ::std::pair;
using ::std::abs;
using ::std::max;

struct Point {
    int r, c;
};

// 운영 비용 계산 함수: K*K + (K-1)*(K-1)
int calculate_cost(int k)
{
    return k * k + (k - 1) * (k - 1);
}

// 2. 맨해튼 거리 계산 함수: 마름모 영역 판단 기준
int get_manhattan_distance(Point p1, Point p2)
{
    return abs(p1.r - p2.r) + abs(p1.c - p2.c);
}

// 3. 특정 중심과 K 범위 내의 집 개수를 세는 함수
int count_houses(Point center, int k, const vector<Point>& houses)
{
    int count = 0;
    for (const auto& house : houses)
    {
        // 거리가 K보다 작아야 영역 안에 포함됨 (거리 < K는 영역 K를 의미)
        if (get_manhattan_distance(center, house) < k) count++;
    }
    return count;
}

// 4. 보안 회사가 손해를 보지 않는지 확인하는 함수
bool is_profitable(int house_count, int m, int cost)
{
    // 이익 = (집 개수 * 지불 비용) - 운영 비용 >= 0
    return (house_count * m) >= cost;
}

void solve (int tc)
{
    int N, M;
    cin >> N >> M;

    vector<Point> houses;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int val;
            cin >> val;
            if (val == 1) houses.push_back({i, j}); // 집 좌표 저장
        }
    }

    int result = 0;

    // 모든 칸을 마름모의 중심으로 시도
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Point center = {i, j};

            // K를 1부터 N+1까지 확장하며 탐색
            for (int k = 1; k <= N + 1; k++)
            {
                int current_houses = count_houses(center, k, houses);
                int current_cost = calculate_cost(k);

                if (is_profitable(current_houses, M, current_cost))
                {
                    result = max(result, current_houses);
                }
            }
        }
    }

    cout << "#" << tc << " " << result << "\n";

    return;
}

int main ()
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}