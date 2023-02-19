// 2023-02-14
// 2473 세 용액
// https://www.acmicpc.net/problem/2473
/*
    투 포인터 (2,020KB, 24ms)
    시간 복잡도: ?
    풀이)
    - v[0] 혹은 v[n-1]의 값을 하나의 용액으로 사용하고 나머지 부분에 투 포인터를 적용하여 최적의 값을 찾음. (나머지 부분의 투 포인터는 두 용액 문제와 동일)
    v의 끝 값부터 사용하므로, 모든 영역을 탐색할 수 있음.
    - 세 용액을 이용하여 0에 최대한 가까운 값을 저장 후 출력.
    etc.) 투 포인터 사이에 용액을 하나 선택해서 판별하는 줄 알았으나, 용액을 제외한 나머지 부분에 투 포인터를 적용하는 거였음
    참고)
    - 이론: https://blog.naver.com/jinhan814/222093798744
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
#define INF 0x7f7f7f7f'7f
#define MAX 5'003 // max n

ll mn = INF; // 0에 가장 가까운 세 용액의 합
ll a, b, c;  // answer

int main()
{
    FAST_IO;

    int n; // 용액의 수 (3 ≤ n ≤ 5,000)
    cin >> n;
    ll v[MAX]; // |vi| ≤ 1,000,000,000
    for (ll i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);

    for (int pos = 0; pos < n - 2; pos++) // 선택된 용액 (추가로 두 개의 용액이 선택되어야 하므로 -2)
    {
        int l = pos + 1, r = n - 1;
        while (l < r)
        {
            ll sum = v[pos] + v[l] + v[r]; // 세 용액의 합
            if (abs(sum) < mn) // 이전에 구한 값보다 0에 가까운 경우
                mn = abs(sum), a = v[pos], b = v[l], c = v[r];

            if (sum <= 0) // 세 용액의 합이 음수일 경우, 음수의 값을 높임
                l++;
            else // 양수의 값을 낮춤
                r--;
        }
    }

    cout << a << ' ' << b << ' ' << c;
}