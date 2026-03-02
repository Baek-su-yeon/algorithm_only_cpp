#include <iostream>
#include <deque>
#include <cstring> // memset 사용

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::deque;
using ::std::memset;
using ::std::pair;

// 변수 선언부
int UNDERGROUD[50][50];
int VISITED[50][50];

// 상하좌우 이동 각 방향과 반대에 있는 방향 인덱스
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int opp[4] = {1, 0, 3, 2};

bool TUNNEL[8][4] = {
    {false, false, false, false}, // 빈 것
    {true, true, true, true}, // 상하좌우
    {true, true, false, false}, // 상하
    {false, false, true, true}, // 좌우
    {true, false, false, true}, // 상우
    {false, true, false, true}, // 하우
    {false, true, true, false}, // 하좌
    {true, false, true, false}, // 상좌
};

int find_thief (int max_x, int max_y, int start_x, int start_y, int time)
{
    int result = 0;
    deque<pair<int, int>> goto_bfs;

    goto_bfs.push_back({start_x, start_y});
    VISITED[start_x][start_y] = 1;
    result++;

    while(!goto_bfs.empty())
    {
        pair<int, int> now = goto_bfs.front();
        goto_bfs.pop_front();

        if (VISITED[now.first][now.second] >= time) continue;

        int type = UNDERGROUD[now.first][now.second];
        for (int i = 0; i < 4; i++)
        {
            // 현재 터널이 어디로 뚫려있나
            if (!TUNNEL[type][i]) continue;

            int nx = now.first + dx[i];
            int ny = now.second + dy[i];

            if (nx < 0 || nx >= max_x || ny < 0 || ny >= max_y) continue;
            
            if (VISITED[nx][ny]) continue;

            int nt = UNDERGROUD[nx][ny];
            if (TUNNEL[nt][opp[i]]) // 지금 방향 i의 반대 방향이 true인가?
            {
                goto_bfs.push_back({nx, ny});
                VISITED[nx][ny] = VISITED[now.first][now.second] + 1;
                result++;
            }
        }
    }

    return result;
}

void solve (int tc)
{   
    // 배열 초기화 (memset을 쓰면 편해요)
    memset(VISITED, 0, sizeof(VISITED));

    int N, M, R, C, L;
    cin >> N >> M >> R >> C >> L;

    // 지하 터널 지도 표시
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) cin >> UNDERGROUD[i][j];
    }

    cout << '#' << tc << ' ' << find_thief(N, M, R, C, L) << '\n';

    return;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 0;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}