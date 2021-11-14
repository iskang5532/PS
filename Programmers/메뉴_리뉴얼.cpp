/*
    메뉴 리뉴얼 (코딩테스트 연습 > 2021 KAKAO BLIND RECRUITMENT > 메뉴 리뉴얼)
    조합
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/72411?language=cpp
    풀이)
    - 하나의 주문된 메뉴로 조합할 수 있는 메뉴를 모두 구함. (= 조합)
    - 조합된 메뉴를 저장하며, 길이에 맞게 맵에 메뉴 및 횟수를 저장. (해당 메뉴가 몇 번 만들어졌는지)
    - 코스의 개수를 하나씩 입력받으며, 맵에서 길이를 이용하여 탐색.
     - 길이가 2일 경우 map[2]에서 탐색.
     - map[2]에서 value의 가장 큰 값(= mx)을 찾은 후, mx와 같은 갑의 문자열을 모두 ans에 저장.
    etc.)
    - 조합 구현은 할 때마다 까먹어서 애먹는듯
 */

#include <string>
#include <vector>
#include <algorithm> // sort
#include <unordered_map>

using namespace std;

#define MAX 20 + 1

vector<string> solution(vector<string> orders, vector<int> course)
{
    unordered_map<string, int> m[MAX];
    for (auto order : orders)
    {
        sort(order.begin(), order.end());
        int len = order.length();

        for (int sel = 2; sel <= len; sel++)
        {
            string comb;
            for (int i = 0; i < len - sel; i++)
                comb += "0";
            for (int i = 0; i < sel; i++)
                comb += "1";

            do // combinate
            {
                string str;
                for (int i = 0; i < len; i++)
                    if (comb[i] == '1')
                        str += order[i];
                sort(str.begin(), str.end());
                m[str.length()][str]++;
            } while (next_permutation(comb.begin(), comb.end()));
        }
    }

    vector<string> ans;
    for (const int &i : course)
    {
        // if (m[i].empty())
        //     continue;

        int mx = 0;
        for (const auto &[str, k] : m[i])
            mx = max(mx, k);

        if (mx != 1)
            for (const auto &[str, k] : m[i])
                if (k == mx)
                    ans.push_back(str);
    }

    sort(ans.begin(), ans.end());
    return ans;
}

// #include <iostream>
// #define endl "\n"
// void print_ans(const vector<string> &ans);
// int main()
// {
//     vector<string> ans;
//     print_ans(solution({{"ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"}}, {2, 3, 4}));   //{"AC", "ACDE", "BCFG", "CDE"}
//     print_ans(solution({{"ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"}}, {2, 3, 5})); //{"ACD", "AD", "ADE", "CD", "XYZ"}
//     print_ans(solution({{"XYZ", "XWY", "WXA"}}, {2, 3, 4}));                             //{"WX", "XY"}
// }
// void print_ans(const vector<string> &ans)
// {
//     for (const auto &str : ans)
//         cout << str << " ";
//     cout << endl;
// }