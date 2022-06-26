// 2022-05-14
// 2022-06-20 us.rehash(0) 추가
// 25192 인사성 밝은 곰곰이
// https://www.acmicpc.net/problem/25192
/*
    셋 (8,612KB, 76ms)
    시간 복잡도: ?
    풀이)
    - 문자열 s를 입력받음.
    만약 s가 "ENTER"일 경우, 셋을 비움.
    만약 s가 셋에 존재하지 않을 경우, 횟수++ 및 셋에 추가.
    참고)
    - clear()에 대해: https://www.acmicpc.net/board/view/90885
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
            us.clear(), us.rehash(0);
        else if (us.find(s) == us.end())
            us.insert(s), ans++;
    }
    cout << ans;
}