/* 
 * 1561 놀이 공원
 * 파라메트릭 서치
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1561
 * etc.) r의 값이 왜 1e11인지 모르겠음. 2G여야 하는게 아닌가? LLONG_MAX는 왜 틀린건가?(LLONG_MAX, 1e10, 2G 다 틀림)
 * 결정 문제로 바꾸는 것 자체는 쉬웠으나, 구한 l값을 응용하여 놀이기구의 번호를 도출해내는 과정이 어려웠음.
 * - 결정 문제로 바꾸어 품.
 * - 기준 시간(= mid)이 지났을 때 놀이기구에 탑승한 인원(= cnt)을 이용.
 * 만약 cnt > n인 경우 mid가 너무 커서 탑승 인원이 많은 것이며, cnt < n인 경우 mid가 너무 작아서  탑승 인원이 적은 것.
 * 또한 조건(cnt == n)에 맞는 최솟값을 구해야 하기 때문에 cnt >= n을 해줌. (값이 같아도 mid를 줄임)
 * 1) 적합한 시간(= l)을 구해준다.
 * 2) l-1분 탑승 인원을 구해준다. (l-1 ~ l 사이에 마지막 인원이 탑승한 경우도 있음. 예시는 아래)
 * 3) l분에 비어 있는 기구(= [i]%l == 0) 하나 당 cnt++.
 * 만약 cnt == n인 경우, 현재 기구의 번호(= i+1)를 출력.
 * 참고: https://blog.naver.com/jinhan814/222260291734 (놀이기구의 번호를 구하는 것에 대한 이론 참고)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    ll n, m; // 인원 (1 ≤ n ≤ 2G), 놀이기구의 개수 (1 ≤ m ≤ 10k)
    cin >> n >> m;
    vector<int> arr(m); // 번호 (1 ≤ 30)
    for (auto &elem : arr)
        cin >> elem;

    if (n <= m)
        cout << n;
    else
    {
        ll l = 1, r = 1e11; // ??

        while (l <= r)
        {
            ll mid = (l + r) / 2; // 기준 시간

            ll cnt = m; // mid분 지났을 때 탑승한 인원
            for (const auto &elem : arr)
                cnt += (mid / elem); // 현재 기구로 mid분 동안 탑승할 수 있는 최대 인원

            if (cnt < n)
                l = mid + 1;
            else
                r = mid - 1;
        }

        ll cnt = m;
        for (const auto &elem : arr)
            cnt += (l - 1) / elem;

        for (int i = 0; i < m; i++)
            if (l % arr[i] == 0) // 시간 l에 [i] 기구가 비어있는 경우 (= 탑승 가능한 경우)
            {
                cnt++;
                if (cnt == n)
                {
                    cout << i + 1;
                    break;
                }
            }
    }
}

// 5분대의 탑승을 구함.
// 6분대에 탑승할 수 있는 인원을 구함. 여기서, 현재 탑승 가능한 기구가 있을 경우 인원을 추가.
// 탑승 인원이 n이 되는 순간의 기구를 출력
// ans: 1
// 6 2
// 3 2
