// 2022-07-08
// 17939 Gazzzua
// https://www.acmicpc.net/problem/17939
/*
    그리디 (2,292KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 코인 가격의 개수를 cnt[]에 저장.
    이후, 앞으로의 코인 가격 중에서 현재 코인보다 높은 가격이 존재하면 구매
    만약 현재 코인보다 높은 가격이 존재하지 않을 경우, 보유 중인 코인을 현재 가격에 모두 판매.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N (int)1e5
#define MAX_K 1'003

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int v[MAX_N], cnt[MAX_K]{};
    for (int i = 0; i < n; i++)
        cin >> v[i], cnt[v[i]]++;

    int ans = 0, p = 0; // 보유중인 코인의 개수 p
    for (int i = 0; i < n; i++)
    {
        bool used = false; // 더 높은 가격이 존재하는가? (= 구매해야 하는가?)
        for (int pos = MAX_K - 1; v[i] < pos && !used; pos--)
            if (cnt[pos])
                used = true;

        if (used)
            ans -= v[i], p++;
        else
            ans += p * v[i], p = 0;

        cnt[v[i]]--;
    }

    cout << ans;
}