// 2022-05-14
// 25192 인사성 밝은 곰곰이
// https://www.acmicpc.net/problem/25192
/*
    셋 (8,240KB, 72ms)
    시간 복잡도: ?
    풀이)
    - 문자열 s를 입력받음.
    만약 s가 "ENTER"일 경우, 셋을 비움.
    만약 s가 셋에 존재하지 않을 경우, 횟수++ 및 셋에 추가.
 */

#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_set<string> us;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "ENTER")
            us.clear();
        else if (us.find(s) == us.end())
            ans++, us.insert(s);
    }
    cout << ans;
}