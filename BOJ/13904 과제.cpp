// 2022-08-29
// 13904 과제
// https://www.acmicpc.net/problem/13904
/*
    sol.1) 그리디 (2,020KB, 0ms)
    시간 복잡도: O(n * logd)
    풀이)
    - 입력된 두 정수 d, w를 v[]에 저장한 후 점수 w를 기준으로 내림차순 정렬.
    - 점수가 큰 과제를 우선적으로 해결.
    - 현재 선택된 과제를 d일에 해결한 후 visited[]에 표시. (visited[i] = true일 경우, i일에는 과제를 처리)
    만약 d일에 처리할 과제가 있을 경우, 과제를 수행하지 않는 날짜가 나올 때까지 d--. (혹은 0일이 되거나)
    해당 과제를 처리할 수 있을 경우, ans에 w 추가.
    etc.) cmp() 잘못짜서 왜맞틀한 문제
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n

bool cmp(const pii &p1, const pii &p2)
{
    return p1.second > p2.second;
}

int main()
{
    FAST_IO;

    int n; // 정수의 수 (1 ≤ n ≤ 1,000)
    cin >> n;
    pii v[MAX]; // 마감일 d(1 ≤ d ≤ 1,000), 점수 w(1 ≤ w ≤ 100)
    for (int i = 0; i < n; i++)
        cin >> v[i].first >> v[i].second;

    sort(v, v + n, cmp);

    int ans = 0;
    bool visited[MAX]{};
    for (int i = 0; i < n; i++)
    {
        auto [d, w] = v[i];

        while (d > 0 && visited[d]) // 과제를 처리할 날짜를 탐색
            d--;

        if (d > 0) // 처리힐 날짜를 발견한 경우
            visited[d] = true, ans += w;
    }

    cout << ans;
}

/*
    sol.2) 그리디 + 유니온 파인드 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 유니온 파인드를 이용하여 과제를 처리할 날짜를 빠르게 확인.
    - uf.parent[i] = k일 경우, i일까지 처리해야 할 과제는 k일에 처리 가능.
    k가 0일 경우, 현재 과제는 처리할 수 없음.
 */

#include <iostream>
#include <algorithm> // sort
#include <numeric>   // iort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n

bool cmp(const pii &p1, const pii &p2)
{
    return p1.second > p2.second;
}

struct Union_Find
{
    int parent[MAX];

    Union_Find() { iota(parent, parent + MAX, 0); }

    int find_parent(int x) { return x == parent[x] ? parent[x] : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; }

} uf;

int main()
{
    FAST_IO;

    int n; // 정수의 수 (1 ≤ n ≤ 1,000)
    cin >> n;
    pii v[MAX]; // 마감일 d(1 ≤ d ≤ 1,000), 점수 w(1 ≤ w ≤ 100)
    for (int i = 0; i < n; i++)
        cin >> v[i].first >> v[i].second;

    sort(v, v + n, cmp);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        auto [d, w] = v[i];

        int x = uf.find_parent(d);
        if (x > 0)
            ans += w, uf.union_parent(x, x - 1);
    }

    cout << ans;
}