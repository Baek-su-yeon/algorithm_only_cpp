#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::ios;
using std::vector;
using std::max;


/*
입력
첫 줄에 사진 데이터의 개수, 다음 줄부터 사진 데이터 별로 첫 줄에 N과 M, 이후 N개의 줄에 M개씩의 데이터가 제공된다.
(3<=N, M<=100)
*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    
    int T=0;

    cin >> T;

    for(int time=1; time < T+1; time++){
        int N;
        int M;

        int sum = 0; // 연속된 최대 값
        // 초기화를 잘못된 줄에서 해서 테스트 케이스 틀림.
        int result = 0; // 최종 결과 값

        cin >> N >> M;

        // NxM 크기의 사진 
        vector<vector<int>> picture(N, vector<int>(M, 0));

        // 배열 입력
        for(int i = 0; i < N; i++){
            sum = 0;
            // 한줄 단위로 계산하면서 입력받기
            for(int j=0; j< M; j++){
                cin >> picture[i][j];
                // 입력 받으면서 연속된 1 갯수 세기
                if(picture[i][j]){
                    sum += 1;
                    // cout << i << "|" << j << "|" << "sum : " << sum << "\n";
                    result = max(result, sum);
                } else {
                    sum = 0;
                }
            }
        }
        
        // NxM 세로 탐색
        for(int i = 0; i < M; i++){
            sum = 0;
            // 세로로 탐색하면서 기둥 개수 세기
            for(int j=0; j< N; j++){
                if(picture[j][i]){
                    sum += 1;
                    // cout << j << "|" << i << "|" << "sum : " << sum << "\n";
                    result = max(result, sum);
                } else {
                    sum = 0;
                }
            }
        }
        cout << "#" << time << " " << result << "\n";
    }
}