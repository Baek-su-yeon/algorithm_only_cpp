#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::min;

// 벽돌의 위치와 폭발 범위를 저장하기 위한 구조체
struct Brick {
    int r, c, range;
};

// 전역 변수 설정
int N, W, H;
int MIN_ANS;

// 현재 맵에 남은 벽돌의 개수를 세는 함수
int getBrickCount(const vector<vector<int>>& map) {
    int cnt = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (map[i][j] > 0) cnt++;
        }
    }
    return cnt;
}

// 빈 공간이 생겼을 때 벽돌을 아래로 떨어뜨리는 함수
void applyGravity(vector<vector<int>>& map) {
    for (int j = 0; j < W; ++j) {
        vector<int> temp;
        // 아래에서 위로 올라가며 벽돌만 추출
        for (int i = H - 1; i >= 0; --i) {
            if (map[i][j] > 0) {
                temp.push_back(map[i][j]);
                map[i][j] = 0; // 기존 자리는 빈 공간으로
            }
        }
        // 추출한 벽돌을 아래에서부터 다시 채움
        for (int i = 0; i < (int)temp.size(); ++i) {
            map[H - 1 - i][j] = temp[i];
        }
    }
}

// BFS를 이용한 벽돌 폭발 처리 (연쇄 반응 포함)
void explode(int startR, int startC, vector<vector<int>>& map) {
    queue<Brick> q;
    q.push({startR, startC, map[startR][startC]});
    map[startR][startC] = 0; // 첫 타격 지점 제거

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Brick curr = q.front();
        q.pop();

        // 벽돌에 적힌 숫자 - 1 만큼 상하좌우로 확산
        for (int i = 1; i < curr.range; ++i) {
            for (int d = 0; d < 4; ++d) {
                int nr = curr.r + dr[d] * i;
                int nc = curr.c + dc[d] * i;

                if (nr >= 0 && nr < H && nc >= 0 && nc < W && map[nr][nc] > 0) {
                    // 숫자가 1보다 크면 연쇄 폭발을 위해 큐에 삽입
                    if (map[nr][nc] > 1) {
                        q.push({nr, nc, map[nr][nc]});
                    }
                    map[nr][nc] = 0;
                }
            }
        }
    }
}

// 모든 가능한 구슬 투하 위치를 탐색하는 DFS
void dfs(int count, vector<vector<int>> current_map) {
    // 모든 구슬을 쐈거나 남은 벽돌이 0개인 경우
    int current_bricks = getBrickCount(current_map);
    if (count == N || current_bricks == 0) {
        MIN_ANS = min(MIN_ANS, current_bricks);
        return;
    }

    for (int j = 0; j < W; ++j) {
        // 복사본 맵 생성 (백트래킹을 위해)
        vector<vector<int>> next_map = current_map;

        // 해당 열에서 가장 위에 있는 벽돌 찾기
        int hitR = -1;
        for (int i = 0; i < H; ++i) {
            if (next_map[i][j] > 0) {
                hitR = i;
                break;
            }
        }

        // 벽돌을 맞춘 경우에만 진행
        if (hitR != -1) {
            explode(hitR, j, next_map);
            applyGravity(next_map);
            dfs(count + 1, next_map);
        }
        
        // 가지치기: 이미 최솟값이 0이면 더 볼 필요 없음
        if (MIN_ANS == 0) return;
    }
}

void solve(int tc) {
    cin >> N >> W >> H;
    vector<vector<int>> map(H, vector<int>(W));
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> map[i][j];
        }
    }

    // 초기 최솟값을 현재 벽돌의 전체 개수로 설정
    MIN_ANS = getBrickCount(map);
    
    dfs(0, map);

    cout << "#" << tc << " " << MIN_ANS << "\n";
}

int main() {
    // 입출력 성능 최적화
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    for (int tc = 1; tc <= T; ++tc) {
        solve(tc);
    }

    return 0;
}