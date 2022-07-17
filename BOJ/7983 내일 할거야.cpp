// 2022-07-13
// 7983 내일 할거야
// https://www.acmicpc.net/problem/7983
/*
    그리디, 정렬 (9,840KB, 304ms)
    시간 복잡도: ?
    풀이)
    - 0일부터 연속으로 쉬는 날이 가장 길어야 하므로, 과제를 끝냄과 동시에 제출할 수 있도록 시작 날짜를 맞춘다.
    이때, 날짜가 서로 겹칠 수 있음에 주의해야 한다.
    - 제출 날짜인 t가 가장 느린 과제부터 처리한다.
    i번째 과제를 마칠 경우, t-d일까지 쉴 수 있으며 변수 r에 저장한다.
    이후, i+1번째 과제를 수행해야 한다. 이때, i+1번째 과제의 t가 r보다 클 수 있다. 즉, t에 맞춰 아슬아슬하게 과제를 제출하고 싶지만 기간이 겹쳐버린다.
    이때는 r을 제출 기한이라 본다.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

bool cmp(const pii &p1, const pii &p2) { return p1.second > p2.second; } // t를 기준으로 내림차순 정렬

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<pii> v(n);
    for (auto &[d, t] : v)
        cin >> d >> t;

    sort(v.begin(), v.end(), cmp);

    int r = v.front().second; // 0일부터 연속으로 쉴 수 있는 날
    for (const auto &[d, t] : v)
    {
        r = min(r, t);
        r -= d;
    }

    cout << r;
}