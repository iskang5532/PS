/*
    소수 만들기 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 소수 만들기)
    구현, 수학
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12977
    풀이)
    - nums[]의 값 중 3개를 뽑는 경우의 수를 모두 구함.
    - 3개의 값을 뽑아 더해진 값이 소수인지를 판별. (만약 소수면 answer++)
    소수는 num값을 2부터 sqrt(num)까지의 i값으로 나눴을 때, 나머지가 없는 경우임. (or num/2)
    etc.) 소수 판별 구현을 까먹어서 헤맸음.
 */

#include <string>
#include <vector>
#include <algorithm> // next_permutation
#include <cmath>     // sqrt

using namespace std;

bool isPrime(int num) // num이 소수인지를 확인
{
    // if (num == 0 || num == 1)
    //     return false;
    for (int i = 2; i <= sqrt(num); i++) // 2부터 sqrt(num)까지 나눴을 때 0이 될 경우 false
        if (num % i == 0)
            return false;
    return true;
}

int solution(vector<int> nums)
{
    int answer = 0;

    string bit; // 조합에 사용
    for (int i = 0; i < nums.size() - 3; i++)
        bit += "0";
    bit += "111"; // 3개의 수
    do
    {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            if (bit[i] - '0') // i번째 비트를 사용하는가?
                sum += nums[i];

        if (isPrime(sum)) // 소수인가?
            answer++;
    } while (next_permutation(bit.begin(), bit.end())); // 조합 수행 (nums에서 3개 뽑기)

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution({1, 2, 3, 4}) << endl;    // 1
//     cout << solution({1, 2, 7, 6, 4}) << endl; // 4
// }