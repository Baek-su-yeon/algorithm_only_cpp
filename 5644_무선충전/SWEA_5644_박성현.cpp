#include <iostream>
#include <vector>
#include <cmath> // abs() 함수
#include <algorithm> // max() 함수

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::vector;
using ::std::abs;
using ::std::max;

// 그냥 인덱스로 받으면 이게 뭘 뜻하는 건지 햇갈린다고 추천 받은 방법
// BC 정보 구조체
struct BC {
    int x, y; // 위치 좌표
    int c;    // 충전 범위
    int p;    // 성능
};

 // M: 총 이동 시간, A: BC의 개수
int M, A;
// 사용자 A
vector<int> userA; 
 // 사용자 B
vector<int> userB;
 // BC 정보
vector<BC> BCs;

// 이동 방향: 0(이동 안함), 1(상), 2(우), 3(하), 4(좌)
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};

void solve() {
    // 사용자 A 초기 위치
    int ax = 1, ay = 1;
    // 사용자 B 초기 위치
    int bx = 10, by = 10;
    int total_charge = 0;

    for (int t = 0; t <= M; t++) {
        // 현재 위치에서 접속 가능한 BC 목록
        vector<int> candA = {-1}; 
        vector<int> candB = {-1};

        for (int i = 0; i < A; i++) {
            // 거리 계산: |Xa - Xbc| + |Ya - Ybc| <= C
            if (abs(ax - BCs[i].x) + abs(ay - BCs[i].y) <= BCs[i].c) {
                // A가 접속 가능한 BC 인덱스
                candA.push_back(i);
            }
            if (abs(bx - BCs[i].x) + abs(by - BCs[i].y) <= BCs[i].c) {
                // B가 접속 가능한 BC 인덱스
                candB.push_back(i); 
            }
        }

        int current_max = 0;

        // A가 고를 수 있는 모든 경우
        for (int a_idx : candA) {
            // B가 고를 수 있는 모든 경우
            for (int b_idx : candB) {
                int sum = 0;

                // 같은 BC를 선택했고, 그게 실제 BC인 경우 - 둘 다 -1인 경우 제외
                if (a_idx == b_idx && a_idx != -1) {
                    // P만큼 획득
                    sum = BCs[a_idx].p;
                } 
                // 서로 다른 BC를 선택한 경우 - 각자 P 획득
                else {
                    if (a_idx != -1) sum += BCs[a_idx].p;
                    if (b_idx != -1) sum += BCs[b_idx].p;
                }

                // 최댓값 갱신
                current_max = max(current_max, sum);
            }
        }

        // 최댓값을 총 충전량에 누적
        total_charge += current_max;

        // 다음 위치로 이동
        if (t < M) {
            ax += dx[userA[t]];
            ay += dy[userA[t]];
            bx += dx[userB[t]];
            by += dy[userB[t]];
        }
    }

    cout << total_charge << "\n";
}

void inputValue() {
    cin >> M >> A;
    
    // 전역 변수 이전 테스트 케이스 데이터 비우기
    userA.clear(); 
    userB.clear(); 
    BCs.clear();
    
    // userA 경로 입력
    for (int i = 0; i < M; i++) {
        int dir;
        cin >> dir;
        userA.push_back(dir);
    }
    
    // userB 경로 입력
    for (int i = 0; i < M; i++) {
        int dir;
        cin >> dir;
        userB.push_back(dir);
    }

    // BC 정보 입력
    for (int i = 0; i < A; i++) {
        int x, y, c, p;
        cin >> x >> y >> c >> p;
        BCs.push_back({x, y, c, p});
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