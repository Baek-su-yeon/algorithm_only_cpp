#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

// 숫자 배열 크기, 숫자 배열, 암호 배열 크기, 암호 배열
int password(int N, std::vector<int>& numbers, int M, std::vector<int>& code) {
	// 전체 숫자 위치
	int numbers_idx = 0;
	// 암호 위치
	int code_idx = 0;

	// 둘 다 범위 안 일 때
	while (numbers_idx < N && code_idx < M) {
		// 동일한 숫자 찾았으면 다음 암호 숫자로 이동
		if (numbers[numbers_idx] == code[code_idx]) {
			code_idx++;
		}
		// 전체 숫자는 무조건 이동
		numbers_idx++;
	}

	// 찾았으면 1, 아니면 0
	if (code_idx == M) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;

	for (int time = 1; time <= T; time++) {
		int N, M;

		// 입력받는 부분이 이해가 안되서 AI 도움 받음
		// 숫자 입력
		std::cin >> N;

		std::string temp_numbers;
		std::cin >> temp_numbers;

		std::vector<int> numbers(N);
		for (int j = 0; j < N; j++) {
			// 문자 '1'에서 문자 '0'을 빼면 정수 1이 됨 (아스키코드)
			numbers[j] = temp_numbers[j] - '0';
		}

		std::cin >> M;

		// 암호도 공백 없이 들어온다면 string으로 처리
		std::string temp_code;
		std::cin >> temp_code;

		std::vector<int> code(M);
		for (int j = 0; j < M; j++) {
			code[j] = temp_code[j] - '0';
		}

		int result = password(N, numbers, M, code);
		std::cout << "#" << time << " " << result << "\n";
	}

	return 0;
}