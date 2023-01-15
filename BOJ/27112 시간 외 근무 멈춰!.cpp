// 2023-01-09
// 27112 시간 외 근무 멈춰!
// https://www.acmicpc.net/problem/27112
/*
    그리디, 정렬 (2.808KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 작업을 최대한 많이 끝내기 위해서는 최대한 많은 날에 근무를 해야 한다.
    이를 위해, 마감 기한이 빠른 순으로 작업을 처리한다.
    단, 현재 날짜가 마감 기한을 넘었을 시 해당 작업은 처리할 수 없다.
    - 시간 외 근무 또한 위와 마찬가지로 진행한다.
    만약 시간 외 근무를 수행했음에도 모든 작업을 끝마치치 못했을 경우, -1을 출력.
    - 평시 근무는 월요일부터 금요일까지 주 5회 작업을 진행할 수 있지만, 시간 외 근무는 요일과 관계없이 작업을 진행할 수 있다.
    etc.)
    - 문제를 제대로 읽지 않아서 왜맞틀 엄청 외침. (시간 외 근무는 요일과 관계없음)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define d first
#define t second

int work(vector<pii> &v, bool overtime = false)
{
    int ret = 0;

    int ed = v.back().d;
    for (int day = 1, pos = 0; day <= ed; day++)
    {
        while (pos != v.size() && (v[pos].d < day || v[pos].t == 0)) // 날짜가 지났거나 작업이 끝났을 경우, 다음 작업으로
            pos++;
        if (pos == v.size())
            break;

        if (!overtime && (day % 7 == 6 || day % 7 == 0)) // 주말일 경우, 패스 (단, 시간 외 근무는 제외)
            continue;
        v[pos].t--, ret++;
    }

    return ret;
}

int main()
{
    FAST_IO;

    int n; // 작업의 개수 (1 ≤ n ≤ 100,000)
    cin >> n;
    vector<pii> v(n); // {마감 기한, 걸리는 시간}
    for (auto &[d, t] : v)
        cin >> d >> t;
    sort(v.begin(), v.end()); // 마감 기한을 기준으로 오름차순 정렬

    work(v);                 // 평시 근무
    int ans = work(v, true); // 시간 외 근무

    bool flag = true; // 모든 작업을 끝냈는가
    for (const auto &[d, t] : v)
        if (t) // 시간 외 근무를 수행했음에도 제시간에 맞추지 못한 경우
            flag = false;
    cout << (flag ? ans : -1);
}