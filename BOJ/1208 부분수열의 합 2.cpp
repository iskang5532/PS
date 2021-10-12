/* 
 * 1208 부분수열의 합 2
 * 이분 탐색, 비트 마스크 (14,440KB, 296ms)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1208
 * etc.)
 * - 입력된 수열을 절반으로 나눈 후, 수열마다 각각의 값을 더해 나올 수 있는 값을 모두 구해 값들을 저장 (= a, b)
 * 여기서, 나올 수 있는 값, 즉 경우의 수를 구하기 위해 비트 마스크를 사용.
 * - 구한 a와 b를 이용해 s가 나올 수 있는 짝의 개수를 구함.
 * 참고: https://blog.naver.com/jinhan814/222256514284 (입력된 수열을 쪼개는 것에 대한 이론)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
typedef long long ll;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, s; // 정수의 개수 (1 ≤ n ≤ 40), 합으로 만들 수 ( |s| ≤ 1M)
    cin >> n >> s;
    vector<int> v1, v2; // 두 개로 나눈 입력된 수열 (|k| ≤ 100k)
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (i & 1) // 홀
            v1.push_back(k);
        else // 짝
            v2.push_back(k);
    }

    ll ans = 0;
    auto get_cases = [&](const vector<int> &v) -> vector<int> // 경우의 수를 구함
    {
        vector<int> ret;
        int msb = 1 << v.size(); // 최상위 비트 (most significant bit, msb)
        for (int bit = 1; bit < msb; bit++)
        {
            int k = 0;
            for (int i = 0; i < v.size(); i++)
                if (bit & 1 << i) // i번 비트가 사용할 비트인 경우
                    k += v[i];
            ret.push_back(k);

            if (k == s) // 구한 값이 s인 경우 ans++ (이 조건문이 없을 경우 2%에서 틀림)
                ans++;
        }

        return ret;
    };

    vector<int> a = get_cases(v1); // v1으로 만들 수 있는 합에 대한 경우의 수 구하기
    vector<int> b = get_cases(v2);
    sort(a.begin(), a.end()), sort(b.begin(), b.end());

    for (const auto &elem : a)
    {
        int k = s - elem; // 값 s를 구하기 위한 값 (b에서 찾을 값)
        auto [lo, hi] = equal_range(b.begin(), b.end(), k);

        ans += hi - lo;
    }

    cout << ans;
}

// 2%: 구해진 a, b에서 자기 자신의 값에 대해 ans에 추가해 줘야 함. (이분 탐색하여 구한 값은 짝으로 구한 값)
// 입력된 수열이 [1, 2, 3, 4]이며 이때의 경우의 수는 a = [1, 2, 12], b = [3, 4, 34]라고 할 때 1, 2, 12, 3, 4, 34가 빠짐.

// TLE (bit mask)
#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
typedef long long ll;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, s; // 정수의 개수 (1 ≤ n ≤ 40), 합으로 만들 수 ( |s| ≤ 1M)
    cin >> n >> s;
    vector<int> arr(n); // |k| ≤ 100k
    for (auto &elem : arr)
        cin >> elem;

    ll ans = 0;
    ll msb = 1LL * 1 << n;
    for (ll bit = 1; bit < msb; bit++)
    {
        int k = 0;
        for (int i = 0; i < n; i++)
            if (bit & 1 << i)
                k += arr[i];
        if (k == s)
            ans++;
    }

    cout << ans;
}
