#include <iostream>
#include <vector>
using namespace std;
/*
아이디어
포탈은 결국 이전 위치로 돌아가기만 함
방문했던 포탈은 앞으로 한 칸만 이동 가능

>> 과정을 하나하나 겪을 필요 없이 몇 번 포탈 타야 하는지 계산 가능

예를 들어 5번 포탈에서 2번 포탈로 간다면 
이후의 과정은 2 > 3 > 4 > 5 > 6 일 수밖에 없음.
(앞으로 가는 건 한 칸씩만 갈 수 있기 때문에)

시간 복잡도: O(N)
방을 한 번씩만 훑으면 됨.

본 문제는 N의 범위가 4<=N<=20 이라 유의미하진 않지만
N이 커지게 된다면 유리

*/ 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {
        int N;  // 방의 개수
        cin >> N;
        
        int total_count = 0;  // 총 포탈 사용 횟수
        
        for (int i = 1; i <= N; i++) {
            int target;
            cin >> target; // P[i] (이동하게 되는 방)
            
            // 1번 방은 포탈 안 타고 무조건 통과 
            // N번 방은 도착지점이므로 포탈 계산 제외
            if (i < N) {
                total_count++; // i -> i+1로 가는 기본 1턴
                
                // 1번 방이 아니고(i > 1), 포탈이 존재한다면 패널티 추가
                if (i > 1) {
                    // i 번 방에서 target 방으로 포탈 이동 후 
                    // 다시 가야 하는 거리
                    // 5번 방에서 2번 방으로 이동했다면, 5-2+1번 포탈 타야 6번 방 도착
                    total_count += (1 + (i - target));
                }
            }
        }
        cout << "#" << test_case << " " << total_count << "\n";
    }
    return 0;
}