#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> grid(N, vector<int>(M));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> grid[i][j];
        }
    }

    int max_len = 0;

    // 1. 가로 직선 확인 (각 행별로 연속된 1의 개수 세기)
    for (int i = 0; i < N; i++)
    {
        int current_len = 0;
        for (int j = 0; j < M; j++)
        {
            if (grid[i][j] == 1)
            {
                current_len++;
            }
            else
            {
                if (current_len >= 2)
                {
                    max_len = max(max_len, current_len);
                }
                current_len = 0;
            }
        }
        if (current_len >= 2) max_len = max(max_len, current_len);
    }

    // 2. 세로 직선 확인 (각 열별로 연속된 1의 개수 세기)
    for (int j = 0; j < M; j++)
    {
        int current_len = 0;
        for (int i = 0; i < N; i++)
        {
            if (grid[i][j] == 1)
            {
                current_len++;
            }
            else
            {
                if (current_len >= 2)
                {
                    max_len = max(max_len, current_len);
                }
                current_len = 0;
            }
        }
        if (current_len >= 2) max_len = max(max_len, current_len);
    }

    return max_len;
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        int result = solve();
        cout << "#" << t << " " << result << endl;
    }

    return 0;
}