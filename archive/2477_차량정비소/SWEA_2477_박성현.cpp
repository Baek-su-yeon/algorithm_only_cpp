#include <iostream>
#include <queue>
#include <vector>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::queue;

struct Customer {
    int id;           // 고객 번호 
    int arrival_time; // 정비소 도착 시간
    int rec_desk;     // 이용한 접수 창구 번호
    int rep_desk;     // 이용한 정비 창구 번호
};

struct Desk {
    int time;         // 창구 업무 처리 시간
    int customer_id;  // 창구 사용 중인 고객 번호 (0이면 비어있음)
    int end_time;     // 현재 업무가 끝나는 시간
};

int N, M, K, A, B;
Desk reception[15]; // 접수 창구 배열
Desk repair[15];    // 정비 창구 배열
Customer customers[1005]; // 1~ K 고객 정보 배열

void inputValue() {
    cin >> N >> M >> K >> A >> B;

    // 접수 창구 처리 시간
    for (int i = 1; i <= N; i++) {
        cin >> reception[i].time;
        reception[i].customer_id = 0; 
    }

    // 정비 창구 처리 시간
    for (int i = 1; i <= M; i++) {
        cin >> repair[i].time;
        repair[i].customer_id = 0; 
    }

    // 고객 도착 시간 입력
    for (int i = 1; i <= K; i++) {
        customers[i].id = i;
        cin >> customers[i].arrival_time;
        customers[i].rec_desk = 0;
        customers[i].rep_desk = 0;
    }
}

void solve() {
    // 접수 대기열 큐
    queue<int> wait_reception; 
    // 정비 대기열 큐
    queue<int> wait_repair;    
    // 시뮬레이션 시간
    int current_time = 0;
    // 정비를 마친 고객 수
    int completed_cnt = 0;
    // 다음으로 정비소에 도착할 고객 번호
    int next_customer_idx = 1; 

    while (completed_cnt < K) {
        
        // 접수 창구 완료
        for (int i = 1; i <= N; i++) {
            if (reception[i].customer_id != 0 && reception[i].end_time == current_time) {
                // 정비 대기열로 이동
                wait_repair.push(reception[i].customer_id);
                // 창구 비우기
                reception[i].customer_id = 0;
            }
        }

        // 정비 창구 완료
        for (int i = 1; i <= M; i++) {
            if (repair[i].customer_id != 0 && repair[i].end_time == current_time) {
                // 처리 끝난 고객 카운트 증가
                completed_cnt++; 
                // 창구 비우기
                repair[i].customer_id = 0; 
            }
        }

        // 새로운 고객 도착 처리
        while (next_customer_idx <= K && customers[next_customer_idx].arrival_time == current_time) {
            // 접수 대기열로 이동
            wait_reception.push(next_customer_idx); 
            // 다음 고객 번호
            next_customer_idx++;
        }

        // 빈 접수 창구에 대기 중인 고객 배정
        for (int i = 1; i <= N; i++) {
            if (reception[i].customer_id == 0 && !wait_reception.empty()) {
                int cid = wait_reception.front();
                wait_reception.pop();
                
                reception[i].customer_id = cid;
                reception[i].end_time = current_time + reception[i].time;
                // 고객 창구 번호 기록
                customers[cid].rec_desk = i; 
            }
        }

        // 빈 정비 창구에 대기 중인 고객 배정
        for (int i = 1; i <= M; i++) {
            if (repair[i].customer_id == 0 && !wait_repair.empty()) {
                int cid = wait_repair.front();
                wait_repair.pop();
                
                repair[i].customer_id = cid;
                repair[i].end_time = current_time + repair[i].time;
                customers[cid].rep_desk = i; // 고객의 꼬리표에 이용한 창구 번호 기록
            }
        }

        // 정비를 끝날 때까지 1초씩 증가
        current_time++;
    }

    // 고객(지갑 주인 후보) 찾기
    int answer = 0;
    for (int i = 1; i <= K; i++) {
        if (customers[i].rec_desk == A && customers[i].rep_desk == B) {
            answer += customers[i].id;
        }
    }

    // 조건에 맞는 고객이 한 명도 없으면
    if (answer == 0) cout << -1 << "\n";
    else cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin); 

    int T;
    cin >> T;

    for (int testcase = 1; testcase <= T; testcase++) {
        inputValue();
        cout << "#" << testcase << " ";
        solve();
    }

    return 0;
}