/*
    스킬트리 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 스킬트리)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/49993
    풀이)
    - 맵을 이용해 해당 스킬이 몇 번째 스킬 순서인지를 저장.
    - 스킬 순서대로 스킬을 찍는다고 가정 시에 값은 1, 2, 3... 순으로 증가. 이를 이용 및 확인해주기 위한 변수 cnt. (레벨 개념)
    - 입력된 스킬 트리에서 스킬 하나 씩 확인.
     - 현재 스킬이 스킬 트리와 관련이 없는 경우, 다음 스킬을 확인.
     - 현재 스킬이 스킬 트리에 관련이 있는 경우
       - 스킬 순서가 제대로된 경우, 다음 스킬을 이용할 수 있도록 cnt++
       - 스킬 순서가 엉망이 된 경우, 탐색을 종료하며 ans++ (이는 현재 cnt보다 높은 스킬인 경우임)
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(string skill, vector<string> skill_trees)
{
    unordered_map<char, int> m;
    int cnt = 1;
    for (const char &c : skill)
        m[c] = cnt, cnt++;

    int ans = 0;
    for (const auto &str : skill_trees)
    {
        bool valid = true; // 현재 스킬 트리는 유효한가? (default: true)
        int cnt = 1;
        for (const char &c : str)
            if (m[c] > cnt)
            {
                valid = false;
                break;
            }
            else if (m[c] == cnt)
                cnt++;

        if (valid)
            ans++;
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << "1. 2\t" << solution("CBD", {"BACDE", "CBADF", "AECB", "BDA"}) << endl;
// }