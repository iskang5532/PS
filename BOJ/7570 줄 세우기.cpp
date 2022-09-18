// 2022-09-15
// 7570 줄 세우기
// https://www.acmicpc.net/problem/7570
/*
    DP, LIS (5,804KB, 116ms)
    시간 복잡도: ?
    풀이)
    - 각 수의 차이가 1이 나는 LIS를 구하면 되는 문제. (LIS의 개수는 옮기지 않는 수의 개수)
    - 수 k까지의 LIS를 저장할 v[].
    - 수 k를 입력받은 후, k-1번 수가 이전에 나왔는지를 확인.
    만약 나왔을 경우, v[k]는 v[k-1] + 1의 값을 가짐. (이전까지의 길이 + 현재 값의 길이 1)
    참고)
    - 이론: https://blog.naver.com/jinhan814/222260814992
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX]{}; // v[i] = k일 때, i의 LIS는 k (단, 수의 차이가 1일 떄의 LIS)
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        v[t] += 1 + v[t - 1];
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, v[i]);
    cout << n - ans;
}
