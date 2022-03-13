/*
    [1차] 뉴스 클러스터링 (코딩테스트 연습 > 2018 KAKAO BLIND RECRUITMENT > [1차] 뉴스 클러스터링)
    맵
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/17677
    풀이)
    - 대소문자가 동일한 값으로 처리되며, 그에 따라 소문자를 기준으로 잡았음. (= 대문자는 소문자로 변환)
    - 구한 다중집합을 맵에 저장시킴. (문자열 및 문자열의 개수)
    - 맵을 이용해 교집합과 합집합을 구함.
     - 교집합을 구할 시, 두 맵에 동일한 문자열이 있을 때 더 작은 value를 저장해줌.
     - 합집합을 구할 시, 두 맵에 동일한 문자열이 있을 때 더 큰 value를 저장해줌.
     또한 서로 존재하지 않는 값은 각 value를 저장함.
    - 교집합과 합집합을 구했는데 둘의 값이 0일 때가 있으며, 이는 공집합.
    다만, 교집합은 0이지만 합집합은 0이 아닐 때가 있다. 이 경우는 공집합이 아니므로 주의해야 한다.
    1) 다중집합 구하기.
    2) 합집합 및 교집합 구하기.
    3) 계산.
    etc.) 문자 + 문자를 문자열로 변환하는 간단한 방법이 없을까 하다가 생각해낸 방법을 사용해봤는데, 당장은 편한것 같음.
    참고)
    - 반례: https://programmers.co.kr/questions/15397 (tc.5, tc.13)
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#define MUL 65536

int get_gyo(unordered_map<string, int> &um1, unordered_map<string, int> &um2) // 교집합 구하기
{
    int ret = 0;
    for (const auto &[str, k] : um1)
        if (um2[str]) // 겹치는 값이 존재
            ret += min(um1[str], um2[str]);

    return ret;
}

int get_hab(unordered_map<string, int> &um1, unordered_map<string, int> &um2) // 합집합 구하기
{
    int ret = 0;
    for (const auto &[str, k] : um1)
        if (um2[str]) // 겹치는 값이 존재
            ret += max(um1[str], um2[str]);
        else // 겹치지 않는 값이 존재
            ret += k;
    for (const auto &[str, k] : um2)
        if (!um1[str]) // 겹치지 않는 값이 존재
            ret += k;

    return ret;
}

int solution(string str1, string str2)
{
    auto get_m = [&](const string &str) -> unordered_map<string, int> // 다중집합 구하기
    {
        unordered_map<string, int> m;
        for (int i = 0; i < str.length() - 1; i++)
        {
            char l = str[i], r = str[i + 1];
            if ('A' <= l && l <= 'Z') // 알파벳이 대문자인 경우
                l += 32;
            else if (!('a' <= l && l <= 'z')) // 알파벳이 아닌 경우
                continue;

            if ('A' <= r && r <= 'Z')
                r += 32;
            else if (!('a' <= r && r <= 'z'))
                continue;

            m[string() + l + r]++;
        }

        return m;
    };
    auto um1 = get_m(str1);
    auto um2 = get_m(str2);

    int gyo = get_gyo(um1, um2);
    int hab = get_hab(um1, um2);

    return (gyo == 0 && hab == 0) ? MUL : ((double)gyo / hab) * MUL;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << "16384\t " << solution("FRANCE", "french") << endl;         // 16384
//     cout << "65536\t " << solution("handshake", "shake hands") << endl; // 65536
//     cout << "43690\t " << solution("aa1+aa2", "AAAA12") << endl;        // 43690
//     cout << "65536\t " << solution("E=M*C^2", "e=m*c^2") << endl;       // 65536 (a, b 공집합; 교집합 == 합집합 == 0)
//     cout << "0\t " << solution("++", "aa") << endl;                     // 0 (교집합 == 0, 합집합 != 0)
// }