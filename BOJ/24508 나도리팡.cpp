// 2022-07-09
// 24508 나도리팡
// https://www.acmicpc.net/problem/24508
/*
    그리디, 투 포인터 (2,292KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 나도리의 수를 저장할 v.
    - v의 값을 이용하여 오름차순 정렬.
    - 작은 값의 위치를 가리킬 l, 큰 값의 위치를 가리킬 r.
    작은 값인 v[l]을 큰 값 v[r]로 옮긴 후 터트림. (개수는 v[l] 혹은 v[r]의 k개까지 남은 개수)
    v[l] == 0 혹은 v[r] == k가 될 경우, 위치를 변경.
    - 만약 l == r이 됐을 경우, 남아 있는 나도리가 존재. 즉, 다 터트리지 못한 경우.
    etc.) 인접한 바구니로 옮겨야 하는줄..
    참고)
    - 이론: https://blog.naver.com/jinhan814/222711580070
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n, k, t; // 바구니의 개수 n, 필요 마릿수 k (2 ≤ N, K ≤ 10^5), 시간 (0 ≤ T ≤ 10^9)
    cin >> n >> k >> t;

    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);

    for (int l = 0, r = n - 1; t >= 0 && l <= r;)
    {
        if (v[l] == 0)
        {
            l++;
            continue;
        }
        if (l == r)
        {
            t = -1;
            break;
        }

        int p = min(v[l], k - v[r]); // 전부 or 부족한 만큼
        v[l] -= p, v[r] += p, t -= p;
        if (v[l] == 0)
            l++;
        if (v[r] == k)
            r--;
    }

    cout << (t >= 0 ? "YES" : "NO");
}