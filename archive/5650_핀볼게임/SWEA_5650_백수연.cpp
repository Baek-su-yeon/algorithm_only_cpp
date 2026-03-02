#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DIRECTION = 상, 하, 좌, 우
int dx_list[] = {-1, 1, 0, 0};
int dy_list[] = {0, 0, -1, 1};

// BLOCKS[블록번호][진입방향] = {다음_dx, 다음_dy}
// 파이썬의 DIRECTION 인덱스 순서와 맞춤: 0:상, 1:하, 2:좌, 3:우
int block_dir[6][4] = {
    {}, // 0번 (빈공간)
    {1, 3, 0, 2}, // 1번 블록
    {3, 0, 1, 2}, // 2번 블록
    {2, 0, 3, 1}, // 3번 블록
    {1, 2, 3, 0}, // 4번 블록
    {1, 0, 3, 2}  // 5번 블록 (모든 방향 반사)
};

int N;
int game[101][101];
vector<pair<int, int>> wormholes[11]; // 6~10번 웜홀 위치 저장

int play_game(int start_x, int start_y, int start_dir) {
    int score = 0;
    int x = start_x;
    int y = start_y;
    int d = start_dir;

    while (true) {
        int nx = x + dx_list[d];
        int ny = y + dy_list[d];

        // 벽에 부딪힌 경우 (5번 블록과 동일한 로직 처리)
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            score++;
            d = (d == 0) ? 1 : (d == 1) ? 0 : (d == 2) ? 3 : 2; // 반대 방향
            x = nx; y = ny;
            continue;
        }

        // 시작점 복귀 또는 블랙홀(-1) 만남
        if ((nx == start_x && ny == start_y) || game[nx][ny] == -1) {
            return score;
        }

        // 빈 공간
        if (game[nx][ny] == 0) {
            x = nx; y = ny;
        }
        // 블록(1~5) 만남
        else if (game[nx][ny] >= 1 && game[nx][ny] <= 5) {
            score++;
            int b_type = game[nx][ny];
            int next_d = block_dir[b_type][d];
            x = nx; y = ny;
            d = next_d;
        }
        // 웜홀(6~10) 만남
        else if (game[nx][ny] >= 6) {
            int w_idx = game[nx][ny];
            if (wormholes[w_idx][0].first == nx && wormholes[w_idx][0].second == ny) {
                x = wormholes[w_idx][1].first;
                y = wormholes[w_idx][1].second;
            } else {
                x = wormholes[w_idx][0].first;
                y = wormholes[w_idx][0].second;
            }
        }
    }
}

void solve(int tc) {
    cin >> N;
    int max_score = 0;
    
    // 초기화
    for (int i = 6; i <= 10; i++) wormholes[i].clear();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> game[i][j];
            if (game[i][j] >= 6) {
                wormholes[game[i][j]].push_back({i, j});
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (game[i][j] == 0) {
                for (int d = 0; d < 4; d++) {
                    max_score = max(max_score, play_game(i, j, d));
                }
            }
        }
    }

    cout << "#" << tc << " " << max_score << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        solve(tc);
    }
    return 0;
}