// 2022-08-27
// 17305 사탕 배달
// https://www.acmicpc.net/problem/17305
/*
    sol.1) 누적합 (5,224KB, 64ms)
    시간 복잡도: ?
    풀이)
    - 가장 효율적인 사탕만을 뽑아서 구성하면 정답일 것 같지만, 무게가 여유가 생기는 오답이 생길 수 있음.
    즉, 무게 제한에 최대한 근접하면서 효율적인 사탕을 이용해야 함.
    - 3g 사탕 p3개와 5g 사탕 p5개의 무게가 w를 넘지 않으면서 최대 당도를 가져야 함.
    속도를 위해 3g과 5g 사탕 당도의 누적합을 저장하여 이용하였으며, 입력된 값을 내림차순 정렬 후에 누적합을 저장.
    - p3와 p5를 구할 때 주의할 점은, 구한 p3를 이용한 3g 사탕의 무게가 w를 넘을 수 있다는 것이다.
    또한, p3를 구하고서 남는 무게의 여유를 5g 사탕으로 채울 수 있지만, 5g 사탕의 개수가 입력된 개수보다 많을 수 있음에 주의.
    etc.) 슬라이딩 윈도우 느낌
    참고)
    - 이론: https://www.acmicpc.net/source/40144611
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

int main()
{
    FAST_IO;

    int n, w; // 사탕의 개수 N(1 ≤ N ≤ 250,000), 무게 제한 w(0 ≤ w ≤ 5n)가 주어진다.
    cin >> n >> w;
    vector<ll> pSum3(1, 0), pSum5(1, 0); // 각각 3g과 5g 사탕 당도의 누적합
    for (int i = 0; i < n; i++)
    {
        int t, s; // 사탕의 종류 t, 당도 s (t ∈ {3, 5}, 1 ≤ s ≤ 1,000,000,000)
        cin >> t >> s;
        (t == 3 ? pSum3 : pSum5).push_back(s);
    }

    sort(pSum3.begin() + 1, pSum3.end(), greater<ll>());
    sort(pSum5.begin() + 1, pSum5.end(), greater<ll>());

    for (int i = 1; i < pSum3.size(); i++)
        pSum3[i] += pSum3[i - 1];
    for (int i = 1; i < pSum5.size(); i++)
        pSum5[i] += pSum5[i - 1];

    ll ans = 0;
    for (int p3 = 0; p3 < pSum3.size() && 3 * p3 <= w; p3++) // 선택한 3g 사탕의 개수 (고른 무게가 w를 넘으면 안됨)
    {
        int p5 = min<int>(pSum5.size() - 1, (w - 3 * p3) / 5); // 선택한 5g 사탕의 개수 (최대 개수는 5g 사탕의 개수)
        ans = max(ans, pSum3[p3] + pSum5[p5]);
    }

    cout << ans;
}

/*
    sol.2) 구현 (3,688KB, 60ms)
    시간 복잡도: ?
    풀이)
    - 무게 제한에 맞춰 가장 효율적인 5g 사탕을 사용.
    이때 사용한 5g 사탕의 개수를 p5에 저장.
    만약 5g 사탕을 모두 사용했음에도 무게에 여유가 있을 경우, 가장 효율적인 3g 사탕을 사용.
    이때 사용한 3g 사탕의 개수를 p3에 저장.
    - 5g 사탕을 하나씩 빼가며 무게에 여유를 줘 남은 3g 사탕으로 채우게 된다면 더 효율적인가를 확인.
    만약 더 효율적일 경우, 5g 사탕을 뺀 후 남은 공간에 3g 사탕을 채움.
    etc.) 첫 풀이
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

int main()
{
    FAST_IO;

    int n, w; // 사탕의 개수 N(1 ≤ N ≤ 250,000), 무게 제한 w(0 ≤ w ≤ 5n)가 주어진다.
    cin >> n >> w;
    vector<int> v3, v5;
    for (int i = 0; i < n; i++)
    {
        int t, s; // 사탕의 종류 t, 당도 s (t ∈ {3, 5}, 1 ≤ s ≤ 1,000,000,000)
        cin >> t >> s;
        (t == 3 ? v3 : v5).push_back(s);
    }

    sort(v3.begin(), v3.end(), greater<int>());
    sort(v5.begin(), v5.end(), greater<int>());

    ll ans = 0, p3 = 0, p5 = 0;
    {
        for (int i = 0; i < v5.size() && w >= 5; i++)
            w -= 5, p5++, ans += v5[i];
        for (int i = 0; i < v3.size() && w >= 3; i++)
            w -= 3, p3++, ans += v3[i];
    }
    {

        ll a = 0, b = 0;                                           // 우선적으로 빠질 5g 사탕의 당도의 합 a, 우선적으로 추가될 3g 사탕의 당도의 합 b
        for (int i = p5 - 1, t = 0; i >= 0 && p3 < v3.size(); --i) // t: 채울 수 있는 3g 사탕의 개수
        {
            a += v5[i], w += 5;

            int cnt = w / 3; // 이번에 생긴 채울 수 있는 3g 사탕의 개수 (5g를 뺌으로 인해 3g를 추가할 수 있게 됨)
            w %= 3;
            for (int i = p3 + t; i < p3 + t + cnt && i < v3.size(); i++)
                b += v3[i];
            t += cnt;

            if (a < b) // 3g를 채우는 것이 더 효율적인 경우
            {
                ans += b - a;

                a = 0, b = 0;
                p5 = i, p3 += t, t = 0;
            }
        }
    }

    cout << ans;
}

// input:
// 5 12
// 5 10
// 5 10
// 3 5
// 3 5
// 3 5
// ans:
// 20