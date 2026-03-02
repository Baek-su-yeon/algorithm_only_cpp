#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::priority_queue;
using std::ios;

// 고객 정보 구조체
struct Customer {
    int id;
    int arriveTime;
    int receptionId = -1;
    int repairId = -1;
    int receptionEndTime = -1;
};

// 창구 정보 구조체
struct Desk {
    int processTime;
    int remainTime = 0;
    int customerIdx = -1;
};

// 정비 대기열 우선순위 규칙
// 1. 접수 창구에서 빨리 끝난 순
// 2. 이용했던 접수 창구 번호가 작은 순
struct CompareRepair {
    bool operator()(Customer* a, Customer* b) {
        if (a->receptionEndTime != b->receptionEndTime)
            return a->receptionEndTime > b->receptionEndTime;
        return a->receptionId > b->receptionId;
    }
};

void solve(int tc) {
    int N, M, K, A, B;
    cin >> N >> M >> K >> A >> B;

    vector<Desk> receptionDesks(N + 1);
    for (int i = 1; i <= N; ++i) cin >> receptionDesks[i].processTime;

    vector<Desk> repairDesks(M + 1);
    for (int i = 1; i <= M; ++i) cin >> repairDesks[i].processTime;

    vector<Customer> customers(K + 1);
    for (int i = 1; i <= K; ++i) {
        customers[i].id = i;
        cin >> customers[i].arriveTime;
    }

    queue<Customer*> receptionWait;
    priority_queue<Customer*, vector<Customer*>, CompareRepair> repairWait;

    int time = 0;
    int completedCount = 0;
    int receptionInQueueIdx = 1;

    // 모든 고객이 정비 배정을 받을 때까지 반복 (또는 모든 고객 처리가 완료될 때까지)
    while (completedCount < K) {
        // 1. 접수 완료 처리 -> 정비 대기열로 이동
        for (int i = 1; i <= N; ++i) {
            if (receptionDesks[i].customerIdx != -1) {
                receptionDesks[i].remainTime--;
                if (receptionDesks[i].remainTime == 0) {
                    int cIdx = receptionDesks[i].customerIdx;
                    customers[cIdx].receptionEndTime = time;
                    repairWait.push(&customers[cIdx]);
                    receptionDesks[i].customerIdx = -1;
                }
            }
        }

        // 2. 정비 완료 처리
        for (int i = 1; i <= M; ++i) {
            if (repairDesks[i].customerIdx != -1) {
                repairDesks[i].remainTime--;
                if (repairDesks[i].remainTime == 0) {
                    repairDesks[i].customerIdx = -1;
                    completedCount++;
                }
            }
        }

        // 3. 현재 시간에 도착한 고객을 접수 대기열에 추가
        while (receptionInQueueIdx <= K && customers[receptionInQueueIdx].arriveTime <= time) {
            receptionWait.push(&customers[receptionInQueueIdx]);
            receptionInQueueIdx++;
        }

        // 4. 비어있는 접수 창구에 고객 배정 (창구 번호 작은 순)
        for (int i = 1; i <= N; ++i) {
            if (receptionDesks[i].customerIdx == -1 && !receptionWait.empty()) {
                Customer* c = receptionWait.front();
                receptionWait.pop();
                c->receptionId = i;
                receptionDesks[i].customerIdx = c->id;
                receptionDesks[i].remainTime = receptionDesks[i].processTime;
            }
        }

        // 5. 비어있는 정비 창구에 고객 배정 (창구 번호 작은 순)
        for (int i = 1; i <= M; ++i) {
            if (repairDesks[i].customerIdx == -1 && !repairWait.empty()) {
                Customer* c = repairWait.top();
                repairWait.pop();
                c->repairId = i;
                repairDesks[i].customerIdx = c->id;
                repairDesks[i].remainTime = repairDesks[i].processTime;
            }
        }
        time++;
    }

    // 결과 계산: 접수 창구 A와 정비 창구 B를 모두 이용한 고객 ID 합
    long long ans = 0;
    bool found = false;
    for (int i = 1; i <= K; ++i) {
        if (customers[i].receptionId == A && customers[i].repairId == B) {
            ans += customers[i].id;
            found = true;
        }
    }

    cout << '#' << tc << ' ' << (found ? ans : -1) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    for (int i = 1; i <= T; ++i) {
        solve(i);
    }

    return 0;
}