#include <iostream>
#include <vector>

using std::vector;

// 테이블 만들기
vector<vector<int>> maketable(int n)
{
    vector<vector<int>> table(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int fly = 0;
            std::cin >> fly;
            table[i][j] = fly;
        }
    }

    return table;
}

// 누적합
// 가로 행 누적합 구한 후에 세로 열 누적합을 구합니다
vector<vector<int>> makeprefixsum(int n, vector<vector<int>> table)
{
    vector<vector<int>> prefixsum_table_1d(n, vector<int>(n));
    vector<vector<int>> prefixsum_table_2d(n, vector<int>(n));

    // 행 누적합
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += table[i][j];
            prefixsum_table_1d[i][j] = sum;
        }
    }


    // 열 누적합
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += prefixsum_table_1d[j][i];
            prefixsum_table_2d[j][i] = sum;
        }
    }
    return prefixsum_table_2d;
}

// 문제 해결부 - 완전 탐색
void solve(int tc)
{
    int n = 0; // 테이블 크기
    int m = 0; // 파리채 크기
    std::cin >> n >> m;

    vector<vector<int>> table = maketable(n);

    // 파리 잡기
    int maxkill = 0;
    // 전체 테이블 순회(파리채 크기만큼 미리 뺌)
    for (int i = 0; i < n - m + 1; i++)
    {
        for (int j = 0; j < n - m + 1; j++)
        {   
            int kill = 0;

            // 파리채 범위 순회
            for (int k = 0; k < m; k++)
            {
                for (int l = 0; l < m; l++)
                {
                    kill += table[i + k][j + l];
                }
            }

            if (kill > maxkill)
            {
                maxkill = kill;
            }
        }
    }

    std::cout << '#' << tc << ' ' << maxkill << '\n';

    return;
}


// 문제 해결부 - 2d 누적합
void solve_prefixsum(int tc)
{
    int n = 0; // 테이블 크기
    int m = 0; // 파리채 크기
    std::cin >> n >> m;

    vector<vector<int>> table = maketable(n);
    vector<vector<int>> prefixsum_table = makeprefixsum(n, table);

    int maxkill = 0;
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int kill = prefixsum_table[i][j];

            // 여기는 제미나이 도움을 받았습니다
            // m x m에 포함안되는 영역을 어떻게 빼줘야할지 못세워서
            // 누적합 어렵네영,,,
            
            // 1. 위쪽 영역이 존재하면 뺀다
            if (i - m >= 0) {
                kill -= prefixsum_table[i - m][j];
            }

            // 2. 왼쪽 영역이 존재하면 뺀다
            if (j - m >= 0) {
                kill -= prefixsum_table[i][j - m];
            }

            // 3. 위쪽과 왼쪽을 모두 뺐다면, 중복으로 빠진 대각선 귀퉁이를 다시 더한다
            if (i - m >= 0 && j - m >= 0) {
            kill += prefixsum_table[i - m][j - m];
            }

            // 이제 최종 검사
            if (kill > maxkill) maxkill = kill;
        }
    }

    std::cout << '#' << tc << ' ' << maxkill << '\n';

    return;

}

// 문제 입력부
int main ()
{
    int tc = 0;
    std::cin >> tc;

    for (int i = 1; i < tc + 1; i++)
    {
        // solve(i); // 완전탐색 - 내가 냅다 푼 것
        solve_prefixsum(i); // 2D 누적합 - 제미나이 힌트받음
    }

    return 0;
}