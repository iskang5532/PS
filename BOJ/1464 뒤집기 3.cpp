// 2022-05-31
// 1464 뒤집기 3
// https://www.acmicpc.net/problem/1464
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 정답을 저장할 문자열 ans.
    - ans의 첫 번째 문자인 ans.front()는 입력되는 문자 중에서 가장 빠른 문자여야 한다.
    그러므로, 입력되는 문자 c와 비교하여 더 빠른 문자를 ans.front에 오도록 한다.
    - 입력되는 문자와 ans.front() 비교.
    만약 ans.front() < c일 경우, ans의 가장 뒤에 넣는다.
    만약 ans.front() >= c일 경우, ans의 가장 앞에 넣는다.
    etc.) 웰노운..?
    참고)
    - 코드 참고: https://kangminjun.tistory.com/entry/BOJ-1464-%EB%B2%88-%EB%92%A4%EC%A7%91%EA%B8%B0-3
 */
#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string ans;

    char c;
    while (cin >> c)
        if (ans.empty())
            ans += c;
        else if (ans.front() < c)
            ans += c;
        else
            ans = c + ans;

    cout << ans;
}