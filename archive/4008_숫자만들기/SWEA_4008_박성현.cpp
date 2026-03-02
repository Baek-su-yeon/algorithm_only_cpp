#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::ios;
using std::vector;
using std::max;
using std::min;

int N;
int min_val;
int max_val;
vector<int> numbers;

void dfs(int idx, int current_value, int plus, int minus, int mul, int div) {
    // 모든 숫자를 다 사용한 경우
    if (idx == N) {
        max_val = max(max_val, current_value);
        min_val = min(min_val, current_value);
        return;
    }

    // 연산자가 남아있다면 사용하고 다음 단계로 이동
    if (plus > 0)  dfs(idx + 1, current_value + numbers[idx], plus - 1, minus, mul, div);
    if (minus > 0) dfs(idx + 1, current_value - numbers[idx], plus, minus - 1, mul, div);
    if (mul > 0)   dfs(idx + 1, current_value * numbers[idx], plus, minus, mul - 1, div);
    if (div > 0)   dfs(idx + 1, current_value / numbers[idx], plus, minus, mul, div - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T = 0;
    cin >> T;

    for(int time = 1; time < T + 1; time++) {
        // 숫자 개수
        N = 0;
        cin >> N;

        // 최소값, 최대값 초기화
        min_val = 1e9;
        max_val = -1e9;

        // 연산자 +, -, *, /
        vector<int> oprerators(4);

        for(int i = 0; i < 4; i++){
            cin >> oprerators[i];
        }

        // 숫자 리스트 - 배열의 크기를 재할당 하는 함수
        numbers.resize(N);

        for(int i = 0; i < N; i++){
            cin >> numbers[i];
        }

        // DFS 탐색
        dfs(1, numbers[0], oprerators[0], oprerators[1], oprerators[2], oprerators[3]);
        cout << "#" << time << " " << max_val - min_val << "\n";
    }
    return 0;
}