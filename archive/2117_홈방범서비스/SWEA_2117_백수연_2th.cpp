// 운영 비용 = 서비스 영역의 면적 = k*k+(k-1)*(k-1)
#include <iostream>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::vector;
using ::std::pair;
using ::std::abs;
using ::std::max;
using ::std::ios;

vector<pair<int, int>> homes;

int operate_cost (int k)
{
    return k * k + (k - 1) * (k - 1);
}

int distance_calculator (pair<int, int> center, pair<int, int> home)
{
    return abs(center.first - home.first) + abs(center.second - home.second);
}

int fine_homes (int r, int c, int k)
{
    int count = 0;

    for (const auto& home:homes)
    {
        int dist = distance_calculator({r, c}, home);
        if (dist < k) count++;   
    }

    return count;
}

void solve (int tc)
{   
    int N, M;
    cin >> N >> M;
    
    homes.clear();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int home;
            cin >> home;
            if (home) homes.push_back({i, j});   
        }
    }
    
    int result = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 1; k <= N + 1; k++)
            {
                int home_count = fine_homes(i, j, k);

                int cost = operate_cost(k);

                if (cost <= home_count * M) result = max(result, home_count);
            }
        }
    }

    cout << '#' << tc << ' ' << result << '\n';
    
    return;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}