// 2023-02-14
// 9785 Damage Over Time 
// https://www.acmicpc.net/problem/9785
/*
    정렬 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 데미지가 높은 순으로 m개를 사용.
    - m개의 데미지를 각각 a에 더하며, 시간이 가장 작은 값을 b에 저장.
    이후, a와 b를 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n, m; // 능력의 개수 n(0 < n < 100), 사용할 능력의 개수 m(0 < m < 100, m ≤ n)
    cin >> n >> m;
    vector<pii> v(n);
    for (auto &[a, b] : v)
        cin >> a >> b;

    sort(v.begin(), v.end(), greater<>());

    int a = 0, b = 0x3f3f3f3f;
    for (int i = 0; i < m; i++)
        a += v[i].first, b = min(b, v[i].second);

    cout << a << ' ' << b;
}