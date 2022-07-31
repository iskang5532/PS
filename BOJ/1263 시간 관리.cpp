// 2022-7-31
// 1263 시간 관리
// https://www.acmicpc.net/problem/1263
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 일을 끝마쳐야 하는 기한 s를 기준으로 내림차순 정렬.
    - 기한으로부터 t일 이전의 날에 일을 시작하게 된다면, 가장 늦게 일을 시작할 수 있음.
    이를 이용하여, 기한이 늦은 일부터 처리하여 일을 시작하는 시간 st를 정함.
    주의할 점은, 중간에 정해진 st가 다음에 오는 s보다 빨라 일을 빨리 시작해야 할 수 있음.
    즉, st - t에 시작해야 다음에 오는 일과 이전에 정한 일 둘 다 해결할 수 있음.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n

bool cmp(const pii &p1, const pii &p2)
{
    return p1.second > p2.second;
}

int main()
{
    FAST_IO;

    int n; // 일의 개수 (1 ≤ N ≤ 1,000)
    cin >> n;
    int st = 0;       // 일을 시작하는 시간
    vector<pii> v(n); // 걸리는 시간 t(1 ≤ Ti ≤ 1,000), 기한 s(1 ≤ Si ≤ 1,000,000)
    for (auto &[t, s] : v)
        cin >> t >> s, st = max(st, s);

    sort(v.begin(), v.end(), cmp);

    for (const auto &[t, s] : v)
        st = min(s, st) - t;

    cout << (st < 0 ? -1 : st);
}