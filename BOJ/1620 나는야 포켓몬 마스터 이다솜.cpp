/*
    1620 나는야 포켓몬 마스터 이다솜
    map (31,316KB, 164ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1620
    풀이)
    - 맵에 포켓몬 번호와 포켓몬의 이름을 저장시킴.
    입력으로 포켓몬 번호 혹은 포켓몬의 이름이 들어옴. 그러므로 두 개의 맵을 선언하여 각각 저장시킴.
    um1: 포켓몬 번호에 맞는 포켓몬의 이름, um2: 포켓몬의 이름에 맞는 포켓몬 번호
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 포캣몬의 개수 n, 문제의 개수 m (1 ≤ n, m ≤ 100k)
    cin >> n >> m;

    unordered_map<string, string> um1, um2; // um1[num] = str, um1[str] = num
    for (int i = 1; i <= n; i++)
    {
        string str; // 2 ≤ len ≤20
        cin >> str;
        um1[to_string(i)] = str, um2[str] = to_string(i);
    }

    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;

        if ('0' <= str.front() && str.front() <= '9')
            cout << um1[str] << endl;
        else
            cout << um2[str] << endl;
    }
}