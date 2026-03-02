#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::ios;
using std::max;
using std::min;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;

        vector<int> carrots(N);
        for (int i = 0; i < N; i++) {
            cin >> carrots[i];
        }

        // 정렬 백터 시작부터 끝(다음)까지 넣어줘야함.
        sort(carrots.begin(), carrots.end());
        // 최소값 받을 변수
        int min_diff = 21e8;
        // 포장 가능 여부
        bool possible = false;

        // 두 개의 경계값을 정함
        for (int i = 0; i < N - 2; i++) {
            for (int j = i + 1; j < N - 1; j++) {
                
                // 같은 크기의 당근은 같은 상자에 있어야 함
                if (carrots[i] == carrots[i+1] || carrots[j] == carrots[j+1]) {
                    continue;
                }

                // 각 상자의 개수 계산
                int small_count = i + 1;
                int medium_count = j - i;
                int large_count = N - 1 - j;

                // 한 상자가 당근 갯수 절반 넘으면 안된다.
                if (small_count > N / 2 || medium_count > N / 2 || large_count > N / 2) {
                    continue;
                }
                // 빈 상자가 없어야함.
                if (small_count == 0 || medium_count == 0 || large_count == 0) {
                    continue;
                }

                int max_count = max({small_count, medium_count, large_count});
                int min_count = min({small_count, medium_count, large_count});

                if (min_diff > (max_count - min_count)) {
                    min_diff = max_count - min_count;
                    possible = true;
                }
            }
        }

        // 포장 불가능하면 -1
        if (!possible || min_diff == 21e8) {
            cout << "#" << test_case << " -1" << "\n";
        } else {
            cout << "#" << test_case << " " << min_diff << "\n";
        }
    }

    return 0;
}