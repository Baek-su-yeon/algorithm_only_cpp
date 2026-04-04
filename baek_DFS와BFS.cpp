#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

bool dfs_visited[1001];

void DFS (vector<vector<int>>& connect, int start, int node_num)
{
    vector<bool> visited (node_num + 1, false);
    deque<int> dfs_stack;

    dfs_stack.push_back(start);

    while(!dfs_stack.empty())
    {
        int node = dfs_stack.back();
        dfs_stack.pop_back();

        if (visited[node]) continue; // 이미 방문
        cout << node << ' ';
        visited[node] = true; // 방문 처리

        sort(connect[node].begin(), connect[node].end(), greater<int>());

        for (int i = 0; i < connect[node].size(); i++)
        {
            int next = connect[node][i];
            if (!visited[next]) dfs_stack.push_back(next);            
        }
    }

    return;
}

void DFS_recursion (vector<vector<int>>& connect, int node)
{
    if (dfs_visited[node]) return;

    cout << node << " ";
    dfs_visited[node] = true;

    sort(connect[node].begin(), connect[node].end());

    for (int i = 0; i < connect[node].size(); i++)
    {
        int next = connect[node][i];
        if(!dfs_visited[next]) DFS_recursion(connect, next);
    }
}

void BFS (vector<vector<int>>& connect, int start, int node_num)
{
    vector<bool> visited (node_num + 1, false);
    deque<int> bfs_queue;

    bfs_queue.push_back(start);

    while(!bfs_queue.empty())
    {
        int node = bfs_queue.front();
        bfs_queue.pop_front();

        if(visited[node]) continue;
        cout<< node << ' ';
        visited[node] = true;

        sort(connect[node].begin(), connect[node].end());

        for (int i = 0; i < connect[node].size(); i++)
        {
            int next = connect[node][i];
            if(!visited[next]) bfs_queue.push_back(next);
        }
    }

    return;
}

int main ()
{   
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // n: 정점개수, m: 간선개수, v: 정점번호
    int n, m, v;
    cin >> n >> m >> v;

    // 연결 리스트 생성, 정점 개수가 1부터 있으므로
    vector<vector<int>> connect (n + 1);

    // 양방향 연결
    int start, end = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> start >> end;

        connect[start].push_back(end);
        connect[end].push_back(start);
    }

    // 내림차순 정리
    // DFS(connect, v, n);
    DFS_recursion(connect, v);
    cout << "\n";

    // 오름차순 정리
    BFS(connect, v, n);
    cout << "\n";

    return 0;
}