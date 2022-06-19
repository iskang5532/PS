// 2022-06-06
// 7490 0 만들기
// https://www.acmicpc.net/problem/7490
/*
    DFS, 파싱 (2,076KB, 8ms)
    시간 복잡도: ?
    풀이)
    - dfs를 이용하여 만들 수 있는 수식 s를 구함.
    - 수식에 존재하는 공백을 지워 수를 붙임. (1+2 3+4 → 1+23+4)
    - 문자열에서 수와 문자를 추출한 후, 문자의 연산에 따라 sum에 저장.
    만약 연산된 값인 sum이 0일 경우, s 출력.
    - 주의할 점은, ASCII 순서에 따른 출력이다. (' ' < '+' < '-')
    etc.) 첫트에 아이디어가 떠오르지 않아 실패한 문제. 며칠 후 갑자기 떠올라 풀림.
 */

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int n;

void dfs(int dep, string s)
{
    if (dep > n)
    {
        string _s = s;
        _s.erase(remove(_s.begin(), _s.end(), ' '), _s.end()); // 공백 제거

        stringstream ss(_s);
        int sum; // 연산된 결과
        ss >> sum;

        int k;
        char c;
        while (!ss.eof()) // 모든 값을 추출할 때까지
        {
            ss >> c >> k;
            c == '+' ? sum += k : sum -= k;
        }

        if (sum == 0)
            cout << s << endl;

        return;
    }

    for (const auto &c : {' ', '+', '-'})
        dfs(dep + 1, s + c + to_string(dep));
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> n;

        dfs(2, "1");
        cout << endl;
    }
}