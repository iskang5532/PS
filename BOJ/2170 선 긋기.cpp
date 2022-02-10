// 2170 선 긋기
// https://www.acmicpc.net/problem/2170
/*
    스위핑 (14,436KB, 472ms)
    시간 복잡도: O(n)
    풀이)
    - 입력된 선을 정렬해줌. (x값을 기준으로 오름차순 정렬)
    - 값을 하나씩 사용.
    만약 이전 선의 길이에 걸치는(포함) 경우, r값을 갱신함.
    만약 이전 선의 길이에 걸쳐지지 않는 경우, 이전 선의 길이를 ans에 저장한 후 l, r값을 갱신함.
    - 마지막으로 확인한 선의 길이가 ans에 포함되지 않으므로, 추가적으로 ans에 저장시킴.
    etc.) 선의 최대 길이를 구하는 줄 알았지만, 선의 총길이였음.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000'000'001   // x, y의 INF
using pii = pair<int, int>; // {l, r}

struct cmp
{
    bool operator()(const pii &p1, const pii &p2) { return p1.first > p2.first; } // x를 기준으로 오름차순 정렬
};

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 1,000,000
    cin >> n;

    priority_queue<pii, vector<pii>, cmp> pq;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y; // -1,000,000,000 ≤ x < y ≤ 1,000,000,000
        pq.push({x, y});
    }

    int ans = 0;
    int l = -MAX, r = -MAX; // 이전의 가장 긴 선의 x, y
    while (pq.size())
    {
        auto [le, ri] = pq.top();
        pq.pop();

        if (le <= r) // 이전 선에 포함되는 경우 (= r값만 갱신해주면 됨)
            r = max(r, ri);
        else if (r < le) // 현재 선이 이전 선과 관계가 없는 경우 (= 이전 선의 길이를 ans에 추가해준 후, l, r 갱신)
            ans += r - l, l = le, r = ri;
    }

    ans += r - l; // while문에서 추가하지 못한 마지막 값을 추가해줌
    cout << ans;
}