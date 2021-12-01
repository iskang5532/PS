/*
    17619 개구리 점프
    유니온 파인드 (3,976KB, 72ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/17619
    풀이)
    - 통나무가 겹쳐 있는 구간은 서로 이동이 가능함. 즉, x1과 x2가 중요하며 y의 값은 중요하지 않음. (but, 이동 횟수를 구해야 한다면?)
    - 입력된 통나무들이 하나로 연결이 가능하여 일직선의 수평으로 만들 시, 가장 왼쪽에 존재하는 통나무가 다른 통나무들의 부모 역할을 수행.
    - 통나무가 서로 연결이 가능하다면, 각 통나무의 부모는 서로 같을 것임.
    1) 입력된 통나무를 시작점 기준으로 정렬. (가장 왼쪽에 존재하는 통나무를 부모로 만드므로)
    2) 통나무들을 하나씩 탐색.
    - 탐색중인 통나무들 중 가장 큰 값의 끝점(= mx)을 기억하며, l <= mx 일 경우, 정점의 부모를 바꿔줌. (= 이전 통나무들과 연결 가능; 통나무의 시작점이 걸쳐있음.)
    3) 서로 다른 두 통나무의 번호를 입력받으며, 두 통나무의 부모가 같은지 확인. (같을 경우, 서로 연결이 가능함.)
    etc.) 정렬이 관건인 문제라고 생각. 정렬 문제는 그리디 느낌이라 항상 헷갈림..
    참고)
    - 반례: https://www.acmicpc.net/board/view/45243
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100000 + 5

struct P
{
    int num, l, r; // 통나무의 번호와 시작점 및 끝점
};

int parent[MAX]; // 각 통나무의 최상위 통나무를 저장 (parent[4] == 2일 경우, 4번 통나무의 최상위 통나무는 2번)

int find_parent(int x) { return parent[x] == x ? x : parent[x] = find_parent(parent[x]); }
void union_parent(int curr, int next)
{
    int a = find_parent(curr), b = find_parent(next);
    parent[b] = a;
}

bool cmp(const P &p1, const P &p2) { return p1.l != p2.l ? p1.l < p2.l : p1.r > p2.r; } // 시작점을 기준으로 오름차순 정렬

int main()
{
    FAST_IO;

    int n, q; // 통나무 개수 n, 질문의 개수 q (1 ≤ n, q ≤ 100k)
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    vector<P> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i].num = i + 1;
        int idx;
        cin >> arr[i].l >> arr[i].r >> idx;
    }
    sort(arr.begin(), arr.end(), cmp);

    int mx = arr.front().r;
    for (int i = 0; i < n - 1; i++)
    {
        P curr = arr[i], next = arr[i + 1];

        int a = find_parent(curr.num), b = find_parent(next.num);
        if (next.l <= mx)
            union_parent(a, b);
        mx = max(mx, next.r);
    }

    while (q--)
    {
        int st, ed;
        cin >> st >> ed;

        find_parent(st) == find_parent(ed) ? cout << "1" << endl : cout << "0" << endl;
    }
}

// 3 1
// 1 8 1
// 2 5 2
// 6 9 3
// 1 3
// ans: 1

// 2 1
// 4 6 1
// 2 4 2
// 1 2
// ans: 1