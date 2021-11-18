/*
    예산 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 예산)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12982
    풀이)
    - 주어진 값을 더했을 때 한계치를 넘기지 않는 최대 개수를 구하는 문제.
    - 최대 개수를 구하는 문제이므로, 작은 값들을 넣어주며 개수를 최대한 많이 셈.
    그러므로 주어진 배열을 정렬시켜 작은 값부터 탐색.
    etc.) 기본적인 정렬 문제인듯
 */

#include <vector>
#include <algorithm> // sort
using namespace std;

int solution(vector<int> d, int budget)
{
    sort(d.begin(), d.end());

    int total = 0, answer = 0;
    for (const auto &elem : d)
        if (total + elem <= budget) // 값을 더했을 때 예산을 넘기지 않는 경우 (= 추가 가능)
            total += elem, answer++;
        else
            break;

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution({1, 3, 2, 5, 4}, 9) << endl; // 3
//     cout << solution({2, 2, 3, 3}, 10) << endl;   // 4
// }