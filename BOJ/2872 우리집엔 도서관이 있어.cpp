// 2022-08-16
// 2872 우리집엔 도서관이 있어
// https://www.acmicpc.net/problem/2872
/*
    그리디 (3,072KB, 32ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값 중 값이 n인 위치 v[i]에서 이전에 나온 값 중 조건을 만족하는 값의 개수가 몇 개인지 탐색.
    조건이란, n-cnt의 값이 [0, i] 안에 존재하는지이다. 만약 v[i]가 n-cnt일 경우, cnt++를 해준다.
    마찬가지로 n-cnt가 [0, i-1]안에 존재하는지 확인하며, v[j]가 n-cnt일 경우 cnt++해준다.
    이러한 조건을 만족하는 수의 개수를 cnt에 저장한다.
    - cnt의 개수만큼은 이미 정렬된 수이다. 그러므로, n - cnt만큼의 수를 정렬해주기만 하면 된다.
    etc.) LIS 느낌. 설명이 어려움
    참고)
    - 이론: https://ip99202.github.io/posts/%EB%B0%B1%EC%A4%80-2872-%EC%9A%B0%EB%A6%AC%EC%A7%91%EC%97%94-%EB%8F%84%EC%84%9C%EA%B4%80%EC%9D%B4-%EC%9E%88%EC%96%B4/
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 300'003 // max n;

int main()
{
    FAST_IO;

    int n; // 책의 개수 (n ≤ 300,000)
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int mx = n, cnt = 0;
    for (int i = n - 1; i >= 0; --i)
        if (v[i] == mx) // n - cnt일 경우
            cnt++, mx--;

    cout << n - cnt;
}