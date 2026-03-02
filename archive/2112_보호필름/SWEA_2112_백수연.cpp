#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

// 전역 변수 설정
int D, W, K;
int FILM[14][21];
int MODIFIED[14]; // -1: 미투입, 0: A약품, 1: B약품
int MIN_ANS;

// 성능 검사: 모든 열에서 동일 특성이 K개 이상 연속되는지 확인
bool check() {
    for (int j = 0; j < W; ++j) {
        bool column_ok = false;
        int cnt = 1;
        
        // 첫 번째 행의 실제 값 결정
        int prev = (MODIFIED[0] == -1) ? FILM[0][j] : MODIFIED[0];

        if (K == 1) column_ok = true;
        else {
            for (int i = 1; i < D; ++i) {
                int curr = (MODIFIED[i] == -1) ? FILM[i][j] : MODIFIED[i];
                if (prev == curr) {
                    if (++cnt >= K) {
                        column_ok = true;
                        break;
                    }
                } else {
                    prev = curr;
                    cnt = 1;
                }
            }
        }
        if (!column_ok) return false;
    }
    return true;
}

// 재귀를 이용한 백트래킹 탐색
void dfs(int row, int count) {
    // 가지치기: 현재 투입 횟수가 이미 구한 최솟값보다 크면 유망하지 않음
    if (count >= MIN_ANS) return;

    // 모든 행의 처리 방식이 결정된 경우
    if (row == D) {
        if (check()) {
            MIN_ANS = count;
        }
        return;
    }

    // 1. 약품 투입 안 함 (원본 유지)
    MODIFIED[row] = -1;
    dfs(row + 1, count);

    // 2. 약품 A 투입
    MODIFIED[row] = 0;
    dfs(row + 1, count + 1);

    // 3. 약품 B 투입
    MODIFIED[row] = 1;
    dfs(row + 1, count + 1);
    
    // 상태 복구
    MODIFIED[row] = -1;
}

// 문제 해결부
void solve(int tc) {
    std::cin >> D >> W >> K;

    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < W; ++j) {
            std::cin >> FILM[i][j];
        }
        MODIFIED[i] = -1; // 초기화
    }

    // 최솟값 초기화 (최악의 경우에도 K번 투입하면 무조건 통과)
    MIN_ANS = K;

    // K가 1이거나 약품 없이 통과 가능한 경우 바로 종료
    if (K == 1 || check()) {
        MIN_ANS = 0;
    } else {
        dfs(0, 0);
    }

    std::cout << '#' << tc << ' ' << MIN_ANS << '\n';
}

// 테스트 케이스 입력부
int main() {
    // 입출력 최적화
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    if (!(std::cin >> T)) return 0;

    for (int i = 1; i <= T; ++i) {
        solve(i);
    }

    return 0;
}