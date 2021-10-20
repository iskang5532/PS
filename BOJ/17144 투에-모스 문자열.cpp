/*
    17144 투에-모스 문자열
    투에-모스 문자열 (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/17144
    etc.) 규칙을 찾아야 하는 문제였으며, 규칙이 보일 것 같으면서도 안보이면서도.. 긴가민가 했던 문제
    - 네 개의 값을 이용. 따라서 이용할 범위의 최소 길이는 4. (굳이 4가 아니어도 될 듯하며, 값이 높아질수록 시간이 짧아지지 않을까 싶음)
    - 범위를 잡을 때 2의 제곱 단위로 이용하며, 비트를 이용.
    - r은 2^n꼴이며 k보다 클 때, r/2의 왼쪽 부분과 오른쪽 부분은 서로 반전된 값. (나중에 질문 게시판을 보며 안 사실)
    - k == 21이라고 가정했을 때,
    1) k보다 큰 2^n 값은 32, 작은 값은 16이다. (= 16 ≤ k ≤ 32; l == 16, r == 32)
    2) l과 r 사이의 간격을 len이라고 하며, len /= 2일 때, l + len 범위 안에 k값이 존재하는지 확인.
    - l을 움직이며 k의 위치를 특정한다. (이분탐색 느낌)
    - 만약 존재할 경우, 3번으로 이동.
    - 만약 존재하지 않을 경우, 다음 칸(= +len)에 위치한다는 것이며, 이는 이전 칸과 비트가 반전된다는 뜻이므로 반전이라는 특징을 flag에 저장해준다.
    또한 l값을 이동시켜줌. (l += len)
    3) len을 반으로 줄인 후, 다시 2번을 실행.
    참고: https://comkiwer.tistory.com/entry/msb-구하기 (최상위 비트 구하기)
 */

#include <iostream>

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

    const bool arr[4] = {0, 1, 1, 0};

    ll k; // 1 ≤ k ≤ 10^18
    cin >> k;
    if (k <= 4)
    {
        cout << arr[k - 1];
        return 0;
    }

    int cnt_zero = __builtin_clzll(k); // 최상위 비트의 앞에 있는 0의 개수를 파악
    ll r = 1LL << (64 - cnt_zero);     // 구한 0의 개수로 k보다 큰 비트 구하기

    bool flag = true; // is reversed?

    ll l = (r >> 1) + 1;
    ll len = r >> 2;
    while (len >= 4)
    {
        if (l + len < k)
            l += len, flag = !flag;

        len >>= 1;
    }

    bool ans = arr[k - l];
    flag ? cout << !ans : cout << ans;
}