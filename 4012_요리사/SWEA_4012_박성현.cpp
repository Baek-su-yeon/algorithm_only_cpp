#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using ::std::cin;
using ::std::cout;
using ::std::ios;
using ::std::min;
using ::std::abs;

// 식재료의 총 개수
int total_ingredients;
// 시너지(맛) 점수
int synergy_matrix[20][20];
// 식재료 배정 체크 배열
bool is_ingredient_selected[20];
// 최종 
int minimum_taste_difference;

// 선택된 A와 선택되지 않은 B의 맛 차이를 계산하는 함수
void calculate_taste_difference() {
    int dish_a_taste = 0;
    int dish_b_taste = 0;

    for (int row_index = 0; row_index < total_ingredients; row_index++) {
        for (int col_index = 0; col_index < total_ingredients; col_index++) {
            // 둘 다 A음식에 선택된 식재료인 경우
            if (is_ingredient_selected[row_index] && is_ingredient_selected[col_index]) {
                dish_a_taste += synergy_matrix[row_index][col_index];
            } 
            // 둘 다 B음식에 배정된 식재료인 경우
            else if (!is_ingredient_selected[row_index] && !is_ingredient_selected[col_index]) {
                dish_b_taste += synergy_matrix[row_index][col_index];
            }
        }
    }

    int current_difference = abs(dish_a_taste - dish_b_taste);
    minimum_taste_difference = min(minimum_taste_difference, current_difference);
}

// 백트래킹
void search_combinations(int current_ingredient, int selected_count) {
    // 목표한 절반의 식재료를 모두 골랐을 때
    if (selected_count == total_ingredients / 2) {
        calculate_taste_difference();
        return;
    }

    // 배열 끝까지 탐색했는데 절반을 다 못 채운 경우 종료
    if (current_ingredient >= total_ingredients) {
        return;
    }

    // 현재 식재료를 A음식에 선택하는 경우
    is_ingredient_selected[current_ingredient] = true;
    search_combinations(current_ingredient + 1, selected_count + 1);

    // 현재 식재료를 A음식에 선택하지 않는 경우
    is_ingredient_selected[current_ingredient] = false;
    search_combinations(current_ingredient + 1, selected_count);
}

void solve_testcase() {
    cin >> total_ingredients;

    for (int row_index = 0; row_index < total_ingredients; row_index++) {
        for (int col_index = 0; col_index < total_ingredients; col_index++) {
            cin >> synergy_matrix[row_index][col_index];
        }
    }

    // 최솟값 변수
    minimum_taste_difference = 99999999;

    // 0번 식재료는 무조건 A음식
    is_ingredient_selected[0] = true;
    search_combinations(1, 1);

    cout << minimum_taste_difference << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int total_testcases;
    if (cin >> total_testcases) {
        for (int testcase = 1; testcase <= total_testcases; testcase++) {
            cout << "#" << testcase << " ";
            solve_testcase();
        }
    }
    return 0;
}