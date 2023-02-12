// 2023-01-16
// 24431 유사 라임 게임
// https://www.acmicpc.net/problem/24431
/*
    정렬 (2,164KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 공통 접미사를 확인하여 쌍을 이루도록 만드는 문제.
    - 접미사를 확인해야 하므로, 입력된 문자열을 뒤집은 후 v에 저장.
    - 곹통된 분자열을 구해야 하므로 v를 정렬.
    - v에서 v[0], v[1]과 같이 두 개의 문자열을 꺼내 서로 비교하여 f개의 문자가 서로 같은지 확인.
    만약 같을 경우, ans++ 및 다른 두 문자열을 비교. (v[2], v[3])
    만약 다를 경우, 문자열을 하나 바꾼 후 비교. (v[1], v[2])
    etc.) 접미사가 아닌 단순 공통 부분 문자열인줄
    - 만약 공통 부분 문자열이라면?
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
#define MAX 503 // max n

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, l, f; // 문자열의 개수 n(2 ≤ n ≤ 500), 길이 l, 공통 접미사의 길이 f(1 ≤ f ≤ l ≤ 10)
        cin >> n >> l >> f;

        vector<string> v(n);
        for (auto &s : v)
            cin >> s, reverse(s.begin(), s.end()); // 문자열 뒤집기

        sort(v.begin(), v.end());

        int ans = 0;
        for (int pos = 0; pos < n - 1; pos++)
            if (v[pos].substr(0, f) == v[pos + 1].substr(0, f)) // f개의 문자가 서로 같을 경우
                ans++, pos++;
        cout << ans << endl;
    }
}