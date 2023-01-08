// 2023-01-07
// 개인정보 수집 유효기간 (코딩테스트 연습 > 2023 KAKAO BLIND RECRUITMENT > 개인정보 수집 유효기간)
// https://school.programmers.co.kr/learn/courses/30/lessons/150370
/*
    문자열
    시간 복잡도: ?
    풀이)
    - 입력된 날짜의 연도와 월을 일로 바꾸는 함수 get_time()을 구현하여 사용.
    - terms에 저장된 약관의 종류에 따른 유효 기간을 term에 저장.
    - privacies의 값을 하나씩 꺼내어 일로 바꾼 후, 약관 종류에 맞는 유효 기간을 찾아 사용.
    만약 유효 기간을 더한 값이 today보다 작거나 같을 경우, 파기해야 함.
 */

#include <bits/stdc++.h>

using namespace std;

int term['Z' + 1]; // 약관 종류에 따른 유효 기간 (term['A'] = k일 경우, 'A' 약관의 유효 기간은 k)

int get_time(const string &s) // 날짜를 일로 바꿈
{
    stringstream ss(s);
    int y, m, d;
    char idx;
    ss >> y >> idx >> m >> idx >> d;

    return y * 12 * 28 + m * 28 + d;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies)
{
    vector<int> ans;

    int _today = get_time(today);
    for (const string &s : terms)
        term[s.front()] = stoi(string(s.begin() + 2, s.end())) * 28;

    for (int i = 0; i < privacies.size(); i++)
    {
        int t = get_time(privacies[i]); // 날짜
        char c = privacies[i].back();   // 약관 종류

        if (t + term[c] <= _today) // 기간을 넘겼는가?
            ans.push_back(i + 1);
    }

    return ans;
}

int main()
{
    for (const int &i : solution("2022.05.19",
                                 {"A 6", "B 12", "C 3"},
                                 {"2021.05.02 A", "2021.07.01 B", "2022.02.19 C", "2022.02.20 C"}))
        cout << i << '\n'; // 1 3
}