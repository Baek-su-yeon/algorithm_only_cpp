#include <iostream>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::vector;
using ::std::max;

// 웜홀 좌표 구조체
struct Wormhole {
    int row;
    int col;
};

// 한 변의 길이 5 ≤ N ≤ 100
int N;
// 보드 내부 값
int board[105][105];
// 웜홀 6~10
vector<Wormhole> wormholes[11]; 

// 상(0), 우(1), 하(2), 좌(3)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// 튕겨나갈 방향
int change_dir[6][4] = {
    {0, 0, 0, 0}, // 0번
    {2, 3, 1, 0}, // 1번
    {1, 3, 0, 2}, // 2번 
    {3, 2, 0, 1}, // 3번
    {2, 0, 3, 1}, // 4번
    {2, 3, 0, 1}  // 5번
};

// 점수 계산
int simulate(int srow, int scol, int sdirection) {
    int row = srow;
    int col = scol;
    int direction = sdirection;
    int score = 0;

    while (true) {
        // 직진
        row += dr[direction];
        col += dc[direction];

        // 벽에 부딪힌 경우
        if (row < 0 || row >= N || col < 0 || col >= N) {
            score++;
            // 반대 방향
            direction = (direction + 2) % 4;
            // 벽에 부딪힌 그 자리에서 바로 다음 이동 진행
            continue;
        }

        // 출발 지점으로 돌아왔거나, 블랙홀(-1)에 빠진 경우
        if ((row == srow && col == scol) || board[row][col] == -1) {
            // 종료
            break;
        }

        int cell = board[row][col];

        // 블록에 부딪힌 경우
        if (cell >= 1 && cell <= 5) {
            score++;
            // 방향 전환
            direction = change_dir[cell][direction];
        }
        // 웜홀(6~10)에 빠진 경우
        else if (cell >= 6 && cell <= 10) {
            Wormhole p1 = wormholes[cell][0];
            Wormhole p2 = wormholes[cell][1];
            
            // p1에 들어왔으면 p2, p2에 들어왔으면 p1
            if (row == p1.row && col == p1.col) {
                row = p2.row;
                col = p2.col;
            } else {
                row = p1.row;
                col = p1.col;
            }
        }
    }

    return score;
}

void solve() {
    int max_score = 0;

    // 모든 방향 탐색
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                for (int dir = 0; dir < 4; dir++) {
                    max_score = max(max_score, simulate(i, j, dir));
                }
            }
        }
    }

    cout << max_score << "\n";
}

void inputValue() {
    cin >> N;
    
    // 이전 테케 정보 비우기
    for (int i = 6; i <= 10; i++) {
        wormholes[i].clear();
    }

    // 크기 및 웜홀 좌표 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            
            if (board[i][j] >= 6 && board[i][j] <= 10) {
                // 웜홀 정보 입력 6~10번
                wormholes[board[i][j]].push_back({i, j});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int time = 1; time <= T; time++) {
        inputValue();
        cout << "#" << time << " ";
        solve();
    }

    return 0;
}