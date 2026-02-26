#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::vector;
using ::std::abs;
using ::std::max;

// 집의 좌표 정보
struct Home {
    int row;
    int col;
};

// 도시의 크기
int size;
// 가구당 지불 비용
int home_pay;
// 집들의 위치 목록
vector<Home> home_list;
// 손해 없는 최대 집의 수
int max_home_count;

void solve() {
    cin >> size >> home_pay;

    // 집 목록 및 정답 초기화
    home_list.clear();
    max_home_count = 0;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int is_home;
            cin >> is_home;
            // 집 위치만 백터에 저장
            if (is_home == 1) {
                home_list.push_back({row, col});
            }
        }
    }

    // 도시의 모든 칸을 서비스 중심점으로 탐색
    for (int center_row = 0; center_row < size; center_row++) {
        for (int center_col = 0; center_col < size; center_col++) {
            
            // 1부터 도시를 다 덮을 때까지
            for (int area_size = 1; area_size <= size + 1; area_size++) {
                
                // 운영 비용 계산 공식
                int operate_cost = (area_size * area_size) + ((area_size - 1) * (area_size - 1));
                // 서비스 범위 안의 집 수
                int covered_homes = 0;

                // 모든 집 순회 거리 측정
                for (int i = 0; i < home_list.size(); i++) {
                    // 가로 차이 + 세로 차이
                    int distance = abs(center_row - home_list[i].row) + abs(center_col - home_list[i].col);
                    
                    // 거리가 영역 크기보다 작으면 서비스 범위 안
                    if (distance < area_size) {
                        covered_homes++;
                    }
                }

                // 회사의 수익 = (집 수 * 지불 비용) - 운영 비용
                int profit = (covered_homes * home_pay) - operate_cost;

                // 손해를 보지 않으면 최대치 갱신
                if (profit >= 0) {
                    max_home_count = max(max_home_count, covered_homes);
                }
            }
        }
    }

    cout << max_home_count << "\n";
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