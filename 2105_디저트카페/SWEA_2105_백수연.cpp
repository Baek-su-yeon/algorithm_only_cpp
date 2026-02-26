#include <iostream>
#include <vector> // pair 사용
#include <algorithm> // max 사용

using ::std::cin;
using ::std::cout;
using ::std::make_pair;
using ::std::pair;
using ::std::max;
using ::std::ios;

// 카페맵
int CAFES[20][20];
bool EATEN[101] = {false,};

// 방향벡터 (우하, 좌하, 좌상, 우상 - 시계방향)
int MOVE_ROW[4] = {1, 1, -1, -1};
int MOVE_COL[4] = {1, -1, -1, 1};

int MAX_EAT = -1; 

struct State
{
    pair<int, int> coordinate;
    int direction;
};

void find_route(pair<int, int> start, State now, int eat, int size)
{
    int r = now.coordinate.first;
    int c = now.coordinate.second;

    // 1. 디저트 중복 체크 (시작점일 때는 제외하고 체크하거나 순서 조정 필요)
    int dessert = CAFES[r][c];
    if (EATEN[dessert]) return;

    EATEN[dessert] = true;

    for (int i = 0; i < 2; i++) {
        int n_dir = now.direction + i;
        if (n_dir > 3) continue;

        int nr = r + MOVE_ROW[n_dir];
        int nc = c + MOVE_COL[n_dir];

        // 2. 다음 칸이 시작점인지 먼저 확인! (한 바퀴 성공)
        if (nr == start.first && nc == start.second && eat >= 3) {
            MAX_EAT = max(MAX_EAT, eat + 1);
        } 
        // 3. 시작점이 아니면 범위 체크 후 전진
        else if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
            State next = {{nr, nc}, n_dir};
            find_route(start, next, eat + 1, size);
        }
    }

    EATEN[dessert] = false; // 백트래킹
    
}

void solve (int tc)
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) cin >> CAFES[i][j];
    }

    // 사각형 못 만드는 구역 빼기
    for (int i = 0; i < N - 2; i++)
    {   
        for (int j = 1; j < N - 1; j++)
        {
            State now;
            now.coordinate = make_pair(i, j);
            now.direction = 0;
            
            find_route(make_pair(i,j), now, 0, N);
        }
    }
    
    cout << '#' << tc << ' ' << MAX_EAT << '\n';

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
        MAX_EAT = -1;
        solve(i);
    }

    return 0;
}