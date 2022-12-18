// 2022-12-17
// 17212 달나라 토끼를 위한 구매대금 지불 도우미
// https://www.acmicpc.net/problem/17212
/*
    DP (2,288KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 금액 m을 합법으로 만들기 위해서는 임의의 동전 c를 뺀 금액인 m-c가 합법이어야 한다.
    즉, m-c를 모두 구하여 저장한 뒤 m-c가 합법인지를 확인하면 된다.
    - cnt[]에 해당 금액을 만들 때 필요한 최소 동전의 개수를 저장한다.
    1, 2, 5, 7원은 각각 동전이 주어졌으므로 1개가 최소 개수이다.
    또한, 0은 지불할 필요가 없으므로 0을 넣는다.
    - 3원에서부터 n원까지 cnt[m-c]를 구하여 저장한다.
    etc.)
    - 그리디인 줄 알았으나 문제에 적힌 17을 보고 틀림을 알아냄.
    - 다행히 곧바로 DP임을 깨달음
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n
#define INF 0x3f3f3f3f

int main()
{
    FAST_IO;

    int n; // 금액 (0 ≤ n ≤ 100,000)
    cin >> n;

    int cnt[MAX]; // cnt[money] = k일 때, money를 만들 때 필요한 최소 동전의 개수는 k개
    fill(cnt, cnt + MAX, INF);
    cnt[0] = 0;
    cnt[1] = cnt[2] = cnt[5] = cnt[7] = 1;

    for (int money = 3; money <= n; money++)
        for (const int &coin : {1, 2, 5, 7})
            if (money - coin > 0 && cnt[money] > cnt[money - coin] + 1) // 갱신 가능한가
                cnt[money] = cnt[money - coin] + 1;

    cout << cnt[n];
}