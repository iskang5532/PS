// 2023-04-02
// 27922 현대모비스 입사 프로젝트
// https://www.acmicpc.net/problem/27922
/*
    그리디, 정렬 (5,540KB, 64ms)
    시간 복잡도: ?
    풀이)
    - 두 개의 역량을 골라 최댓값을 만들어야 하므로, 입력된 역량을 더해 만든 값을 기준으로 정렬하여 값을 구함.
    - 입력된 세 개의 역량 중 두 개의 역량을 더하여 만든 세 개의 값을 v에 넣음. (a+b, a+c, b+c)
    - 각 역량을 기준으로 내림차순 정렬.
    이후, 상위 k개의 값을 더하여 ans에 최댓값을 저장.
    etc.) 어려웠음. 첫 풀이의 반례를 모르겠음. 풀이 자체가 잘못된 것인가?
    - 풀이 설명이 어려움.
    참고)
    - 해설: https://upload.acmicpc.net/3f195577-cf7d-4abc-ac2b-f56fda68da67/
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    int a, b, c;
};

bool cmp_a(const P &p1, const P &p2) { return p1.a > p2.a; }
bool cmp_b(const P &p1, const P &p2) { return p1.b > p2.b; }
bool cmp_c(const P &p1, const P &p2) { return p1.c > p2.c; }

int get_ans(const vector<P> &v, int k)
{
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < k; i++)
        a += v[i].a, b += v[i].b, c += v[i].c;

    return max({a, b, c});
}

int main()
{
    FAST_IO;

    int n, k; // 강의의 개수 n, 수강 개수 k (1 ≤ k ≤ n ≤ 100,000)
    cin >> n >> k;
    vector<P> v(n);
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back({a + b, a + c, b + c});
    }

    int ans = 0;

    sort(v.begin(), v.end(), cmp_a);
    ans = max(ans, get_ans(v, k));

    sort(v.begin(), v.end(), cmp_b);
    ans = max(ans, get_ans(v, k));

    sort(v.begin(), v.end(), cmp_c);
    ans = max(ans, get_ans(v, k));

    cout << ans;
}

// 첫 풀이. WA
#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    int a, b, c;
};

bool cmp_a(const P &p1, const P &p2) { return p1.a > p2.a; }
bool cmp_b(const P &p1, const P &p2) { return p1.b > p2.b; }
bool cmp_c(const P &p1, const P &p2) { return p1.c > p2.c; }

int get_ans(const vector<P> &v, int k)
{
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < k; i++)
        a += v[i].a, b += v[i].b, c += v[i].c;

    return a + b + c - min({a, b, c});
}

int main()
{
    FAST_IO;

    int n, k; // 강의의 개수 n, 수강 개수 k (1 ≤ k ≤ n ≤ 100,000)
    cin >> n >> k;
    vector<P> v(n);
    for (auto &[a, b, c] : v)
        cin >> a >> b >> c;

    int ans = 0;

    sort(v.begin(), v.end(), cmp_a);
    ans = max(ans, get_ans(v, k));

    sort(v.begin(), v.end(), cmp_b);
    ans = max(ans, get_ans(v, k));

    sort(v.begin(), v.end(), cmp_c);
    ans = max(ans, get_ans(v, k));

    cout << ans;
}