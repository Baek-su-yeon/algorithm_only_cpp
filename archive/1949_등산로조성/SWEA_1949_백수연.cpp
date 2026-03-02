#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

// 방향 벡터 (상, 하, 좌, 우)
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int N, K, MAX_LEN;
int map[8][8];
bool visited[8][8];

/**
 * DFS를 이용한 등산로 탐색
 * @param r 현재 행
 * @param c 현재 열
 * @param h 현재 위치의 높이
 * @param used 지형을 깎았는지 여부
 * @param len 현재까지의 등산로 길이
 */
void dfs(int r, int c, int h, bool used, int len)
{
    // 현재까지의 최대 길이 갱신
    MAX_LEN = max(MAX_LEN, len);
    visited[r][c] = true;

    for (int i = 0; i < 4; ++i)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // 지도 범위를 벗어나거나 이미 방문한 경우 제외
        if (nr < 0 || nr >= N || nc < 0 || nc >= N || visited[nr][nc]) continue;

        // 1. 현재 높이보다 낮은 지형으로 이동하는 경우
        if (map[nr][nc] < h)
        {
            dfs(nr, nc, map[nr][nc], used, len + 1);
        }
        // 2. 높거나 같지만 아직 지형을 깎지 않았고, 깎아서 이동 가능한 경우
        else if (!used && map[nr][nc] - K < h)
        {
            // 다음 칸을 현재 칸보다 '딱 1만큼' 작게 깎는 것이 가장 유리함
            dfs(nr, nc, h - 1, true, len + 1);
        }
    }

    // 백트래킹을 위해 방문 표시 해제
    visited[r][c] = false;
}

void solve(int tc)
{
    cin >> N >> K;

    int maxHeight = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j) 
        {
            cin >> map[i][j];
            if (map[i][j] > maxHeight) maxHeight = map[i][j];
        }
    }

    MAX_LEN = 0;
    // 모든 가장 높은 봉우리에서 DFS 시작
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (map[i][j] == maxHeight)
            {
                dfs(i, j, maxHeight, false, 1);
            }
        }
    }

    cout << "#" << tc << " " << MAX_LEN << "\n";
}

int main() 
{
    // 입출력 최적화
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc ++)
    {
        solve(tc);
    }

    return 0;
}