#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::ios;

// 6: 바퀴 갯수 + 튀어나감,, 방지,,,2
// 9: 톱날 갯수(8) + 각 톱니 빨간색 화살표 위치(1)
vector<vector<int>> wheel(6, vector<int>(9));
vector<int> WHEELS_DIR(6); // 각 바퀴를 무슨 방향으로 돌릴지
vector<int> visited(6); // 각 바퀴를 이미 비교 했는지

void wheel_check(int num)
{
    visited[num] = 1; // 방문처리

    int center_top = wheel[num][8];
    
    // 오른쪽
    int right_top = wheel[num + 1][8];
    if (visited[num + 1] != 1)
    {
        if (wheel[num][(center_top + 2) % 8] != wheel[num + 1][(right_top + 6) % 8])
        {
            WHEELS_DIR[num + 1] = WHEELS_DIR[num] * (-1); // 반대로 회전
            wheel_check(num + 1);
        }
    }

    // 왼쪽
    int left_top = wheel[num - 1][8];
    if (visited[num - 1] != 1)
    {
        if (wheel[num][(center_top + 6) % 8] != wheel[num - 1][(left_top + 2) % 8])
        {
            WHEELS_DIR[num - 1] = WHEELS_DIR[num] * (-1); // 반대로 회전
            wheel_check(num - 1);
        }
    }

}


void solve (int tc)
{
    int K; // 회전 횟수
    cin >> K;

    for (int i = 1; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> wheel[i][j];
        }

        wheel[i][8] = 0; // 빨간색 화살표 위치, 즉 각 바퀴의 top
    }

    // 회전
    for (int i = 0; i < K; i++)
    {
        WHEELS_DIR = {0,0,0,0,0,0}; // 초기화
        visited = {1,0,0,0,0,1}; // 
        
        int num, dir;
        cin >> num >> dir;

        WHEELS_DIR[num] = dir;

        // 돌릴지 말지 확인
        wheel_check(num);

        // 돌려!!!!!!!
        for (int j = 1; j < 5; j++)
        {
            int now_top = wheel[j][8];
            wheel[j][8] = (now_top - (WHEELS_DIR[j]) + 8) % 8;
        }
    }

    // 점수 계산
    int score = 0;
    for (int i = 1; i < 5; i++)
    {
        int top = wheel[i][8];
        score += wheel[i][top] * pow(2, i - 1);
    }

    cout << '#' << tc << ' ' << score << '\n';

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