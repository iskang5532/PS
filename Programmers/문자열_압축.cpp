/*
    문자열 압축 (코딩테스트 연습 - 2020 KAKAO BLIND RECRUITMENT - 문자열 압축)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/60057?language=cpp
    etc.) 제일 앞에서부터 '정해진 길이만큼' 잘라야 한다는 조건을 몰라 헤맸던 문제.
    - 주어진 문자열을 모든 길이에 대해 압축률을 조사한다.
    - 문자열을 asdasdxx, 압축 길이(= ext)를 3이라고 가정.
    1) 시작 지점(= start)부터 시작되는 문자열인 asd를 기준 문자열(= curr)로 잡는다.
    2) 다음 위치인 [3]부터인 asd가 curr와 같으므로 압축 횟수(= cnt) +1.
    3) 다음 위치인 [6]부터인 xx가 curr와 다르므로 종료.
    4) 만약 압축에 성공했을 경우 먼저 압축 횟수를 압축 문자열(= ret)에 추가하며 start를 압축 횟수만큼 위치를 옮겨준다. (= 중복 제거)
    또한, 압축의 여부와 상관없이 curr을 ret에 추가.
    5) 이후 start에서 ext만큼 옮긴 후 1)부터 시작.
    6) 탐색을 완료하고 구해진 ret의 길이(= answer)가 이전에 구한 answer보다 작은 경우, 갱신.
    이후 ext값을 변경하며 1)부터 실행.
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1234567890

int compressed(const string &str, const int ext) // 문자열 str, 압축 길이 ext
{
    string ret = ""; // 압축된 문자열을 저장
    for (int start = 0; start < str.length(); start += ext)
    {
        int cnt = 1; // 기준 문자열을 이용한 압축 횟수 (기준 문자열(= curr) 포함이기 때문에 1부터)
        string curr = str.substr(start, ext);

        for (int l = start + ext; l < str.length(); l += ext) // 기준 문자열에서부터 다음 문자열
        {
            string next = str.substr(l, ext); // 기준 문자열의 다음 문자열 (ext만큼 떨어진)
            if (curr == next)
                cnt++;
            else
                break;
        }

        if (cnt >= 2) // 압축에 성공한 경우
        {
            ret += to_string(cnt);    // 압축 횟수 추가
            start += (cnt - 1) * ext; // 압축한 만큼 시작 위치를 옮김 (-1인 이유는 기준 문자열 이동을 제외시키기 위함이며, 이는 for문에서 이동시킴)
        }
        ret += curr;
    }

    return ret.length();
}

int solution(string s)
{
    int answer = INF;

    for (int i = 1; i <= s.length(); i++) // 문자열의 압축 길이
        answer = min(answer, compressed(s, i));

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution("aabbaccc") << endl;                 // 7
//     cout << solution("ababcdcdababcdcd") << endl;         // 9
//     cout << solution("abcabcdede") << endl;               // 8
//     cout << solution("abcabcabcabcdededededede") << endl; // 14
//     cout << solution("xababcdcdababcdcd") << endl;        // 17
//     cout << solution("a") << endl;                        // 1  (tc.5)
// }