#include <iostream>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::max;

// 지역의 크기
int size;
// 디저트 종류 맵
int board[20][20];
// 디저트 먹었는지 체크 (1~100)
bool eaten[101];
// 최대 디저트 수
int max_answer;

// 출발점 위치
int start_row;
int start_column;

// 우하, 좌하, 좌상, 우상
int dir_row[4] = {1, 1, -1, -1};
int dir_column[4] = {1, -1, -1, 1};

void dfs(int row, int column, int dir, int count) {
    // 직진(dir) 또는 90도 꺾기(dir + 1)
    for (int next_dir = dir; next_dir <= dir + 1; next_dir++) {
        
        // 방향은 3번(우상)이 끝
        if (next_dir >= 4) continue;

        int next_row = row + dir_row[next_dir];
        int next_column = column + dir_column[next_dir];

        // 출발점으로 돌아오면 루프 완성
        if (next_row == start_row && next_column == start_column) {
            // 4방향을 모두 거쳐 우상향으로 들어왔을 때만 정답 갱신
            if (next_dir == 3) {
                max_answer = max(max_answer, count);
            }
            continue; 
        }

        // 지도 경계 체크
        if (next_row >= 0 && next_row < size && next_column >= 0 && next_column < size) {
            int dessert = board[next_row][next_column];
            
            // 아직 안 먹은 디저트일 때만
            if (!eaten[dessert]) {
                // 방문 체크
                eaten[dessert] = true;
                // 다음 탐색
                dfs(next_row, next_column, next_dir, count + 1);
                // 백트래킹
                eaten[dessert] = false; 
            }
        }
    }
}

void solve() {
    cin >> size;

    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            cin >> board[row][column];
        }
    }

    // 테스트 케이스마다 방문 배열 초기화
    for (int i = 1; i <= 100; i++) {
        eaten[i] = false;
    }
    
    // 정답 초기화 (못 찾는 경우 -1)
    max_answer = -1;

    // 시작점 탐색 (맨 아래 2줄, 양 끝 1줄 제외)
    for (int row = 0; row < size - 2; row++) {
        for (int column = 1; column < size - 1; column++) {
            start_row = row;
            start_column = column;
            
            int dessert = board[row][column];
            
            // 시작점 방문 체크
            eaten[dessert] = true;
            // 우하(0) 방향으로 시작, 디저트 1개
            dfs(row, column, 0, 1); 
            // 방문 해제
            eaten[dessert] = false;
        }
    }

    cout << max_answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int testcases;
    if (cin >> testcases) {
        for (int testcase = 1; testcase <= testcases; testcase++) {
            cout << "#" << testcase << " ";
            solve();
        }
    }
    return 0;
}