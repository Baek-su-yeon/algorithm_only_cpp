#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main ()
{
    int n, m;
    cin >> n >> m;

    vector<int> numbers(n);
    int number;
    int max_num = 0;
    for (int i = 0; i < n; i++) cin >> numbers[i];

    // 브루트포스
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int sum = 0;
                sum = numbers[i] + numbers[j] + numbers[k];
                if (m < sum) continue;
                else if (max_num < sum) max_num = sum;
            }
        }
    }

    cout << max_num << '\n';

    return 0;
}