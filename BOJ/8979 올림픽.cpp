// 2022-04-20
// 8979 올림픽
// https://www.acmicpc.net/problem/8979
/*
    구현 (2,160KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 메달 순으로 정렬한 값을 v에 저장.
    - 등수를 저장할 rank.
    이후 첫 번째 값부터 확인.
    만약 i번째 국가와 i+1번째 국가의 메달 보유가 다를 경우, rank의 값을 바꿈.
    만약 i번째 국가와 i+1번째 국가의 메달 보유가 같을 경우, rank의 값은 변동 없음.
    현재 탐색 중인 국가가 k번일 경우, rank 출력. (이때, i는 0부터 시작했으므로 rank + 1 출력)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    int num, a, b, c;

    friend bool operator<(const P &p1, const P &p2) { return p1.a != p2.a ? p1.a > p2.a : (p1.b != p2.b ? p1.b > p2.b : p1.c > p2.c); }
    friend bool operator!=(const P &p1, const P &p2) { return p1.a != p2.a || p1.b != p2.b || p1.c != p2.c; }
};

int main()
{
    FAST_IO;

    int n, k; // 국가의 수 n(1 ≤ n ≤ 1,000), 등수를 알고 싶은 국가 k(1 ≤ k ≤ n)
    cin >> n >> k;
    vector<P> v(n);
    for (auto &[num, a, b, c] : v)
        cin >> num >> a >> b >> c;

    sort(v.begin(), v.end());

    int rank = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i].num == k)
        {
            cout << rank + 1;
            break;
        }

        if (i != n - 1 && v[i] != v[i + 1])
            rank = i + 1;
    }
}

/*
    sol.2) 이분 탐색 (벡터) (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 메달 순으로 정렬한 값을 v에 저장.
    - k번 국가의 메달을 p에 저장한 후, 이분 탐색을 통해 v에서 p는 몇 번째에 위치하는지 확인.
    이때, 0번부터 시작이므로 출력 시에는 +1을 해줌.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    int a, b, c;

    friend bool operator<(const P &p1, const P &p2) { return p1.a != p2.a ? p1.a > p2.a : (p1.b != p2.b ? p1.b > p2.b : p1.c > p2.c); }
};

int main()
{
    FAST_IO;

    int n, k; // 국가의 수 n(1 ≤ n ≤ 1,000), 등수를 알고 싶은 국가 k(1 ≤ k ≤ n)
    cin >> n >> k;
    vector<P> v(n);
    P p;
    for (auto &[a, b, c] : v)
    {
        int idx;
        cin >> idx >> a >> b >> c;
        if (idx == k)
            p = {a, b, c};
    }

    sort(v.begin(), v.end());
    cout << lower_bound(v.begin(), v.end(), p) - v.begin() + 1;
}

// sol.2) - 배열
P v[MAX], p;
for (int i = 0; i < n; i++)
{
    int idx;
    auto &[a, b, c] = v[i];
    cin >> idx >> a >> b >> c;
    if (idx == k)
        p = {a, b, c};
}

sort(v, v + n);
cout << lower_bound(v, v + n, p) - v + 1;