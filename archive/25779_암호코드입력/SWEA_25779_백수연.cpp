
#include <iostream>
#include <queue>

using namespace std;

/*
아이디어?
순차적으로 입력하기 아니면 입력 안하기 밖에 없어서
그냥 앞에서 모든 데이터를 비교하도록 했습니다.

굳이 큐를 이용해봤습니다.
먼가...갑자기 string이 생각이 안나서...
근데 두 코드의 속도는 똑같네영
*/

void solve_queue(int tc)
{
    // 입력할 수 있는 숫자 개수(N) 입력
    int N;
    cin >> N;

    // queue에 N개의 숫자 입력
    string num;
    cin >> num;

    queue<int> user_input;
    for (int j = 0; j < N; j++)
    {
        user_input.push(num[j] - '0');
    }
    
    // 암호코드 숫자 개수(M) 입력
    int M;
    cin >> M;

    cin >> num;
    queue<int> password;
    for (int j = 0; j < M; j++)
    {
        password.push(num[j] - '0');
    }

    // 암호 코드 비교
    while (!user_input.empty() && !password.empty())
    {
        int input = user_input.front();
        int pwd = password.front();

        if (input == pwd)
        {   
            password.pop();
        }

        user_input.pop();
    }

    // 결과 출력
    if (password.empty())
    {
        cout << "#" << tc << " " << 1 << endl;
    }
    else
    {
        cout << "#" << tc << " " << 0 << endl;
    }
}


void solve_string(int tc)
{
    int N;
    cin >> N;

    string userinput;
    cin >> userinput;

    int M;
    cin >> M;

    string password;
    cin >> password;

    int idx = 0;
    for (int j = 0; j < userinput.size(); j++)
    {
        if (idx < password.size() && userinput[j] == password[idx])
        {
            idx += 1;
        }
    }

    if (idx == password.size())
    {
        cout << "#" << tc << " " << 1 << "\n";
    }
    else
    {
        cout << "#" << tc << " " << 0 << "\n";
    }
}

int main ()
{
    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve_queue(i);
        // solve_string(i);
    }

    return 0;
}