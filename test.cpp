#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::vector;
using ::std::abs;
using ::std::max;
using ::std::min;
using ::std::sort;

struct Pos {
    int r, c;
};

struct Stair {
    int r, c, k;
};

// 전역 변수 설정
int N, minTime;
vector<Pos> people;
vector<Stair> stairs;
int choice[11]; // 각 사람이 선택한 계단 번호 (0 또는 1)

// 특정 계단에 배정된 사람들이 모두 내려가는 시간 계산 로직
int calculateTime(int stairIdx, const vector<int>& arrivals) {
    if (arrivals.empty()) return 0;

    // 도착 시간 순으로 정렬 (먼저 도착한 사람부터 계단 진입)
    vector<int> sortedArrivals = arrivals;
    sort(sortedArrivals.begin(), sortedArrivals.end());

    int K = stairs[stairIdx].k;
    vector<int> startTimes(sortedArrivals.size());

    for (int i = 0; i < (int)sortedArrivals.size(); ++i) {
        int readyToEnter = sortedArrivals[i] + 1; // 도착 1분 후 진입 가능

        if (i < 3) {
            // 계단에 자리가 있는 경우(최대 3명) 바로 진입
            startTimes[i] = readyToEnter;
        } else {
            // 자리가 없는 경우: 3명 전 사람이 나가는 시간과 내가 준비된 시간 중 늦은 시간 선택
            int waitFinish = startTimes[i - 3] + K;
            startTimes[i] = max(readyToEnter, waitFinish);
        }
    }

    // 마지막 사람이 계단을 완전히 내려가는 시간(진입 시간 + 계단 길이 K)을 반환
    return startTimes.back() + K;
}

// DFS를 이용해 모든 사람에게 계단을 배정하는 모든 경우의 수 탐색 (2^P)
void dfs(int idx) {
    if (idx == (int)people.size()) {
        vector<int> group0, group1;
        for (int i = 0; i < (int)people.size(); ++i) {
            // 맨해튼 거리 계산
            int dist = abs(people[i].r - stairs[choice[i]].r) + abs(people[i].c - stairs[choice[i]].c);
            if (choice[i] == 0) group0.push_back(dist);
            else group1.push_back(dist);
        }

        int time0 = calculateTime(0, group0);
        int time1 = calculateTime(1, group1);

        // 두 계단 중 더 늦게 끝나는 시간이 전체 완료 시간
        minTime = min(minTime, max(time0, time1));
        return;
    }

    // 현재 사람을 0번 계단에 배정
    choice[idx] = 0;
    dfs(idx + 1);

    // 현재 사람을 1번 계단에 배정
    choice[idx] = 1;
    dfs(idx + 1);
}

void solve(int tc) {
    cin >> N;
    people.clear();
    stairs.clear();

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int val; cin >> val;
            if (val == 1) people.push_back({ i, j });
            else if (val >= 2) stairs.push_back({ i, j, val });
        }
    }

    minTime = 1e9; // 최솟값 초기화
    dfs(0);

    cout << "#" << tc << " " << minTime << "\n";
}

int main() {
    // 입출력 최적화
    ::std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    for (int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}