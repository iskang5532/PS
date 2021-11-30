/*
    9576 책 나눠주기
    그리디 (2,024KB, 4ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/9576
    풀이)
    - 입력받은 값을 정렬시켜줘야 한다. 이때 정렬은 b값을 기준으로 오름차순 정렬을 시켜주며, 값이 같을 경우 a값을 기준으로 오름차순 정렬을 시켜준다.
    - b값 기준 오름차순 정렬같은 경우, [1, 3]까지 모든 책을 나눠줬다고 하더라도 [4, 4]와 같은 이전보다 큰 b값이 나올 시 무조건 새 책을 줄 수 있다.
    - a값 기준 오름차순 정렬같은 경우
    이는 먼저 수행한 b값 기준 오름차순 정렬과 연관이 있다. b값이 일정한 두 입력이 들어왔다고 가정했을 경우, a값이 작은 순서대로 탐색할 것이다.
    이는 결국 b값에서 멀리 떨어져 있는 값부터 선택한다는 것이며, 이후에 들어올 현재 값보다 큰 b값에 대해 선택의 폭을 넓혀주는 것이다.
    예시로, 입력으로 {1, 3}, {1, 4}, {3, 4}, {3, 4}의 값이 들어왔을 시 [1]부터 채워줘야 뒤에 올 {3, 4}의 선택을 편하게 할 수 있다.
    1) 입력된 값을 정렬.
    2) i번째 책을 줬는지를 판단하는 배열(= visited) 선언.
    3) a, b값을 하나씩 가져옴.
    - 만약 [a]를 나눠준 적이 없을 경우, 책을 나눠줌. (= ans++, [x] = true)
    - 만약 [a]를 나눠준 적이 있을 경우, 나눠준 적이 없는 책이 나올 때까지 +1번째를 탐색. (단, 원하는 범위인 [a, b]를 지켜야 함.)
    etc.) 정렬 방식을 생각해내는게 어려웠던 문제.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define a first
#define b second
typedef pair<int, int> pii;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m; // 1 ≤ n, m ≤ 1k
        cin >> n >> m;
        vector<pii> arr(m);
        for (auto &[a, b] : arr)
            cin >> a >> b;
        sort(arr.begin(), arr.end(), [&](const pii &p1, const pii &p2)
             { return p1.b != p2.b ? p1.b < p2.b : p1.a < p2.a; });

        vector<bool> visited(n + 1, false);
        int ans = 0;
        for (const auto &[a, b] : arr)
        {
            int x = a;
            while (visited[x] && x <= b)
                x++;

            if (x <= b)
                visited[x] = true, ans++;
        }
        cout << ans << endl;
    }
}

// sol.2) 유니온 파인드..? (2,024KB, 0ms)
#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1'000 + 1
#define a first
#define b second
typedef pair<int, int> pii;

int parent[MAX];
int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m; // 1 ≤ n, m ≤ 1k
        cin >> n >> m;
        vector<pii> arr(m);
        for (auto &[a, b] : arr)
            cin >> a >> b;
        sort(arr.begin(), arr.end(), [&](const pii &p1, const pii &p2)
             { return p1.b != p2.b ? p1.b < p2.b : p1.a < p2.a; });

        for (int i = 1; i < n + 1; i++) // fill
            parent[i] = i;

        int ans = 0;
        for (const auto &[a, b] : arr)
        {
            int x = find(a);

            if (a <= x && x <= b)
                parent[x] = x + 1, ans++;
        }
        cout << ans << endl;
    }
}

// 1
// 7 6
// 1 7
// 1 7
// 1 7
// 1 7
// 2 2
// 6 6
// ans: 6

// 1
// 4 4
// 1 4
// 1 3
// 1 3
// 1 3
// ans: 4

// 1
// 4 4
// 1 2
// 2 3
// 3 4
// 1 3
// ans: 4

// 1
// 2 2
// 1 2
// 2 2
// ans: 2

// 1
// 3 3
// 1 3
// 2 2
// 2 2
// ans: 2

// 1
// 6 6
// 1 5
// 1 5
// 1 5
// 1 5
// 2 6
// 2 6
// ans: 6