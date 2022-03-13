/*
    숫자 게임 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 숫자 게임)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12987
    풀이) B의 가장 큰 값부터 확인하며, A의 값들 중 B보다 작으며 차이가 가장 적게 나는 숫자를 찾음.
    - A, B를 내림차순으로 정렬.
    - A, B의 가장 큰 값부터 하나 씩 확인.
     - B > A인 경우 다음 숫자를 확인
     - B <= A인 경우 A의 현재 숫자를 이길 수 없으므로 A의 다음 카드를 확인.
 */

#include <vector>
#include <algorithm> // sort

using namespace std;

bool _greater(const int a, const int b) { return a > b; } // 내림차

int solution(vector<int> A, vector<int> B)
{
    sort(A.begin(), A.end(), _greater), sort(B.begin(), B.end(), _greater);

    int ans = 0;
    auto itr_a = A.begin(), itr_b = B.begin();
    while (itr_a != A.end() && itr_b != B.end())
    {
        if (*itr_b > *itr_a)
            ans++, itr_b++, itr_a++;
        else
            itr_a++;
    }
    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << "1. 3\t" <<  solution({5, 1, 3, 7}, {2, 2, 6, 8}) << endl; // 3
//     cout << "2. 0\t" << solution({2, 2, 2, 2}, {1, 1, 1, 1}) << endl; // 0
// }