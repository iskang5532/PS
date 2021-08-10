/* 
 * 11441 합 구하기
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/11441
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n + 1, 0); // 현재 값과 이전 값을 합친 누적 합을 저장
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        arr[i] = arr[i - 1] + k; // 이전 값 + 현재 값
    }

    int m;
    cin >> m;
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        l--; // [r, l - 1]이 우리가 구할 범위이므로 l--

        cout << arr[r] - arr[l] << endl;
    }
}
// 누적 합 arr
// [10 20 30 40 50] 입력일 때의 누적 합 arr는
// [10 30 60 100 150]