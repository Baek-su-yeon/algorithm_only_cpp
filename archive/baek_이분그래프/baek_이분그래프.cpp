#include <iostream>
#include <vector>

using namespace std;

bool DFS (vector<vector<int>>& connect, vector<int>& visited, int node, int color)
{
    visited[node] = color;

    for (int i = 0; i < connect[node].size(); i++)
    {
        int next = connect[node][i];
        if(!visited[next]) // 방문 안함
        {
            // 반대색 표시
            if (!DFS (connect, visited, next, 3 - color)) return false;
        }
        else if (visited[next] == color) return false; // 색이 겹침
    }

    return true; // 싸이클이 없음
}

void solve ()
{
    int v, e; // 정점 개수, 간선 개수
    cin >> v >> e;

    // 연결 리스트
    vector<vector<int>> connect (v + 1);
    vector<int> visited (v + 1);

    // 간선 연결
    int x, y;
    for (int i = 0; i < e; i++)
    {
        cin >> x >> y;
        connect[x].push_back(y);
        connect[y].push_back(x);
    }

    bool possible = true;
    for (int i = 0; i <= v; i++)
    {
        if (visited[i] == 0)
        {
            if (!DFS(connect, visited, i, 1))
            {
                possible = false;
                break;
            }
        }
    }

    if (possible) cout << "YES\n";
    else cout << "NO\n";

    return;
}

int main ()
{
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }

    return 0;
}