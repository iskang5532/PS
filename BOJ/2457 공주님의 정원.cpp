/*
    2457 공주님의 정원
    그리디, 구현 (KB, ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2457
    풀이)
    - 1번 조건) 공주가 가장 좋아하는 계절인 3월 1일부터 11월 30일까지 매일 꽃이 한 가지 이상 피어 있도록 한다.
    - 2번 조건) 정원이 넓지 않으므로 정원에 심는 꽃들의 수를 가능한 한 적게 한다.
    - 연속해서 꽃이 피게 하도록 i번째 꽃까지 골랐으며, 첫 번째 꽃이 지는 날부터 i번째 꽃이 지는 날까지를 '범위'라고 함.
    - 꽃이 피는 날을 기준으로 오름차순 정렬.
    - 범위를 생성해줌. (범위의 마지막 값, 즉 꽃이 지는 날짜 r의 초깃값은 3월 1일이다.)
    1) 3월 1일에 펴있는 꽃 중에서 가장 나중에 지는 꽃을 탐색하며, 꽃이 지는 날짜를 r에 저장하며 ans++.
    만약 탐색을 완료해도 r값이 그대로인 경우, 0을 출력. (이는 범위를 더 늘려줄 꽃이 없으며 1번 조건을 만족시킬 수가 없음)
    2) 1)을 반복하되, 3월 1일을 r로 변경하여 탐색.
    3) 모든 탐색이 끝난 경우, 2번 조건을 만족하는지에 따라 결과를 출력.
    etc.) 구현이 재밌었던 문제
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

struct pii
{
    int m, d; // 꽃의 정보 (m월 d일)

    friend bool operator<=(const pii &p1, const pii &p2) { return p1.m == p2.m ? p1.d <= p2.d : p1.m <= p2.m; }
    friend bool operator==(const pii &p1, const pii &p2) { return p1.m == p2.m && p1.d == p2.d; }
};

struct Flower
{
    pii s, e; // 꽃이 피는 날짜 s, 꽃이 지는 날짜 e
};

pii _max(const pii &p1, const pii &p2) // 날짜가 더 큰 값을 반환
{
    if (p1.m == p2.m)
        return p1.d >= p2.d ? p1 : p2;
    else
        return p1.m > p2.m ? p1 : p2;
}
struct s_greater // 꽃이 피는 날짜를 기준으로 오름차순 정렬
{
    bool operator()(const Flower &p1, const Flower &p2) { return p1.s.m == p2.s.m ? p1.s.d > p2.s.d : p1.s.m > p2.s.m; }
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n;
    cin >> n;
    priority_queue<Flower, vector<Flower>, s_greater> pq;
    for (int i = 0; i < n; i++)
    {
        int sm, sd, em, ed; // sm월 sd일, 꽃이 지는 날짜 em월 ed일
        cin >> sm >> sd >> em >> ed;
        pq.push(Flower{sm, sd, em, ed});
    }

    int ans = 0;
    pii r = {3, 1}; // 범위에서 꽃이 지는 날 r (초깃값은 start인 {3, 1})
    pii end = {11, 30};
    while (!pq.empty() && r <= end) // 범위에서 꽃이 지는 날이 마지막 날 이하일 시에 반복 (= 12월 1일에 꽃이 질 경우 조건을 만족하여 break)
    {
        pii nr = r; // 다음 꽃을 이용하여 범위를 넓힐 시에 마지막 꽃의 지는 날짜를 저장

        while (!pq.empty() && pq.top().s <= r) // i번째 꽃의 피는 날이 r 이하인 경우 (= r은 꽃이 지는 날이므로 r에 꽃이 펴야 1번 조건을 만족시킴)
        {
            nr = _max(nr, pq.top().e); // 날짜가 더 긴 걸로 (2번 조건을 위해; max을 사용하는 이유는 꽃이 지는 날을 기준으로 정렬하지 않았으므로)
            pq.pop();
        }

        if (r == nr) // 범위가 안바뀐 경우 (= 1번 조건을 만족시킬 꽃이 없음)
            break;

        r = nr;
        ans++;
    }

    if (r <= end) // 1번 조건을 만족시키지 못한 경우
        cout << "0";
    else
        cout << ans;
}

// 4%
// 3
// 1 1 10 10
// 2 2 9 9
// 10 10 12 1
// ans: 2
