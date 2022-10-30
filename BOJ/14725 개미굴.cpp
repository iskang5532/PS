// 2022-10-28
// 14725 개미굴
// https://www.acmicpc.net/problem/14725
/*
    (KB, ms)
    시간 복잡도: ?
    풀이)
    etc.)
    참고)
 */

// https://blog.naver.com/jinhan814/222146729124
// https://ansohxxn.github.io/boj/14725/

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

struct Trie
{
    vector<Trie> arr;
    map<string, int> m;

    void add(const vector<string> &v, int dep = 0)
    {
        if (v.size() == dep)
            return;

        const string &str = v[dep];
        if (m.find(str) == m.end())
        {
            Trie trie;
            m[str] = arr.size(), arr.push_back(trie);

            add()
        }
        else
            add(v, dep + 1);
    }
} T;

int main()
{
    FAST_IO;

    // int n; // 모든 정보 개수 (1 ≤ N ≤ 1000)
    // cin >> n;
    // for (int i = 0; i < n; i++)
    // {
    //     int k;
    //     cin >> k; // 먹이 정보 개수 (1 ≤ K ≤ 15)
    //     for (int j = 0; j < k; j++)
    //     {
    //         string s; // 먹이 (1 ≤ s.length() ≤ 15)
    //         cin >> s;
    //     }
    // }
}