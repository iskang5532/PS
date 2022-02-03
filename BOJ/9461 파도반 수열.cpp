// 9461 파도반 수열
// https://www.acmicpc.net/problem/9461
/*
    DP (2,020KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 점화식: fibo[n] = fibo[n-2] + fibo[n-1] 또는 fibo[n] = fibo[n-1] + fibo[n-5]
    - [1], [2]은 1로 예외 처리 해주었음. ([3] 또한 1이므로 추가로 넣어줌)
    - 피보나치 수열과 흡사한듯.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 100 + 1
using ll = long long;

int main()
{
    FAST_IO;

    ll fibo[MAX];
    fibo[1] = fibo[2] = fibo[3] = 1;
    for (int i = 4; i < MAX; i++)
        fibo[i] = fibo[i - 2] + fibo[i - 3];

    int tc;
    cin >> tc;
    while (tc--)
    {
        int k;
        cin >> k;
        cout << fibo[k] << endl;
    }
}