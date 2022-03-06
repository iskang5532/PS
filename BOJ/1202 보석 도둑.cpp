// 1202 보석 도둑
// https://www.acmicpc.net/problem/1202
/*
    그리디 (11,512KB, 208ms)
    시간 복잡도: ?
    풀이)
    - 입력된 보석을 저장한 후, 무게를 기준으로 오름차순 정렬.
    - 입력된 가방을 오름차순 정렬.
    - 무게가 낮은 순으로 가방을 선택한 후, 해당 가방에 들어갈 수 있는 보석 중 가격이 가장 높은 보석을 선택.
    1. 현재 가방 c에 들어갈 수 있는 보석을 우선순위 큐 pq2에 모두 저장. pq2는 가격을 기준으로 내림차순 정렬)
    2. pq2에 저장된 보석들은 현재 가방 c와 이후 선택될 가방에 들어갈 수 있는 무게의 보석이며, pq2.top()은 그러한 보석들 중 가격이 가장 높다.
    그러므로, 현재 가방에 들어갈 수 있는 무게를 가지면서 가격이 가장 높은 보석은 pq2.top()이다.
    pq2.top().v를 ans에 더한 후, 보석을 제거해준다.
    3. 선택할 가방이 남아 있을 경우, 1번으로 이동하여 다시 수행한다.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

struct pii
{
    int m, v; // 무게 m, 가격 v  (0 ≤ Mi, Vi ≤ 1,000,000)
};

struct greater_m // 무게를 기준으로 오름차순 정렬
{
    bool operator()(const pii &p1, const pii &p2) { return p1.m > p2.m; }
};
struct less_v // 가격를 기준으로 내림차순 정렬
{
    bool operator()(const pii &p1, const pii &p2) { return p1.v < p2.v; }
};

int main()
{
    FAST_IO;

    int n, k; // 보석의 개수 n, 가방의 개수 k (1 ≤ N, K ≤ 300,000)
    cin >> n >> k;
    priority_queue<pii, vector<pii>, greater_m> pq; // 모든 보석을 저장 (무게 중심 오름차순 정렬)
    for (int i = 0; i < n; i++)
    {
        int m, v;
        cin >> m >> v;
        pq.push({m, v});
    }

    vector<int> bag(k); // 가방의 무게 (1 ≤ Ci ≤ 100,000,000)
    for (auto &c : bag)
        cin >> c;

    sort(bag.begin(), bag.end());

    ll ans = 0;
    priority_queue<pii, vector<pii>, less_v> pq2; // 현재 가방에 담을 수 있는 보석을 저장 (가격 기준 내림차순 정렬)
    for (const auto &c : bag)
    {
        while (pq.size() && c >= pq.top().m) // 현재 가방에 담을 수 있는 모든 보석을 pq2로 이동
            pq2.push(pq.top()), pq.pop();

        if (pq2.size())
            ans += pq2.top().v, pq2.pop(); // 가방에 담을 수 있는 보석 중 가장 가격이 높은 보석을 담음
    }

    cout << ans;
}

// 7%
// 2 2
// 5 5
// 5 5
// 1
// 10
// ans: 5