// 10814 나이순 정렬
// https://www.acmicpc.net/problem/10814
// 푼 순서: 퀵 - 멀티맵 - 안정 정렬
/*
    sol.1) 맵 (9,948KB, 84ms)
    시간 복잡도: ?
    풀이)
    - 맵에 수와 문자열을 저장시킴. (맵에 저장된 값은 자동으로 안정 정렬.)
    이때, 수가 중복될 수 있으므로 멀티맵을 사용.
    - 입력이 끝난 후, 맵에 존재하는 값을 모두 출력함.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    multimap<int, string> m; // 1 ≤ k ≤ 200, 1 ≤ str.len ≤ 100

    int n; // 1 ≤ N ≤ 100,000
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        string str;
        cin >> k >> str;
        m.insert({k, str});
    }

    for (const auto &[k, str] : m)
        cout << k << ' ' << str << endl;
}

/*
    sol.2) 안정 정렬 (STL) (7,900KB, 40ms)
    시간 복잡도: ?
    풀이)
    - 수가 같을 경우, 입력된 순서대로 출력해야 한다.
    즉, 안정 정렬을 필요로 하는 문제.
    - 벡터에 값을 입력받은 후, 안정 정렬 시킴.
    주의할 점은, 정렬 기준을 정하지 않을 경우 첫 번째 값을 기준으로 정렬한 후, 만약 값이 같은 경우가 생길 시 두 번째 값을 기준으로 정렬이 된다.
    이는 첫 번째 값이 같을 시 입력된 순서대로 출력해야 하는 조건에 어긋나므로, 첫 번째 값만 비교시켜줘야 한다.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 100,000
    cin >> n;
    vector<pair<int, string>> v(n); // 1 ≤ k ≤ 200, 1 ≤ str.len ≤ 100
    for (auto &[k, str] : v)
        cin >> k >> str;

    stable_sort(v.begin(), v.end(), [&](const pair<int, string> &p1, const pair<int, string> &p2)
                { return p1.first < p2.first; });

    for (const auto &[k, str] : v)
        cout << k << ' ' << str << endl;
}

/*
    sol.3) 계수 정렬 (Counting Sort) (9,840KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수의 범위가 작다는 점을 이용하여 계수 정렬 사용.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

struct pis
{
    int num;
    string str;
};

void CountingSort(vector<pis> &v, int n)
{
    int mx = 0;
    for (const auto &[k, str] : v)
        mx = max(mx, k);
    vector<pis> ret(n);
    vector<int> cnt(mx + 1, 0);

    for (int i = 0; i < n; i++)
        cnt[v[i].num]++;

    for (int i = 1; i <= mx; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        auto cur = v[i];

        int pos = --cnt[cur.num];
        ret[pos] = cur;
    }

    v = move(ret);
}

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 100,000
    cin >> n;
    vector<pis> v(n); // 1 ≤ k ≤ 200, 1 ≤ str.len ≤ 100
    for (auto &[k, str] : v)
        cin >> k >> str;

    CountingSort(v, n);

    for (const auto &[k, str] : v)
        cout << k << ' ' << str << endl;
}