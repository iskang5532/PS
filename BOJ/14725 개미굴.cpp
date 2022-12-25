// 2022-12-21
// 14725 개미굴
// https://www.acmicpc.net/problem/14725
/*
    트라이 (2,296KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 트라이 구조를 이루는 root에 입력된 문자열을 추가.
    - 같은 깊이여도 오름차순으로 출력되어야 함.
    이는 맵의 특성으로 인해 해결 가능.
    etc.) [7432 디스크 트리]와 같음
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

struct Node
{
    map<string, Node *> m;

    void add(const vector<string> &v, int pos = 0)
    {
        string s = v[pos];

        auto itr = m.find(s);
        if (itr == m.end())
            m[s] = new Node();

        if (pos + 1 == v.size())
            return;
        m[s]->add(v, pos + 1);
    }

    void print(int dep = 0)
    {
        for (const auto &[s, idx] : m)
        {
            for (int i = 0; i < dep; i++)
                cout << "--";
            cout << s << endl;

            m[s]->print(dep + 1);
        }
    }
} root;

int main()
{
    FAST_IO;

    int n; // (1 ≤ n ≤ 1,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k; // (1 ≤ k ≤ 15)
        cin >> k;
        vector<string> v(k);
        for (auto &s : v)
            cin >> s;

        root.add(v);
    }

    root.print();
}