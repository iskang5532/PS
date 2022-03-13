// 17419 비트가 넘쳐흘러
// https://www.acmicpc.net/problem/17419
/*
    비트마스킹 (3,680KB, 8ms)
    시간 복잡도: O(n)
    풀이)
    - 문제에 연산이 주어졌으므로, k가 0이 될 때까지 연산을 수행하여 답을 얻을 수 있을듯싶으나, n의 자릿수가 커 비트 연산이 불가능.
    - K = K-(K&((~K)+1))
    1. ~k + 1 == -k
    2. k & -k는 LSB(최우측 1)을 구함.
    3. k - LSB이므로, 기존 k에서 LSB를 제거.
    즉, 켜져 있는 비트의 개수만큼 해당 연산은 반복됨.
    그러므로, 입력된 수에서 '1'의 개수를 세어준 후 출력해줌.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 3,000,000
    cin >> n;

    string s;
    cin >> s;

    int cnt = 0;
    for (const auto &c : s)
        if (c == '1')
            cnt++;

    cout << cnt;
}