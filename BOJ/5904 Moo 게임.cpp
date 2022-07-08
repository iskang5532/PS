// 5904 Moo 게임
// https://www.acmicpc.net/problem/5904
/*
    재귀, 분할 정복 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이) *이론을 참고하면 이해가 빠름.
    - 배열 S를 선언한 후, k번째 수열의 길이를 저장. (S의 크기는 최대 28. 10^9 < S[28]이므로)
    - k번째 수열의 문자열은 앞, 뒤로 k-1번째 문자열이 있으며, 중간에 문자열 "mo..o"가 있다.
    즉, n번째 위치가 k-1번째 수열의 문자열일 경우, k-1번째 수열의 문자열을 탐색하여 문자를 구해줄 수 있다.
    이는 k-1번째, k-2번째 또한 마찬가지이므로 재귀적으로 풀어 나갈 수 있다.
    - n번째 문자의 위치 탐색.
     - 앞부분임을 알기 위해서는 n이 이전 수열의 길이인 S[k-1]보다 작아야 하며,작을 경우 k-1번째 수열에서 n번째 문자를 탐색해준다.
     (이후 중간 부분과 뒷부분은 앞부분인 k-1번째 수열을 제외한 문자열이므로 n -= S[k-1])
     - 중간 부분임을 알기 위해서는 n이 "mo..o", 즉 k + 3보다 작아야 한다. 만약 작을 경우
     1. n == 0, 이 경우 'm'을 반환
     2. m != 0, 이 경우 'o'를 반환.
     - 앞부분 혹은 중간 부분이 아닐 경우, 뒷부분이다. 이는 k-1번째 수열의 문자열이므로 n의 위치를 조정시킨 후 재귀. (n -= k + 3)
    etc.) [0]부터 첫 번째 글자라 헷갈렸음.
    참고)
    - 이론: https://blog.kakaocdn.net/dn/byHxiR/btq4NK7ZEbB/eKlO3RjdVK1DyqDjhgaOIK/img.png (https://excited-hyun.tistory.com/110)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 28 // 10^9 < S[28]

int S[MAX]; // k번째 수열의 길이

char func(int k, int n) // k번째 수열, n번째 글자
{
    if (k == 0)
        return "moo"[n];

    if (n < S[k - 1]) // 앞부분
        return func(k - 1, n);

    n -= S[k - 1];
    if (n < k + 3) // 중간 부분
        return n == 0 ? 'm' : 'o';
    else // 뒷부분
        return func(k - 1, n - (k + 3));
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // N (1 ≤ N ≤ 10^9)
    cin >> n;
    n--;

    S[0] = 3;
    int k = 1;
    for (; S[k - 1] <= n; k++)
        S[k] = (S[k - 1] * 2) + (k + 3);
    k--;

    cout << func(k, n) << endl;
}

// 39
// ans: m

// 99
// ans: m