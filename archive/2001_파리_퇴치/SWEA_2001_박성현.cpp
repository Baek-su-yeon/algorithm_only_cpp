#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::vector;

// 테스트 케이스 개수
int T;
// 배열 크기 NxN
int N; // 5 <= N <= 15
// 탐색 하고자 하는 칸의 크기 MxM
int M; // 2 <= M <= N

int main(){
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for(int time=1; time < T+1; time++){
        // N, M 값 입력받기
        cin >> N >> M;
        vector<vector<int>> map(N, vector<int>(N));

        // 벡터 자체 배열 
        for(int i=0; i<N; i++){
            // 벡터 내부 배열
            for(int j=0; j<N; j++){
                cin >> map[i][j];
            }
        }

        int result = 0;
        // N-M+1
        for(int x=0; x<N-M+1; x++){
            // N-M+1
            for(int y=0; y<N-M+1; y++){
                int sumValue = 0;
                // MxM 크기만큼 값을 차례대로 더해줘야한다.
                for(int k=0; k<M; k++){
                    for(int p=0; p<M; p++){
                        // 값 더하기
                        sumValue += map[x+k][y+p];
                    }
                }
                // 최종 비교 - 이전 값보다 작으면 패스
                if(sumValue<result){
                    continue;
                // 이전 값보다 크면 교체
                } else {
                    result = sumValue;
                }
            }
        }
        cout << "#" << time << " " << result << endl;
    }
    return 0;
}

