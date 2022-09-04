// 2022-08-31
// 8980 택배
// https://www.acmicpc.net/problem/8980
/*
    그리디 (2,344KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력된 박스의 정보를 path에 저장.
    이후, 받는 번호 b를 기준으로 오름차순 정렬.
    택배를 빠르게 배송 후 다른 택배를 싣게 된다면 많은 배송을 할 수 있기 때문.
    - 현재 트럭에 실어져 있는 박스의 개수 sum, 현재까지 배송한 박스의 개수 ans.
    - 목적지까지 배송될 박스의 개수를 저장할 cnt
    - 현재 마을에서 보낼 박스의 목적지 next와 개수 c를 확인.
    만약 모든 박스를 실어도 mx를 초과하지 않는 경우, c개를 실은 후 cnt[next]에 c를 더함.
    만약 모든 박스를 실을 시 mx를 초과하는 경우, next보다 멀리 있는 박스를 뺀 후 c를 추가한다.
     - 가장 멀리 있는 마을인 n부터 next+1까지 도착할 박스의 개수 cnt가 있는지를 확인.
     만약 존재할 경우, c만큼 뺀 후 cnt[next]에 추가한다.
    etc.) 고민을 오래해서 그런지 WA없이 바로 AC
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 2'003 // max n

vector<pii> path[MAX];
int cnt[MAX]; // cnt[i] = k일 때, i번 마을에 도착할 박스의 개수는 k

int main()
{
    FAST_IO;

    int n, mx; // 마을의 수 n(2 ≤ n ≤ 2,000), 용량 mx(1 ≤ mx ≤ 10,000)
    cin >> n >> mx;
    int m; // 박스의 개수 (1 ≤ m ≤ 10,000)
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c; // 보내는 번호 a, 받는 번호 b, 개수 c(1 ≤ c ≤ 10,000)
        cin >> a >> b >> c;

        path[a].push_back({b, c});
    }

    for (int i = 1; i <= n; i++)
        sort(path[i].begin(), path[i].end());

    int ans = 0;
    int sum = 0; // 택배에 실어져 있는 박스의 개수
    for (int cur = 1; cur <= n; cur++)
    {
        ans += cnt[cur], sum -= cnt[cur], cnt[cur] = 0; // 배송

        for (const auto &[next, c] : path[cur])
            if (sum + c <= mx) // 모든 박스를 실을 수 있는 경우
                sum += c, cnt[next] += c;
            else // 모든 박스를 실을 수 없는 경우 (다른 박스를 빼내어 현재 택배를 추가해야 함)
            {
                int rem = c + sum - mx; // 싣고 남은 박스의 개수
                cnt[next] += mx - sum, sum = mx;

                for (int ed = n; ed >= next + 1 && rem; --ed) // 가장 먼 마을부터 확인
                {
                    int &r = cnt[ed]; // ed번에 도착할 박스의 개수
                    if (r >= rem)
                        cnt[next] += rem, r -= rem, rem = 0;
                    else if (r && r < rem)
                        cnt[next] += r, rem -= r, r = 0;
                }
            }
    }

    cout << ans;
}