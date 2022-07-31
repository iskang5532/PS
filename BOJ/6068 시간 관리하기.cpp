// 2022-07-25
// 6068 시간 관리하기
// https://www.acmicpc.net/problem/6068
/*
    그리디, 정렬 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 가장 늦게 시작하는 시간을 찾아 출력하면 되는 문제.
    즉, 끝내야 하는 시간 ed에 맞춰 일을 종료하면 됨.
    - ed를 기준으로 내림차순 정렬.
    이후, ed에서부터 필요 시간 t만큼 빼준 값이 i번째 일의 시작 시간이 됨.
    일을 시작할 최소 시간 ans에 구한 값을 저장.
    - 주의할 점은, 일하는 시간이 겹치면 안 됨.
    즉, ed에서 t를 빼어 얻은 일을 시작하는 시간이 이전에 구한 시간과 겹칠 수가 있음.
    이를 위해, ans와 ed 중 더 작은 값에서부터 t를 빼줘야 함. (일하지 않는 시간대 혹은 ed)
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

    int n;
    cin >> n;
    vector<pii> v(n); // [필요 시간 t, 끝내야 하는 시간 ed]
    for (auto &[t, ed] : v)
        cin >> t >> ed;

    sort(v.begin(), v.end(), [&](pii &p1, pii &p2)
         { return p1.second > p2.second; }); // ed를 기준으로 내림차순 정렬

    int ans = v[0].second;
    for (const auto &[t, ed] : v)
        ans = min(ans, ed) - t;

    cout << (ans >= 0 ? ans : -1);
}