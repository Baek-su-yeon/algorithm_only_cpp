#include <iostream>
#include <queue>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::min;
using ::std::queue;

int max_shots, width, height;
int min_remain_bricks;

// 방향 배열 (상, 하, 좌, 우)
int direction_y[4] = {-1, 1, 0, 0};
int direction_x[4] = {0, 0, -1, 1};

// 보드판
struct BoardState {
    int map[15][15];
};

// 벽돌 정보 
struct BrickInfo {
    int y, x, power;
};

// 남은 벽돌 개수
int count_remain_bricks(const BoardState& state) {
    int current_count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (state.map[y][x] > 0) current_count++;
        }
    }
    return current_count;
}

// 중력 - 끌어내리기
void apply_gravity(BoardState& state) {
    for (int x = 0; x < width; x++) {
        int write_index = height - 1; 
        for (int y = height - 1; y >= 0; y--) {
            if (state.map[y][x] > 0) {
                int temp_value = state.map[y][x];
                state.map[y][x] = 0; 
                state.map[write_index][x] = temp_value; 
                write_index--;
            }
        }
    }
}

// 연쇄 폭발 BFS
void explode_bricks(int target_x, BoardState& state) {
    int target_y = 0;
    
    // 맨 위에 있는 벽돌
    while (target_y < height && state.map[target_y][target_x] == 0) target_y++;
    if (target_y == height) return; 

    queue<BrickInfo> boom_queue;
    boom_queue.push({target_y, target_x, state.map[target_y][target_x]});
    state.map[target_y][target_x] = 0; 

    // 연쇄 폭발
    while (!boom_queue.empty()) {
        BrickInfo current_brick = boom_queue.front();
        boom_queue.pop();

        int current_power = current_brick.power;
        if (current_power == 1) continue; 

        for (int direction_index = 0; direction_index < 4; direction_index++) {
            int next_y = current_brick.y;
            int next_x = current_brick.x;
            
            // 범위만큼 뻗어나감
            for (int power_step = 1; power_step < current_power; power_step++) { 
                next_y += direction_y[direction_index];
                next_x += direction_x[direction_index];

                if (next_y >= 0 && next_y < height && next_x >= 0 && next_x < width && state.map[next_y][next_x] > 0) {
                    if (state.map[next_y][next_x] > 1) {
                        boom_queue.push({next_y, next_x, state.map[next_y][next_x]}); 
                    }
                    state.map[next_y][next_x] = 0; 
                }
            }
        }
    }
}

// 남은 블록 값 찾기
void search_minimum_bricks(int current_shot, BoardState current_state) {
    if (min_remain_bricks == 0) return;

    int remain_count = count_remain_bricks(current_state);
    
    if (current_shot == max_shots || remain_count == 0) {
        min_remain_bricks = min(min_remain_bricks, remain_count);
        return;
    }

    for (int x = 0; x < width; x++) {
        bool has_brick = false;
        for (int y = 0; y < height; y++) {
            if (current_state.map[y][x] > 0) {
                has_brick = true;
                break;
            }
        }
        if (!has_brick) continue;

        BoardState next_state = current_state; 
        // 블록 폭파
        explode_bricks(x, next_state);
        // 중력 적용
        apply_gravity(next_state);
        // 남은 블록 갯수
        search_minimum_bricks(current_shot + 1, next_state);
    }
}

void solve_testcase() {
    cin >> max_shots >> width >> height;
    // 보드 상태 초기화
    BoardState initial_state;
    // 보드 세로
    for (int y = 0; y < height; y++) {
        // 보드 가로
        for (int x = 0; x < width; x++) {
            cin >> initial_state.map[y][x];
        }
    }

    min_remain_bricks = 9999999; 
    search_minimum_bricks(0, initial_state);

    cout << min_remain_bricks << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int total_testcases;
    if (cin >> total_testcases) {
        for (int testcase = 1; testcase <= total_testcases; testcase++) {
            cout << "#" << testcase << " ";
            solve_testcase();
        }
    }
    return 0;
}