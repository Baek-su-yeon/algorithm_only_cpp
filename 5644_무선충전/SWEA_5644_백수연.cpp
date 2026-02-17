#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// BC 정보를 담을 구조체
struct BC
{
    int x, y, range, power;
};

int M, A;
int pathA[101], pathB[101];
vector<BC> bcs;

// 방향: 제자리, 상, 우, 하, 좌
int dx[] = {0, 0, 1, 0, -1};
int dy[] = {0, -1, 0, 1, 0};

// 거리 계산 함수: D = |X1 - X2| + |Y1 - Y2|
int get_dist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// 현재 위치에서 최대로 충전할 수 있는 양을 계산
int get_max_charge(int ax, int ay, int bx, int by)
{
    int max_val = 0;

    // 접속 가능한 BC 후보군 찾기
    vector<int> listA, listB;
    for (int i = 0; i < A; i++)
    {
        if (get_dist(ax, ay, bcs[i].x, bcs[i].y) <= bcs[i].range) listA.push_back(i);
        if (get_dist(bx, by, bcs[i].x, bcs[i].y) <= bcs[i].range) listB.push_back(i);
    }

    // 아무것도 접속 못할 경우를 위해 빈 값 추가 (인덱스 대신 -1)
    if (listA.empty()) listA.push_back(-1);
    if (listB.empty()) listB.push_back(-1);

    // 모든 조합 탐색 (A가 선택한 BC i, B가 선택한 BC j)
    for (int a_idx : listA)
    {
        for (int b_idx : listB)
        {
            int current_sum = 0;
            
            if (a_idx == b_idx && a_idx != -1)
            {
                // 같은 BC에 접속한 경우: 나눠 갖지만 결국 총합은 해당 BC의 Power 하나와 같음
                current_sum = bcs[a_idx].power; 
            }
            else
            {
                // 서로 다른 BC거나 한쪽이 접속 안 한 경우
                if (a_idx != -1) current_sum += bcs[a_idx].power;
                if (b_idx != -1) current_sum += bcs[b_idx].power;
            }
            max_val = max(max_val, current_sum);
        }
    }
    return max_val;
}

void solve(int tc)
{
    cin >> M >> A;
    bcs.clear();

    for (int i = 0; i < M; i++) cin >> pathA[i];
    for (int i = 0; i < M; i++) cin >> pathB[i];

    for (int i = 0; i < A; i++)
    {
        int x, y, c, p;
        cin >> x >> y >> c >> p;
        bcs.push_back({x, y, c, p});
    }

    int ax = 1, ay = 1, bx = 10, by = 10;
    int total_charge = 0;

    // 0초부터 M초까지 시뮬레이션
    for (int t = 0; t <= M; t++)
    {
        // 1. 현재 위치에서 최대 충전량 누적
        total_charge += get_max_charge(ax, ay, bx, by);

        // 2. 이동 (마지막 초에는 이동하지 않음)
        if (t < M) {
            ax += dx[pathA[t]];
            ay += dy[pathA[t]];
            bx += dx[pathB[t]];
            by += dy[pathB[t]];
        }
    }

    cout << "#" << tc << " " << total_charge << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);

    return 0;
}