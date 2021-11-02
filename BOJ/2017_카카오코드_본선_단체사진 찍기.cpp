/*
    단체사진 찍기 (코딩테스트 연습 > 2017 카카오코드 본선 > 단체사진 찍기)
    brute-force, 조합
    시간 복잡도: O(8! * 8^2 * 100)? (258,048,000인데 맞는 것인가?)
    문제: https://programmers.co.kr/learn/courses/30/lessons/1835?language=cpp
    etc.)
    - 문자열을 정렬한 후에 조합을 사용.
 */

#include <string>
#include <vector>
#include <algorithm> // next_permutation

using namespace std;

#define MAX 8 // 글자의 개수

bool isValid(const string &str, const string &vec, const int l, const int r)
{
    bool ret = false;

    char sign = vec[3];
    int k = vec[4] - '0';

    int dist = abs(l - r) - 1; // 가장 거리가 가까운 경우인 서로 붙어있을 때의 거리는 0
    if (sign == '=' && dist == k)     ret = true;
    else if (sign == '<' && dist < k) ret = true;
    else if (sign == '>' && dist > k) ret = true;

    return ret;
}

int solution(int n, vector<string> data)
{
    int answer = 0;
    string str = "ACFJMNRT";

    do
    {
        bool flag = true;
        for (int i = 0; i < MAX - 1 && flag; i++)
            for (int j = 1; j < MAX && flag; j++)
                for (const auto &vec : data)
                    if ((str[i] == vec[0] && str[j] == vec[2]) || (str[i] == vec[2] && str[j] == vec[0]))
                        if (!isValid(str, vec, i, j)) // 조건을 만족하지 않는 경우
                            flag = false;

        if (flag)
            answer++;

    } while (next_permutation(str.begin(), str.end()));

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(2, {"N~F=0", "R~T>2"}) << endl; // 3648
//     cout << solution(2, {"M~C<2", "C~M>1"}) << endl; // 0
// }