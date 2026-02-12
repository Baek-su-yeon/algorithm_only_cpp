#include <iostream>
#include <algorithm>

using namespace std;

void solve(int tc)
{
    int A, B, C;
    cin >> A >> B >> C;

    int eaten = 0;

    // 1. B가 C보다 작아지도록 조정 (B < C)
    if (B >= C) {
        int diff = B - (C - 1);
        eaten += diff;
        B = C - 1;
    }

    // 2. A가 B보다 작아지도록 조정 (A < B)
    if (A >= B) {
        int diff = A - (B - 1);
        eaten += diff;
        A = B - 1;
    }

    // 3. 모든 상자에 사탕이 1개 이상 있는지 확인
    // B가 C-1이 되었을 때 B < 1이거나, A가 B-1이 되었을 때 A < 1이면 불가능
    if (A < 1 || B < 1 || C < 1) {
        cout << "#" << tc << " -1" << endl;
    } else {
        cout << "#" << tc << " " << eaten << endl;
    }
}

int main()
{
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        solve(i);
    }

    return 0;
}