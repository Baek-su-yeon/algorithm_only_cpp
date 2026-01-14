/*
아이디어
N개의 숫자열 하나씩 순회하며 M자리 암호문 체크

암호문의 idx 번째 숫자가 N자리 숫자열에 포함되는지 확인(앞에서부터)
찾았다면 idx+1 번째 숫자를 그 다음부터 확인

순서가 고정이기 때문에 위 방식이 최적일 듯
시간 복잡도: O(N)
*/
// 실행 시간 4ms
// 메모리 396 kb
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 테스트 케이스별 해결 함수
void solve(int t) {
    int N, M;

    // 전체 숫자 개수
    cin >> N;
    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        char temp;
        cin >> temp; // 문자 하나를 읽음 ('1')
        
        // 문자를 숫자로 변환하는 방법: 아스키코드를 사용
        // 문자 '0' 은 아스키코드값 48, '2'는 49 ...
        // 문자열 '0'의 코드값(48)을 빼서 각 문자가 의미하는 정수값만 남김
        sequence[i] = temp - '0'; 
    }
    // 암호문
    cin >> M;
    vector<int> target(M);
    for (int i = 0; i < M; i++) {
        char temp;
        cin >> temp;
        target[i] = temp - '0';
    }

    // 암호문 앞에서부터 하나씩 체크
    // target_idx 가 암호문 길이(M)이 된다면
    // 1을 출력
    int target_idx = 0;
    
    // 주어진 전체 숫자 순회하며
    // 암호문 체크
    for (int i=0; i<N; i++) {
        // 암호문 다 찾았으면 더 이상 탐색하지 않고 중단
        if (target_idx == M) break;

        // 현재 암호문 타겟 숫자를 찾았다면
        // 다음 암호문 숫자를 이어서 탐색
        if (sequence[i] == target[target_idx]) {
            target_idx++;
        }
    }

    // 삼항 연산자
    // 암호문 끝까지 다 돌았다면 1, 아니면 0 출력
    int result = (target_idx == M) ? 1 : 0;

    cout << "#" << t << " " << result << "\n";
}

int main() {
    // 입출력 속도 향상
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int i=1; i<=T; i++) {
        solve(i);
    }
    return 0;
}