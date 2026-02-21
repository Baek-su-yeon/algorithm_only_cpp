#include <iostream>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::vector;

struct Microbe {
    int r, c;   // 위치 (행, 열)
    int cnt;    // 미생물 수
    int dir;    // 이동 방향

    // 정렬 기준 만들기: sort() 함수를 실행하면 이 기준에 따라 1. 위쪽부터, 2. 왼쪽부터, 3. 덩치가 큰 순서대로 리스트가 정렬
    // 1순위: 행 오름차순
    // 2순위: 열 오름차순 (같은 위치끼리 모음)
    // 3순위: 미생물 수 '내림차순'
    bool operator<(const Microbe& other) const {
        if (r != other.r) return r < other.r;
        if (c != other.c) return c < other.c;
        return cnt > other.cnt; 
    }
};

int N, M, K;
vector<Microbe> microbes;

// 방향: 0(안씀), 1(상), 2(하), 3(좌), 4(우)
int di[5] = {0, -1, 1, 0, 0};
int dj[5] = {0, 0, 0, -1, 1};

// 약품에 닿았을 때 반대 방향으로 바꿔주는 배열 (1->2, 2->1, 3->4, 4->3)
int rev_dir[5] = {0, 2, 1, 4, 3};

void inputValue() {
    cin >> N >> M >> K;
    microbes.clear();
    
    for (int i = 0; i < K; i++) {
        int r, c, cnt, dir;
        cin >> r >> c >> cnt >> dir;
        microbes.push_back({r, c, cnt, dir});
    }
}

void solve() {
    // M시간 동안 시뮬레이션
    for (int time = 0; time < M; time++) {
        
        // 모든 미생물 이동 및 약품(가장자리) 체크
        for (auto& m : microbes) {
            m.r += di[m.dir];
            m.c += dj[m.dir];

            // 가장자리(약품)에 닿은 경우
            if (m.r == 0 || m.r == N - 1 || m.c == 0 || m.c == N - 1) {
                // 미생물 수 반토막
                m.cnt /= 2;
                // 방향 반대로
                m.dir = rev_dir[m.dir];
            }
        }

        // 위치가 겹치는 군집들을 하나로 모으기 위해 정렬
        sort(microbes.begin(), microbes.end());

        vector<Microbe> next_microbes;
        
        // 겹치는 군집 합치기 로직
        for (int i = 0; i < microbes.size(); i++) {
            // 약품에 닿아 0마리가 된 군집 처리
            if (microbes[i].cnt == 0) continue;

            Microbe current = microbes[i];

            // 내 바로 다음 배열에 있는 미생물이 나와 같은 위치라면 -> 겹친 상황
            while (i + 1 < microbes.size() && microbes[i+1].r == current.r && microbes[i+1].c == current.c) {
                // 덩치를 합침
                current.cnt += microbes[i+1].cnt; 
                // 합쳐진 군집은 이미 흡수했으니 건너뛰기
                i++; 
            }

            next_microbes.push_back(current); // 살아남은 군집들을 새로운 리스트에 저장
        }

        // 새롭게 정리된 군집들로 갱신
        microbes = next_microbes;
    }

    // M시간 종료 후 살아남은 미생물 총합 계산
    int total_cnt = 0;
    for (const auto& m : microbes) {
        total_cnt += m.cnt;
    }
    cout << total_cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        inputValue();
        cout << "#" << tc << " ";
        solve();
    }
    return 0;
}