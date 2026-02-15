#include <iostream>
#include <vector>
#include <string>
#include <set>

using ::std::cin;
using ::std::cout;
using ::std::string;
using ::std::ios;
using ::std::set;
using ::std::greater;
using ::std::stoi;

int N, K;
int result; 

int solve() {
    // password 입력
    string password;
    cin >> password;

    set<string, greater<string>> setPassword;
    
    // 한 변에 적힌 글자 수
    int len = N / 4; 
    
    // 슬라이딩 윈도우
    string doublePassword = password+password;

    // 시작부터 len-1까지 반복 - 0 -> N
    for(int start=0; start < len; start++){
        // 상자의 4개 변을 각각 자르기
        for(int i = 0; i < 4; i++) {
            // i * len 위치부터 len 개수만큼 자르기
            string slicePassword = doublePassword.substr(start + i * len, len);
            setPassword.insert(slicePassword);
        }
    }

    // 처음 사용해보는 포인터 
    /* ------------------------------------------------------ */
    // 가장 큰 값을 가리키는 손가락(Iterator) 생성
    auto iterator = setPassword.begin();

    // K번째를 찾기 위해 K-1번만큼 옆으로 이동
    for(int i = 0; i < K - 1; i++) {
        iterator++; 
    }

    // 3손가락이 가리키는 곳의 진짜 값(문자열) 빼오기
    string kth_str = *iterator;
    /* ------------------------------------------------------ */

    return stoi(kth_str, nullptr, 16);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T = 0;
    cin >> T;
    
    for(int time = 1; time <= T; time++){
        
        cin >> N >> K;
        result = solve(); // 함수 호출

        cout << "#" << time << " " << result << "\n";
    }
    return 0;
}