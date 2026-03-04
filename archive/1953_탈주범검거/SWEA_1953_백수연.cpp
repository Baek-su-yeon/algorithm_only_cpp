#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstring> // memset 사용

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::map;
using ::std::vector;
using ::std::pair;
using ::std::deque;
using ::std::memset;

// 변수 선언부
int UNDERGROUD[50][50];
int VISITED[50][50];
map<int, vector<pair<int,int>>> TUNNEL = {
    {1, {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}, // 상하좌우
    {2, {{-1, 0}, {1, 0}}}, // 상하
    {3, {{0, -1}, {0, 1}}}, // 좌우
    {4, {{-1, 0}, {0, 1}}}, // 상우
    {5, {{1, 0}, {0, 1}}}, // 하우
    {6, {{1, 0}, {0, -1}}}, // 하좌
    {7, {{-1, 0}, {0, -1}}}, // 상좌
};

int find_thief (int max_x, int max_y, int start_x, int start_y, int time)
{
    int result = 0;
    deque<pair<int,int>> goto_bfs;

    goto_bfs.push_back({start_x, start_y});
    VISITED[start_x][start_y] = 1;
    result++;
    
    while(!goto_bfs.empty())
    {
        pair<int, int> now = goto_bfs.front();
        goto_bfs.pop_front();

        if (VISITED[now.first][now.second] >= time) continue;

        vector<pair<int,int>> now_tunnel = TUNNEL[UNDERGROUD[now.first][now.second]];
        
        for (int i = 0; i < now_tunnel.size(); i++)
        {
            int next_x = now.first + now_tunnel[i].first;
            int next_y = now.second + now_tunnel[i].second;

            if (next_x < 0 || next_x >= max_x || next_y < 0 || next_y >= max_y) continue;
            
            if (VISITED[next_x][next_y] || UNDERGROUD[next_x][next_y] == 0) continue;
            
            // 연결되어 있는지 확인
            vector<pair<int, int>> next_tunnle = TUNNEL[UNDERGROUD[next_x][next_y]];
            for (int j = 0; j < next_tunnle.size(); j++)
            {
                if (now_tunnel[i].first * -1 == next_tunnle[j].first &&
                    now_tunnel[i].second * -1 == next_tunnle[j].second)
                {
                    goto_bfs.push_back({next_x, next_y});
                    VISITED[next_x][next_y] = VISITED[now.first][now.second] + 1;
                    result++;
                }
            }
        }
    }

    return result;
}

void solve (int tc)
{   
    // 배열 초기화 (memset을 쓰면 편해요)
    memset(UNDERGROUD, 0, sizeof(UNDERGROUD));
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