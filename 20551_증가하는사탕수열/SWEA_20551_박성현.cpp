#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::ios;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("sample_input.txt", "r", stdin);
    
    int T;
    cin >> T;
    
    for(int time=1; time<T+1; time++){
        int result = 0;
        vector<int> candy(3, 0);
        // 변수 입력 
        for(int i=0; i<3; i++){
            cin >> candy[i];
        }

        // 순차 조건 성립 불가
        if(!(candy[1]>1&&candy[2]>2)){
            cout << "#" << time << " " << -1 << "\n";
        } 
        // 최소 조건 만족
        else {
            // 2번째 요소가 3번째 요소보다 크거나 같은 경우
            if(candy[1] >= candy[2]){
                // 2번째 요소 3번째 요소보다 1 작으면 된다.
                result += (candy[1] - candy[2]) + 1;
                candy[1] -= result;
            }
            // 1번째 요소가 2번째 요소보다 크거나 같은 경우
            if(candy[0] >= candy[1]){
                // 1번째 요소 2번째 요소보다 1 작으면 된다.
                result += (candy[0] - candy[1]) + 1;
            }
            cout << "#" << time << " " << result << "\n";
        }
    }
    return 0;
}
