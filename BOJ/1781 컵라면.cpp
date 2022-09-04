// 2022-09-02
// 1781 컵라면
// https://www.acmicpc.net/problem/1781
/*
    그리디, 유니온 파인드 (4,244KB, 56ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 v에 저장한 후, 받을 수 있는 컵라면을 기준으로 내림차순 정렬.
    - 컵라면을 많이 받을 수 있는 숙제를 우선적으로 해결하여 최대한 많은 컵라면을 받는다.
    만약 해당 숙제의 데드라인 날에 숙제를 해결할 수 있을 시, 숙제를 해결한다.
    만약 해당 숙제의 데드라인 날에 숙제를 해결할 수 없을 시, 데드라인 전날에 해결할 수 있는지 확인한다.
    데드라인 전날에 해결할 수 없다면, 그 전날.. 해결할 수 없다면 그 전날.. 해결이 가능한 날짜가 나오거나 1일이 될 때까지 반복하여 찾는다.
    - 유니온 파인드를 이용하여 숙제를 해결할 수 있는 날짜를 빠르게 확인한다.
    - uf.parent[i] = k일 경우, 데드라인이 i인 숙제는 k일에 처리할 수 있다. (단, k == 0일 경우 해결할 수 없음)
    etc.)
    - 유니온 파인드를 사용하지 않을 경우 TLE.
    - 우선순위 큐로 푸는 문제였으나, 유파 풀이가 먼저 생각남
 */

#include <iostream>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 200'003 // max n

bool cmp(const pii &p1, const pii &p2) // 컵라면을 기준으로 내림차순 정렬
{
    return p1.second > p2.second;
}

struct Union_Find
{
    int parent[MAX];

    Union_Find() { iota(parent, parent + MAX, 0); }
    int find_parent(int x) { return x == parent[x] ? parent[x] : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { parent[a] = b; }
} uf;

int main()
{
    FAST_IO;

    int n; // 숙제의 개수 (1 ≤ n ≤ 200,000)
    cin >> n;
    pii v[MAX]; // {데드라인, 받을 수 있는 컵라면의 수}
    for (int i = 0; i < n; i++)
        cin >> v[i].first >> v[i].second;

    sort(v, v + n, cmp);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        auto [dead, k] = v[i];
        dead = uf.find_parent(dead);

        if (dead >= 1) // 해결이 가능한 경우
            ans += k, uf.union_parent(dead, dead - 1);
    }

    cout << ans;
}