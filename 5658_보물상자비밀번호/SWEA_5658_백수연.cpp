#include <iostream>
#include <string>
#include <set>

using std::cin;
using std::cout;
using std::string;
using std::set;
using std::hex;
using std::stoul;
using std::ios;

void solve (int tc)
{
    int N, K;
    cin >> N >> K;

    string treasure;
    cin >> treasure;

    set<int> numbers; // 자동 중복 제거, 오름차순 정렬

    // 뚜껑 회전을 위한 반복문
    for (int i = 0; i < N/4; i++)
    {
        // 뚜껑의 각 변에 있는 16진수를 10진수로 저장
        for (int j = 0; j < N - (N/4) + 1; j += (N/4))
        {
            string hex_number = treasure.substr(j, N/4); // 각 변에 있는 숫자만큼 자르고

            unsigned int number = stoul(hex_number, nullptr, 16); // 16진수 문자열을 10진수로 변환

            numbers.insert(number); // 10진수 저장
        }

        string rotate;
        rotate = treasure[N - 1] + treasure.substr(0, N - 1);
        treasure = rotate;
    }


    // K번째로 큰 수 10진수로 출력하기
    // K번째!!!!를 잘 못 이해함!!!!!!!!!
    int count = 0;
    for (int x:numbers)
    {
        // 중요!! 중요!!!!!
        // 중복 없앤 set에서 찾는거지 N 중에 K번째가 아님!!!!
        // 플리즈 띵킹!!!!!!!!!!!!!!!!
        if (count == numbers.size() - K) cout << '#' << tc << ' ' << x << '\n';
        count += 1;
    }

    return;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i < T + 1; i++)
    {
        solve(i);
    }

    return 0;
}