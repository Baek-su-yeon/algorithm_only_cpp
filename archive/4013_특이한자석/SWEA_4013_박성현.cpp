#include <iostream>
#include <deque>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::deque;

// 회전 시키고자 하는 횟수
int K = 0;
// 1번부터 4번까지 기어를 편하게 쓰기 위해 5개 선언
deque<int> Gear[5];

// 시계 방향
void rotateClock(int num) {
    int temp = Gear[num].back();
    Gear[num].pop_back();
    Gear[num].push_front(temp);
}

// 반시계 방향
void rotateReverseClock(int num) {
    int temp = Gear[num].front();
    Gear[num].pop_front();
    Gear[num].push_back(temp);
}

void solve() {
    // 점수 계산 , K번 회전 
    for (int k = 0; k < K; k++) {
        int num, dir;
        cin >> num >> dir;

        // 각 기어 방향 저장 배열 (0이면 안 돎)
        int direction[5] = {0, 0, 0, 0, 0};
        
        direction[num] = dir; // 기준 기어 방향 설정

        // 기준 기어에서 '왼쪽'
        for (int i = num; i > 1; i--) {
            // 현재 기어의 9시(6번 인덱스) 왼쪽 기어의 3시(2번 인덱스) 비교
            if (Gear[i][6] != Gear[i - 1][2]) {
                 // 극성이 다르면 반대 방향
                direction[i - 1] = -direction[i];
            } else {
                 // 극성이 같으면 연쇄 회전이 끊김
                break;
            }
        }

        // 기준 기어에서 '오른쪽'
        for (int i = num; i < 4; i++) {
            // 현재 기어의 3시(2번 인덱스) 오른쪽 기어의 9시(6번 인덱스) 비교
            if (Gear[i][2] != Gear[i + 1][6]) {
                // 극성이 다르면 반대 방향
                direction[i + 1] = -direction[i]; 
            } else {
                 // 극성이 같으면 연쇄 회전이 끊김
                break;
            }
        }

        // 기어 회전시키기
        for (int i = 1; i <= 4; i++) {
            // 1이면 정방향
            if (direction[i] == 1) {
                rotateClock(i);
            // -1 이면 역방향
            } else if (direction[i] == -1) {
                rotateReverseClock(i);
            }
        }
    }

    // K번 째 점수 계산
    int score = 0;
    if (Gear[1][0] == 1) score += 1; // 1번 자석 S극(1)이면 1점
    if (Gear[2][0] == 1) score += 2; // 2번 자석 S극(1)이면 2점
    if (Gear[3][0] == 1) score += 4; // 3번 자석 S극(1)이면 4점
    if (Gear[4][0] == 1) score += 8; // 4번 자석 S극(1)이면 8점

    cout << score << "\n";
}

// deque에 값 받기
void insertValue() {
    for (int i = 1; i <= 4; i++) {
        // 새로운 테케마다 덱 비우기
        // 안해주면 이전 값이 쌓임
        Gear[i].clear();

        for (int j = 0; j < 8; j++) {
            // 아직 할당되어있지 않은 인덱스에 값을 입력받으면 에러남
            // 하나씩 받아서 deque에 쌓는 형태로 써야함.
            int mag;
            cin >> mag;
            Gear[i].push_back(mag);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int time = 1; time <= T; time++) {
        cin >> K;
        insertValue();
        
        cout << "#" << time << " ";
        solve();
    }
    
    return 0;
}