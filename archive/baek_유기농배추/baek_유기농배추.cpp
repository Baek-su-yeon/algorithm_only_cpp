#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int visited[50][50];
int row_dir[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int col_dir[4] = {0, 0, -1, 1}; // 상, 하, 좌, 우

void DFS (vector<vector<int>>& garden, int row, int col, int row_size, int col_size)
{
    visited[row][col] = true;

    for (int i = 0; i < 4; i++)
    {
        int nr = row + row_dir[i];
        int nc = col + col_dir[i];

        if (nr < 0 || nr >= row_size || nc < 0 || nc >= col_size) continue;

        if (garden[nr][nc] && !visited[nr][nc])
        {
            DFS(garden, nr, nc, row_size, col_size);
        }
    }

    return;
}

void solve (int tc)
{
    // visited 초기화
    memset(visited, false, sizeof(visited));
    
    // m: 밭 가로길이, n: 밭 세로길이, k: 배추 개수
    int m, n, k;
    cin >> m >> n >> k;

    vector<vector<int>> garden(n, vector<int> (m, 0)); // 배추밭 생성

    // 배추 심기
    int row, col;
    for (int i = 0; i < k; i++)
    {
        cin >> col >> row;
        garden[row][col] = 1;
    }

    // 필요한 지렁이 조사하기
    int worm = 0;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(garden[i][j] && !visited[i][j])
            {
                DFS(garden, i, j, n, m);
                worm ++;
            }
        }
    }

    cout << worm << "\n";

    return;
}

int main ()
{
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 테스트 케이스 반복
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve(i);

    return 0;
}