#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

vector<vector<int>> city (25, vector<int>(25, 0));
vector<vector<int>> visited (25, vector<int>(25, 0));
vector<int> total_homes;
int row_dir[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int col_dir[4] = {0, 0, -1, 1}; // 상, 하, 좌, 우
int bundle = 1;

void BFS (int row, int col, int size)
{
    deque<pair<int, int>> queue;
    int homes = 0;

    queue.push_back(make_pair(row, col));
    visited[row][col] = bundle;
    homes += 1;

    while(!queue.empty())
    {
        pair<int, int> now = queue.front();
        queue.pop_front();

        for (int i = 0; i < 4; i++)
        {
            int nr = now.first + row_dir[i];
            int nc = now.second + col_dir[i];

            if (nr < 0 || nr >= size || nc < 0 || nc >= size) continue;

            if (city[nr][nc] && !visited[nr][nc])
            {
                queue.push_back(make_pair(nr, nc));
                visited[nr][nc] = bundle;
                homes += 1;
            }
        }
    }

    bundle += 1;
    total_homes.push_back(homes);
    
    return;
}

int DFS (int row, int col, int size)
{
    visited[row][col] = bundle;
    int homes = 1;

    for (int i = 0; i < 4; i++)
    {
        int nr = row + row_dir[i];
        int nc = col + col_dir[i];

        if (nr < 0 || nr >= size || nc < 0 || nc >= size) continue;

        if (city[nr][nc] && !visited[nr][nc])
        {
            homes += DFS(nr, nc, size);
        }
    }

    return homes;
}

int main ()
{
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 지도 크기
    int n;
    cin >> n;

    // 지도 정보 받기
    string home;
    for (int i = 0; i < n; i++)
    {
        cin >> home;
        for (int j = 0; j < home.size(); j++) city[i][j] = int(home[j] - '0');
    }

    // 지도 순회
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // 지금 지도에 집이 있고, 방문을 안한 곳이면 탐색
            if (city[i][j] && !visited[i][j])
            {
                // BFS(i, j, n);

                int bundle_homes = DFS(i, j, n);
                total_homes.push_back(bundle_homes);
                bundle += 1;
            }
        }
    }

    cout << total_homes.size() << "\n";
    sort(total_homes.begin(), total_homes.end()); // 오름차순 정렬
    for (int i = 0; i < total_homes.size(); i++) cout << total_homes[i] << "\n";

    return 0;
}