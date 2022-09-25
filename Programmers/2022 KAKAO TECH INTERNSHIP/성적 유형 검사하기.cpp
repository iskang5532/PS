// 2022-05-07
// 성적 유형 검사하기 (코딩테스트 연습 > 2022 KAKAO TECH INTERNSHIP > 성격 유형 검사하기)
// https://school.programmers.co.kr/learn/courses/30/lessons/118666?language=cpp
/*
    완전 탐색
    시간 복잡도: ?
    풀이)
    - 네 가지 지표의 성격 유형을 ch에 저장.
    - 각 성향의 점수를 저장할 score. (score[c] = k일 때, 성향 c의 점수는 k)
    - choices의 4를 기준으로 4보다 작은 값과 큰 값을 나눠 생각.
    만약 4보다 작을 경우, 현재 확인중인 두 문자 l(= survey[i][0]), r(= survey[i][1]) 중에서 l에 값을 저장.
    만약 4보다 클 경우, r에 값을 저장.
    - 네 가지 지표의 성격 유형을 이용하여 저장된 점수를 구함.
    참고)
    - 해설: https://tech.kakao.com/2022/07/13/2022-coding-test-summer-internship/
 */

#include <bits/stdc++.h>

using namespace std;

const vector<vector<char>> ch = {{'R', 'T'},
                                 {'C', 'F'},
                                 {'J', 'M'},
                                 {'A', 'N'}};

string solution(vector<string> survey, vector<int> choices)
{
    int n = survey.size();

    map<char, int> score; // score[c] = k일 때, 성향 c의 점수는 k
    for (int i = 0; i < n; i++)
    {
        char l = survey[i][0], r = survey[i][1];
        int k = choices[i] - 4; // 음수와 양수로 나눔 (모르겠음인 4를 기준으로)

        if (k < 0) // 비동의
            score[l] += -k;
        else if (k > 0) // 동의
            score[r] += k;
    }

    string ans = "";
    for (int i = 0; i < 4; i++)
    {
        char l = ch[i][0], r = ch[i][1];
        ans += (score[l] >= score[r] ? l : r);
    }

    return ans;
}

// int main()
// {
//     cout << solution({"AN", "CF", "MJ", "RT", "NA"}, {5, 3, 2, 7, 5}) << endl; //	"TCMA"
//     cout << solution({"TR", "RT", "TR"}, {7, 1, 3});                           // 	"RCJA"
// }