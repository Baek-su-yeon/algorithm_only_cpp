#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

bool alphabet[91]; // 아스키 코드 대문자 'Z' = 90, 어차피 1번 이상 못가므로 bool로 가능
int row_dir[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int col_dir[4] = {0, 0, -1, 1}; // 상, 하, 좌, 우
int max_len = 0;


void DFS (vector<vector<char>>& board, int row, int col, int length, int row_size, int col_size)
{
    alphabet[int(board[row][col])] = true;

    for (int i = 0; i < 4; i++)
    {
        int nr = row + row_dir[i];
        int nc = col + col_dir[i];

        if (nr < 0 || nr >= row_size || nc < 0 || nc >= col_size) continue;
        
        int new_alphabet = int(board[nr][nc]);

        // 중복된 알파벳이 아닐 때
        if (!alphabet[new_alphabet])
        {
            DFS(board, nr, nc, length + 1, row_size, col_size);
            alphabet[new_alphabet] = false; // 재귀 끝나고 돌아오면 새로운 길 탐색을 위해 다시 원상복귀
        }
    }

    if (max_len < length) max_len = length;

    return;
}

int main ()
{
    // 전역 변수 초기화 
    memset(alphabet, false, sizeof(alphabet));
    max_len = 0;

    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    cin >> r >> c;

    vector<vector<char>> board (r, vector<char>(c));

    string alphabets;
    for (int i = 0; i < r; i++)
    {
        cin >> alphabets;
        for(int j = 0; j < c; j++) board[i][j] = alphabets[j];
    }

    DFS(board, 0, 0, 1, r, c);

    cout << max_len << "\n";

    return 0;
}