// 2022-11-28
// 14247 나무 자르기
// https://www.acmicpc.net/problem/14247
/*
    그리디, 정렬 (3,460KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 나무가 최대로 컸을 때를 비교하여 가장 큰 나무부터 나중에 잘라주면 된다.
    이때, 나무의 성장 길이만을 이용해야 하며, 초기에 주어지는 값은 제외한다.
    - 자란 나무를 잘라 값을 더해줄 때, 초기에 주어진 값은 나무의 길이에 포함되므로 같이 더해준다.
    - 위와 같이 자르게 될 경우, 마지막에 더해줄 값(= 맨 처음에 자를 나무)은 증가하지 않은 초기 길이가 된다.
    etc.) 문제를 이해하지 못해서 예제를 보고 문제를 유추해서 풂.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
using ll = long long;
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n; // 나무의 개수 (1 ≤ n ≤ 100,000) 
    cin >> n;
    ll v1[MAX]{}, v2[MAX]{};

    for (int i = 0; i < n; i++)
        cin >> v1[i];
    for (int i = 0; i < n; i++)
        cin >> v2[i];

    sort(v2, v2 + MAX, greater<ll>());

    ll ans = 0;
    for (int i = 0; i < n - 1; i++)
        ans += v2[i] * (n - 1 - i); // 성장 길이가 가장 큰 나무부터 더해줌 (= 마지막에 자르는 나무부터 추가)
    for (int i = 0; i < n; i++)
        ans += v1[i];

    cout << ans;
}