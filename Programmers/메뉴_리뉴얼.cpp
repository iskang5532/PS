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
    조합 구현에 대해.
    - 비트를 이용해 조합을 구현.
    - 길이가 5인 문자열 str이 있으며 2개를 뽑는 경우, 00011의 값을 만든 후 next_permutation을 실행.
    첫 번째 값인 00011의 경우에는 str[3]과 str[4]을 이용한 문자열이 만들어지며, 이를 저장함.
    etc.)
    - 조합 구현 문제는 풀 때마다 까먹어서 애먹는듯
 */

#include <string>
#include <vector>
#include <algorithm> // sort
#include <unordered_map>

using namespace std;

#define MAX 20 + 1

vector<string> solution(vector<string> orders, vector<int> course)
{
    unordered_map<string, int> m[MAX]; // m[3] = {{ABC, 3}, {DEF, 5}}일 때, 문자열의 길이가 3인 배열에서 문자열 ABC는 3번, DEF는 5번 만들어짐.
    for (auto order : orders)
    {
        sort(order.begin(), order.end());
        int len = order.length();

        for (int sel = 2; sel <= len; sel++) // 선택할 문자의 개수
        {
            string bit;
            for (int i = 0; i < len - sel; i++)
                bit += "0";
            for (int i = 0; i < sel; i++) // 선택할 개수만큼 1 추가 (next_permutation을 위해 낮은 자릿수부터 값을 추가)
                bit += "1";

            do // combinate
            {
                string str; // 조합으로 만들 문자열 저장
                for (int i = 0; i < len; i++)
                    if (bit[i] == '1')
                        str += order[i];
                sort(str.begin(), str.end());
                m[str.length()][str]++; // 만들어진 문자열의 횟수 +1
            } while (next_permutation(bit.begin(), bit.end()));
        }
    }

    vector<string> ans;
    for (const int &i : course)
    {
        // if (m[i].empty())
        //     continue;

        int mx = 0; // 가장 많은 횟수 저장
        for (const auto &[str, k] : m[i])
            mx = max(mx, k);

        if (mx != 1) // 둘 이상의 손님이 주문해야 하므로 1은 제외
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