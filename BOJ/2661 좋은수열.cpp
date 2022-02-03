// 2661 좋은수열
// https://www.acmicpc.net/problem/2661
/*
    백트래킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 완전 탐색으로 풀 시 3^n으로 시간 초과가 발생할 수 있음. (3^80)
    - 1부터 3까지의 문자 c를 n개 저장할 s.
    - dep번째 문자 c를 담은 s가 좋은 수열인지를 판단.
    s의 뒤에서부터 len개의 문자열을 2개 선택한 후, 서로 비교한다. (s = "12131"일 때, {3}과 {1}, {2,1}과 {3,1})
    만약 같을 경우, 나쁜 수열.
    etc.) 문자열 비교 방법에서 헤맴.
    참고)
    - 문자열 비교: https://blog.naver.com/jinhan814/222604405729
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int n; // 1 ≤ n ≤ 80

bool isValid(const string &s) // 좋은 수열인가?
{
    const int sz = s.size();
    for (int len = 1; len <= sz >> 1; len++)
    {
        // s의 뒤에서 반으로 나눠 len개만큼 비교
        string l = s.substr(sz - len * 2, len);
        string r = s.substr(sz - len, len);
        if (l == r) // 나쁜 수열인가?
            return false;
    }
    return true;
}

void dfs(int dep = 0, const string &s = "")
{
    if (dep == n)
    {
        cout << s;
        exit(0);
    }

    for (char c = '1'; c <= '3'; c++)
        if (isValid(s + c)) // 이 문자열은 좋은 수열인가?
            dfs(dep + 1, s + c);
}

int main()
{
    FAST_IO;

    cin >> n;

    dfs();
}