#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::max;

// 지도의 가로/세로 크기
int map_size;
// 최대 공사 가능 깊이 (K)            
int max_dig_depth;          
// 2차원 지도
int mountain_map[10][10];   
// 방문 체크 배열
bool is_visited[10][10];    
// 최대 등산로 길이
int max_trail_length;       

// 상, 하, 좌, 우
int direction_row[4] = {-1, 1, 0, 0};
int direction_col[4] = {0, 0, -1, 1};

void explore_trail(int current_row, int current_col, int current_length, bool has_used_construction) {
    // 최대치 갱신
    max_trail_length = max(max_trail_length, current_length);
    // 방향 별로 반복
    for (int direction = 0; direction < 4; direction++) {
        int next_row = current_row + direction_row[direction];
        int next_col = current_col + direction_col[direction];

        // 지도를 벗어나지 않는지 확인
        if (next_row >= 0 && next_row < map_size && next_col >= 0 && next_col < map_size) {
            
            // 아직 방문하지 않은 칸일 때만 진행
            if (!is_visited[next_row][next_col]) {
                
                // 다음 칸이 현재 칸보다 낮아서 그냥 지나갈 수 있는 경우
                if (mountain_map[next_row][next_col] < mountain_map[current_row][current_col]) {
                    is_visited[next_row][next_col] = true;
                    explore_trail(next_row, next_col, current_length + 1, has_used_construction);
                    // 백트래킹
                    is_visited[next_row][next_col] = false; 
                } 
                // 다음 칸이 나보다 높거나 같아서 막혔지만, 아직 깎을 값이 남아있는 경우
                else if (!has_used_construction) {
                    // 최대 깊이만큼 깎았을 때 현재 내 높이보다 낮아질 수 있는지 확인
                    if (mountain_map[next_row][next_col] - max_dig_depth < mountain_map[current_row][current_col]) {
                        
                        // 공사 전 원래 높이
                        int original_height = mountain_map[next_row][next_col];
                        
                        // 현재 내 높이보다 딱 1만 낮게 깎음
                        mountain_map[next_row][next_col] = mountain_map[current_row][current_col] - 1;
                        
                        is_visited[next_row][next_col] = true;
                        // 공사 했으므로 true
                        explore_trail(next_row, next_col, current_length + 1, true); 
                        
                        // 백트래킹
                        is_visited[next_row][next_col] = false;
                        mountain_map[next_row][next_col] = original_height;
                    }
                }
            }
        }
    }
}

void solve() {
    cin >> map_size >> max_dig_depth;

    // 지도에서 가장 높은 봉우리의 높이
    int highest_peak = 0;

    for (int row = 0; row < map_size; row++) {
        for (int col = 0; col < map_size; col++) {
            cin >> mountain_map[row][col];
            // 값 입력 받으면서 봉우리 최대치 입력
            highest_peak = max(highest_peak, mountain_map[row][col]);
            // 방문 배열 초기화
            is_visited[row][col] = false; 
        }
    }
    // 최댓값 초기화
    max_trail_length = 0; 

    // 가장 높은 봉우리 찾기
    for (int row = 0; row < map_size; row++) {
        for (int col = 0; col < map_size; col++) {
            if (mountain_map[row][col] == highest_peak) {
                // 방문 배열 체크
                is_visited[row][col] = true;
                // 길이 1부터 시작, 공사 여부 (false)
                explore_trail(row, col, 1, false);
                // 방문 배열 체크 해제 
                is_visited[row][col] = false;
            }
        }
    }
    
    cout << max_trail_length << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int total_testcases;
    if (cin >> total_testcases) {
        for (int testcase = 1; testcase <= total_testcases; testcase++) {
            cout << "#" << testcase << " ";
            solve();
        }
    }
    return 0;
}