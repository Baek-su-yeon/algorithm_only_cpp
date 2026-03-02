#include <iostream>
#include <vector>   
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case  <= T; test_case++) {
        // 방 번호 1부터 N까지
        int N;
        cin >> N;
        // i번 방에서 이동할 수 있는 포탈
        vector<int> P(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> P[i];
        }
        // 방문 여부 체크
        vector<bool> visited(N + 1, false);
        // 현재 방 번호
        int current_room = 1;
        // 포탈 사용 횟수
        int total_count = 0;
        // 모든 방 방문
        while (current_room < N) {
            // 1번 방 - 방문 여부와 상관없이 무조건 2번 방으로 이동
            if (current_room == 1) {
                current_room = 2; 
            }
            // 현재 방이 방문한 적이 없다면
            else if (!visited[current_room]) {
                visited[current_room] = true;
                 // 뒤로 이동
                current_room = P[current_room];
            }else {
                // 다음방
                current_room++;
            }
            total_count++;
        }
        cout << "#" << test_case << " " << total_count << "\n";
    }
    system("pause"); // 결과창 꺼짐 방지용
    return 0;
}