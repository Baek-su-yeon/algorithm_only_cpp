#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::abs;
using ::std::vector;
using ::std::sort;
using ::std::max;
using ::std::min;

struct Pos {
    int r, c;
};

struct Stair
{
    int r, c, l;
};

vector<Pos> PEOPLE;
vector<Stair> STAIRS;
int CHOICE[11];
int MINTIME;

int movedist (int pr, int pc, int sr, int sc)
{
    return abs(pr - sr) + abs(pc - sc);
}

int movetime (int length, vector<int> group)
{
    if (group.empty()) return 0; // 모든 사람이 0이나 1로 갔을 때

    // 오름차순 정렬, 먼저 도착한 사람부터 계단 들어가기
    sort(group.begin(), group.end());

    vector<int> down_start_time(group.size());
    for (int i = 0; i < group.size(); i++)
    {
        int ready = group[i] + 1; // 도착 후 1분 뒤 계단 내려감

        if (i < 3) down_start_time[i] = ready; // 3명 안차서 바로 내려감
        else
        {
            int wait = down_start_time[i - 3] + length; // 제일 첫 사람이 내려갈 때까지 기다림
            down_start_time[i] = max(wait, ready); // 첫 사람이 나가고 바로 들어갈 수 있는 경우와 거리가 멀어서 이미 3명이 다 나간 경우를 가림
        }
    }

    return down_start_time.back() + length;
}

void stairchoice (int idx)
{
    // 조합 끝
    if (idx == PEOPLE.size())
    {
        vector<int> stair0group, stair1group;
        for (int i = 0; i < PEOPLE.size(); i++)
        {
            int dist = movedist(PEOPLE[i].r, PEOPLE[i].c, STAIRS[CHOICE[i]].r, STAIRS[CHOICE[i]].c);
            if (!CHOICE[i]) stair0group.push_back(dist);
            else stair1group.push_back(dist);
        }

        int stair0time = movetime(STAIRS[0].l, stair0group);
        int stair1time = movetime(STAIRS[1].l, stair1group);
        
        MINTIME = min(MINTIME, max(stair0time, stair1time)); // 어차피 제일 마지막 사람이 내려와야 끝나므로 최대값고름
        
        return;
    }

    // 조합 시작
    CHOICE[idx] = 0;
    stairchoice(idx + 1);

    CHOICE[idx] = 1;
    stairchoice(idx + 1);
}

void solve (int tc)
{
    int N;
    cin >> N;

    PEOPLE.clear();
    STAIRS.clear();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int state;
            cin >> state;

            if (state == 1) PEOPLE.push_back({i, j});
            else if (state >= 2) STAIRS.push_back({i, j, state});
        }
    }

    MINTIME = 1e9;
    stairchoice(0);

    cout << '#' << tc << ' ' << MINTIME << '\n';

    return;
}

int main ()
{   
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}