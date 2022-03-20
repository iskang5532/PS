// 신고 결과 받기 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > 신고 결과 받기)
// https://programmers.co.kr/learn/courses/30/lessons/92334
/*
    맵, 구현
    시간 복잡도: ?
    풀이)
    - 중복해서 신고할 수 없으므로, report의 중복된 값을 제거해줌.
    - 편의를 위해 report의 값을 벡터 v에 저장. ({신고한 사람, 신고된 사람})
    - 해당 인원의 신고당한 횟수를 저장할 맵 um1과 신고 결과를 저장할 um2.
    1. v를 탐색하며 신고된 횟수를 um1에 저장.
    2. v를 탐색하며 신고된 사람의 횟수를 um1에서 확인. 만약 k 이상일 경우, 신고 결과를 um2에 저장.
    3. id_list를 이용해 um1을 탐색하며 신고 결과를 ans에 저장.
    참고)
    - 문제해설: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
    sort(report.begin(), report.end());
    report.erase(unique(report.begin(), report.end()), report.end());

    vector<pair<string, string>> v;
    for (const auto &s : report)
    {
        stringstream ss(s);
        string s1, s2;
        ss >> s1 >> s2;

        v.push_back({s1, s2});
    }

    unordered_map<string, int> um1, um2;
    for (const auto &[s1, s2] : v) // 신고된 사람
        um1[s2]++;
    for (const auto &[s1, s2] : v)
        if (um1[s2] >= k)
            um2[s1]++; // 신고한 사람

    vector<int> ans;
    for (const auto &s : id_list)
        ans.push_back(um2[s]);

    return ans;
}

// void print_ans(const vector<int> &arr);
// int main()
// {
//     print_ans(solution({"muzi", "frodo", "apeach", "neo"},
//                        {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"}, 2)); // 2 1 1 0
// }
// void print_ans(const vector<int> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << endl;
// }