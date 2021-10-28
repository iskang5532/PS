/*
    1041 주사위
    그리디, 구현 (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1041
    etc.) n이 증가할 때마다 노출되는 주사위 면의 개수를 구하는 게 어려웠음.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222247849129
 */

#include <iostream>
#include <vector>
#include <algorithm> // min, max
#include <cmath>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
typedef long long ll;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    ll n; // 주사위의 개수 (1 <= n <= 1M)
    cin >> n;
    ll a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    if (n == 1) // 하나일 경우 예외 처리
    {
        cout << a + b + c + d + e + f - max({a, b, c, d, e, f});
        return 0;
    }

    ll p1 = min({a, b, c, d, e, f});                                                                       // 한 쪽 노출
    ll p2 = min({a + b, a + d, a + e, a + c, b + d, b + c, b + f, d + e, d + f, e + c, e + f, c + f});     // 두 쪽 노출
    ll p3 = min({a + b + d, a + d + e, a + e + c, a + c + b, b + d + f, d + e + f, e + c + f, c + b + f}); // 세 쪽 노출

    ll m3 = p3 * 4;
    ll m2 = p2 * (((n - 2) * 4) +           // 위
                  ((n - 1) * 4));           // 옆
    ll m1 = p1 * (pow(n - 2, 2) +           // 위
                  ((n - 1) * (n - 2) * 4)); // 옆

    // cout << "p3 : " << p3 << "  m3 : " << m3 << endl;
    // cout << "p2 : " << p2 << "  m2 : " << m2 << endl;
    // cout << "p1 : " << p1 << "  m1 : " << m1 << endl;
    cout << m1 + m2 + m3;
}

// p\n 2   3       4       5
// 1   0   2*4+1   3*8+4   4*12+9
// 2   4   8+4     12+8    16+12
// 3   4   4       4       4

// ㅁㅁㅁ
// ㅁㅁㅁ
// ㅁㅁㅁ

// ㅁㅁㅁㅁ
// ㅁㅁㅁㅁ
// ㅁㅁㅁㅁ
// ㅁㅁㅁㅁ

// ㅁㅁㅁㅁㅁ
// ㅁㅁㅁㅁㅁ
// ㅁㅁㅁㅁㅁ
// ㅁㅁㅁㅁㅁ
// ㅁㅁㅁㅁㅁ