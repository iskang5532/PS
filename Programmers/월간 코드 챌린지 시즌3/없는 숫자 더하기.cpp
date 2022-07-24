// 2022-07-24
// 코딩테스트 연습 > 월간 코드 챌린지 시즌3 > 없는 숫자 더하기
// https://school.programmers.co.kr/learn/courses/30/lessons/86051
/*
    구현
    풀이)
    - 수가 numbers에 존재하는지 여부를 저장할 used. (used[i] = true일 때, i는 numbers에 존재)
    - numbers의 값을 하나씩 확인하며 used에 체크.
    etc.) numbers의 모든 원소가 다르므로, numbers의 모든 원소를 더한 후 45에서 빼주어 정답을 구할 수도 있음.
 */

#include <iostream>
#include <vector>

using namespace std;
#define MAX 12

int solution(vector<int> numbers)
{
    bool used[MAX]{}; // used[i] = true일 때, i는 numbers에 존재
    for (const auto &i : numbers)
        used[i] = true;

    int ans = 0;
    for (int i = 1; i <= 9; i++)
        if (!used[i])
            ans += i;

    return ans;
}