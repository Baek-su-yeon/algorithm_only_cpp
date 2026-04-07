// 웜 바이러스에 걸리게 되는 "컴퓨터의 수"를 출력
// 컴퓨터 대수가 최대 100, 간선이 모든 컴퓨터와 이어지면 100*100 = 10000
// DFS는 재귀로 해도 될 것 같구만.....

// DFS의 시간 복잡도: O(V + E), 그래프 탐색의 시간 복잡도는 보통 정점(V)과 간선(E)의 합
// $$E = \frac{V(V-1)}{2} = \frac{100 \times 99}{2} = 4,950$$

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

bool visited[101];
int computer_num = 0;

void DFS (vector<vector<int>>& connect, int node)
{
    if (visited[node]) return;

    visited[node] = true; // 방문처리
    computer_num += 1;

    for (int i = 0; i < connect[node].size(); i++)
    {
        int next = connect[node][i];
        if(!visited[next]) DFS(connect, next);
    }
}

void BFS (vector<vector<int>>& connect, int start)
{
    deque<int> queue;

    queue.push_back(start);
    visited[start] = true;
    computer_num += 1;

    while(!queue.empty())
    {
        int node = queue.front();
        queue.pop_front();

        for (int i = 0; i < connect[node].size(); i++)
        {
            int next = connect[node][i];
            if (!visited[next])
            {
                visited[next] = true;
                computer_num += 1;
                queue.push_back(next);
            }
        }
    }

}

int main ()
{
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 컴퓨터 수
    int n;
    cin >> n;

    // 간선 수
    int m;
    cin >> m;

    // 연결리스트 생성, n이 1부터 있음
    vector<vector<int>> connect (n + 1);

    // 간선 연결
    int start, end;
    for (int i = 0; i < m; i++)
    {
        cin >> start >> end;
        connect[start].push_back(end);
        connect[end].push_back(start);
    }

    //DFS(connect, 1); // 연결리스트, 시작노드
    BFS(connect, 1);

    cout << computer_num - 1; // 1번은 숙주니까 제외!

    return 0;
}