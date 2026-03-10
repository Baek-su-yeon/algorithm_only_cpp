#include <iostream>
#include <vector>
#include <utility>

using ::std::cin;
using ::std::cout;
using ::std::vector;
using ::std::pair;
using ::std::ios;

int maxynos[12][12];
int max_cores;
int min_lines;
vector<pair<int, int>> cores;

// 상, 우, 하, 좌: 시계방향
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void dfs (int idx, int corenum, int linenum, int n)
{
    // 종료조건
    if (idx == cores.size())
    {
        // 최대한 많은 전원을 연결했을 때
        if (max_cores < corenum)
        {
            max_cores = corenum;
            min_lines = linenum; // 전선이 최소일 필요 없음
        }
        else if (max_cores == corenum)
        {
            // 그 중에서도 전선의 길이가 가장 작을 때
            if (linenum < min_lines) min_lines = linenum;
        }

        return;
    }

    // 백트레킹
    int rest_cores = cores.size() - idx;
    if (rest_cores + corenum < max_cores) return;

    int r = cores[idx].first;
    int c = cores[idx].second;

    // 4가지 방향 시도
    for (int i = 0; i < 4; i++)
    {
        int line = 0;
        bool can_place = true;
        int nr = r;
        int nc = c;
        
        // 지금 방향에서 끝까지 갈 수 있는지 체크
        while(true)
        {   
            // 한 방향으로 계속 전진
            nr += dr[i];
            nc += dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n) break;
            if (maxynos[nr][nc] != 0)
            {
                can_place = false;
                break;
            }
            line++;
        }

        if (can_place)
        {

            // 전선 깔기
            int line_r = r + dr[i];
            int line_c = c + dc[i];
            for (int j = 0; j < line; j++)
            {
                maxynos[line_r][line_c] = 2;
                line_r += dr[i];
                line_c += dc[i];
            }

            // 다음 코어로 넘어가기
            dfs (idx + 1, corenum + 1, linenum + line, n);

            // 전선 해체
            line_r = r + dr[i];
            line_c = c + dc[i];
            for (int j = 0; j < line; j++)
            {
                maxynos[line_r][line_c] = 0;
                line_r += dr[i];
                line_c += dc[i];
            }
        }
    }

    // 4가지 방향 다 해봤는데 연결이 안되는 경우
    dfs (idx + 1, corenum, linenum, n);
}

void solve (int tc)
{
    cores.clear();

    int N;
    cin >> N;

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int cell;
            cin >> cell;
            maxynos[i][j] = cell;
            if (cell)
            {
                if (i == 0 || i == N - 1 || j == 0 || j == N - 1) count++;
                else cores.push_back({i, j});
            }
        }
    }

    max_cores = 0;
    min_lines = 12 * 12 + 1;
    dfs(0, count, 0, N);

    cout << '#' << tc << ' ' << min_lines << '\n';

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