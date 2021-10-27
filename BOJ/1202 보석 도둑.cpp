/*
    1202 보석 도둑
    그리디, 우선순위 큐 (11,512KB, 192ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1202
    etc.) 생각보다 금방 풀려서 기부니가 좋았음.
    - 가방을 무게 기준 오름차로 정렬한 후, 가장 작은 가방부터 선택.
    - 보석을 저장한 pq 또한 무게 기준 오름차로 정렬한 후, 가장 가벼운 보석부터 선택.
    1) 선택된 가방에 들어갈 수 있는 모든 보석을 pq2에 담으며 pq에서 빼줌.
    2-1) pq2에 값이 없는 경우, 다음 가방을 선택.
    2-2) pq2에서 가격이 가장 높은 보석을 가방에 담은 후, pq2에서 빼줌.
    3) 이후 다음 가방을 선택한 후 1)로 이동하며, 선택할 가방이 더 이상 없는 경우 가방에 담긴 가격의 합을 출력.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
typedef long long ll;

struct pii
{
    int m, v; // 무게 M과 가격 V(0 ≤ M, V ≤ 1M)
};

struct greater_m // 무게 기준 오름차순
{
    bool operator()(const pii &p1, const pii &p2) { return p1.m > p2.m; }
};
struct less_v // 가격 기준 내림차순
{
    bool operator()(const pii &p1, const pii &p2) { return p1.v < p2.v; }
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, k; // 보석의 정보 N과 가방의 개수 K(1 ≤ N, K ≤ 300K)
    cin >> n >> k;
    priority_queue<pii, vector<pii>, greater_m> pq; // 무게 기준 오름차순
    for (int i = 0; i < n; i++)
    {
        int m, v;
        cin >> m >> v;
        pq.push({m, v});
    }
    vector<int> bag(k); // 가방에 담을 수 있는 최대 무게 C (1 ≤ C ≤ 100M)
    for (auto &c : bag)
        cin >> c;
    sort(bag.begin(), bag.end()); // 가방 무게 오름차순

    ll ans = 0;
    priority_queue<pii, vector<pii>, less_v> pq2; // 가치 기준 내림차순
    for (const auto &curr : bag)
    {
        while (!pq.empty() && pq.top().m <= curr) // 현재 가방에 담을 수 있는 무게인 경우
            pq2.push(pq.top()), pq.pop();

        if (pq2.empty()) // 현재 가방에 담을 수 있는 물건이 없는 경우, 다음 가방으로
            continue;

        auto [m, v] = pq2.top();
        ans += v, pq2.pop(); // 현재 보석의 가격을 저장
    }

    cout << ans;
}

// 이해를 돕기 위한 예제
// M V
// 4 9     bag     ans
// 5 8     10      4 6
// 6 7     5       5

// 7%
// 2 2
// 5 5
// 5 5
// 1
// 10
// ans: 5