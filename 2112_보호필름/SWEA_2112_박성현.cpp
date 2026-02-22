#include <iostream>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::min;
using ::std::max;

int D, W, K;
int film[15][25];
int inject[15]; // -1: 약품 투입 안 함, 0: A약품 투입, 1: B약품 투입
int min_inject;

// 합격 기준 검사
bool check() {
    for (int c = 0; c < W; c++) {
        int max_streak = 1;
        int current_streak = 1;
        
        // inject 배열을 확인하여 약품이 투입되었으면 약품 값, 아니면 원본 필름 값 가져옴
        int prev = (inject[0] == -1) ? film[0][c] : inject[0];
        
        for (int r = 1; r < D; r++) {
            
            int curr = (inject[r] == -1) ? film[r][c] : inject[r];
            
            if (curr == prev) {
                current_streak++;
                max_streak = max(max_streak, current_streak);
            } else {
                current_streak = 1;
                prev = curr;
            }
            
            // K번 연속을 만족 검사할 필요 없음
            if (max_streak >= K) break;
        }
        
        // 세로줄 하나라도 K번 연속을 달성하지 못했다면 불합격
        if (max_streak < K) return false;
    }
    // 모든 세로줄이 기준을 통과
    return true;
}

// row: 현재 막의 인덱스, count: 투입한 약품 횟수
void dfs(int row, int count) {
    // 백트래킹: 이미 찾은 최소 투입 횟수보다 크거나 같아지면 더 탐색할 필요 없음
    if (count >= min_inject) return;
    
    // D번째 막까지 모두 결정을 내린 경우
    if (row == D) {
        if (check()) {
            min_inject = min(min_inject, count);
        }
        return;
    }

    // 현재 막에 약품을 투입하지 않음
    inject[row] = -1;
    dfs(row + 1, count);

    // 현재 막에 A약품(0) 투입
    inject[row] = 0;
    dfs(row + 1, count + 1);

    // 현재 막에 B약품(1) 투입
    inject[row] = 1;
    dfs(row + 1, count + 1);
}

void solve() {
    cin >> D >> W >> K;
    
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < W; j++) {
            cin >> film[i][j];
        }
         // 초기화
        inject[i] = -1;
    }

    // 합격 기준이 1인 경우 약품을 넣을 필요 없음
    if (K == 1) {
        cout << 0 << "\n";
        return;
    }

    // 최악의 경우에도 K번 약품을 넣으면 무조건 합격이므로 초기 최솟값을 K로 설정
    min_inject = K; 
    
    // 0번째 막부터 탐색 시작
    dfs(0, 0);

    cout << min_inject << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cout << "#" << tc << " ";
        solve();
    }
    return 0;
}