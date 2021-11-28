/*
    14908 구두 수선공
    그리디 (2,160KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/14908
    풀이)
    - i번째 손님의 시간 대비 비용에 대한 값을 구해준 후, 그것을 정렬.
    etc.) 진정한 아이디어 문제 같았음
    참고)
    - 이론: https://onground-korea.github.io/algorithm/2021/03/20/%EB%B0%B1%EC%A4%80-14908.html
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
typedef pair<int, double> pid;

bool cmp(const pid &p1, const pid &p2) { return p1.second == p2.second ? p1.first < p2.first : p1.second < p2.second; }

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n;
    cin >> n;
    vector<pid> arr;
    for (int i = 0; i < n; i++)
    {
        double t, s; // t일, 비용 s
        cin >> t >> s;

        arr.push_back({i + 1, t / s});
    }
    sort(arr.begin(), arr.end(), cmp);

    for (const auto &[i, d] : arr)
        cout << i << " ";
}