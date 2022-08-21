// 2022-08-15
// 2374 같은 수로 만들기
// https://www.acmicpc.net/problem/2374
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 현재 값을 이전에 나온 최댓값까지 올리면 됨.
    단, 인접한 값과 동일할 경우, 한 번에 다 같이 올릴 수 있음.
    - 최댓값을 저장할 mx, 현재 값인 cur, 이전 값인 prev.
    - prev를 확인. prev를 cur와 함께 올릴 수 있는지 확인.
    만약 cur가 prev보다 작을 경우, cur가 prev까지만 올리면 됨. (prev가 mx까지 함께 올려주므로)
    - cur가 prev보다 클 경우, prev를 올려야 함.
    그러나 mx보다는 작을 경우, cur는 건들지 않음. (prev에서 이미 mx까지 올렸으므로, cur 또한 함께 올라감)
    - cur가 prev보다 크면서 mx보다 클 경우, mx를 cur까지 올린 후 mx 갱신. (prev에서 mx까지 올렸으므로 mx에서 cur까지만 올려주면 됨)
    etc.) 스택을 이용해서 풀려 했으나 없어도 풀린 문제.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define MAX 1'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> v[i];

    ll ans = 0;
    int mx = v[0]; // 이전까지 나온 최댓값 mx
    for (int i = 1; i < n; i++)
    {
        int cur = v[i], prev = v[i - 1];
        if (prev < cur && mx < cur) // cur가 최댓값인 경우
            ans += cur - mx, mx = cur;
        else if (cur < prev && cur < mx) // 이전 값보다 작으며 최댓값보다 작을 경우
            ans += prev - cur;
    }

    cout << ans;
}