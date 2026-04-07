#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

bool visited[100][100];
int row_dir[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int col_dir[4] = {0, 0, -1, 1}; // 상, 하, 좌, 우

void DFS(vector<vector<char>>& art, int row, int col, int size)
{
    visited[row][col] = true;

    for (int i = 0; i < 4; i++)
    {
        int nr = row + row_dir[i];
        int nc = col + col_dir[i];

        if (nr < 0 || nr >= size || nc < 0 || nc >= size) continue;

        if (art[row][col] == art[nr][nc] && !visited[nr][nc])
        {
            DFS(art, nr, nc, size);
        }
    }

    return;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<vector<char>> art (n, vector<char> (n));
    vector<vector<char>> abnormal_art (n, vector<char> (n));


    // 그림 그리기
    string row;
    for (int i = 0; i < n; i++)
    {
        cin >> row;
        for (int j = 0; j < row.size(); j++)
        {
            art[i][j] = row[j];

            if (row[j] == 'G') abnormal_art[i][j] = 'R';
            else abnormal_art[i][j] = row[j];
        }
    }

    // 그림 분석하기
    int section = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(!visited[i][j])
            {
                DFS(art, i, j, n);
                section ++;
            }
        }
    }
    cout << section << " ";
    
    memset (visited, false, sizeof(visited));
    
    section = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(!visited[i][j])
            {
                DFS(abnormal_art, i, j, n);
                section ++;
            }
        }
    }
    cout << section << "\n";

    return 0;
}