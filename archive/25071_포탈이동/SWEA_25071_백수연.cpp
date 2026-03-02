#include <iostream>
#include <vector>

using namespace std;

void testcase(int tc)
{
    int N;
    cin >> N;

    // 포탈 정보를 담을 배열 (1번 방부터 시작하므로 N+1 크기)
    vector<int> potal(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> potal[i];
    }

    // 각 방의 첫 방문 여부를 체크할 배열
    vector<bool> visited(N + 1, false);
    
    int current = 1; // 시작은 1번 방
    int count = 0; // 포탈 사용 횟수

    // 마지막 N번 방에 도달할 때까지 반복
    while (current < N) {
        count++;

        // 규칙 4: 1번 방은 방문 여부 상관없이 무조건 2번 방으로
        if (current == 1)
        {
            current = 2;
        }

        // 규칙 2: 처음 방문하는 방이라면 Pi 번 방으로 이동
        else if (!visited[current])
        {
            visited[current] = true; // 방문 표시
            current = potal[current];
        }

        // 규칙 3: 처음 방문이 아니라면 i+1 번 방으로 이동
        else
        {
            current = current + 1;
        }
    }

    // 결과 출력
    cout << "#" << tc << " " << count << endl;
}

int main() {

    int T;
    std::cin >> T;

    for (int i = 1; i <= T; i++) {
        testcase(i);
    }

    return 0;
}