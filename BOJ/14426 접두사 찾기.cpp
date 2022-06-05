// 2022-05-30
// 14426 스택 수열
// https://www.acmicpc.net/problem/14426
/*
    정렬되지 않은 셋 (12,852KB, 680ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 저장할 셋 S.
    - 문자열 s를 n개 입력받음.
     - 문자열 s를 1개부터 s.length()개의 문자열로 쪼개어 셋에 저장.
    - 문자열 s를 m개 입력받음.
     - 입력받은 문자열 s가 셋에 존재하는지 확인.
     만약 존재할 경우 ans++.
    - 셋을 사용할 경우 TLE. (각 find()의 시간 복잡도는 set는 O(logN), unordered_set는 O(1))
    etc.) 트라이 전용 문제는 아닌듯 싶다.
 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n, m;
    cin >> n >> m;

    unordered_set<string> S;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        string _s;
        for (const auto &c : s)
            _s.push_back(c), S.insert(_s);
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        if (S.find(s) != S.end())
            ans++;
    }
    cout << ans;
}