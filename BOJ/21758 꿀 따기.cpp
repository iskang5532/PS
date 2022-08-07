// 2022-08-05
// 21758 꿀 따기
// https://www.acmicpc.net/problem/21758
/*
    누적 합 (2,800KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 꿀통을 세 가지 위치에 두어 답을 구할 수 있음.
    1. 가장 우측에 둠.
    - 이 경우, 벌의 위치는 가장 왼쪽에 한 마리, 그리고 그 외의 위치에 한 마리를 위치시킬 수 있다.
    나머지 한 마리의 벌을 위치시킨 후, 모을 수 있는 최대의 꿀의 양을 구한다.
    - 벌이 위치한 곳의 꿀은 캘 수 없다. 이는, 외곽에 있는 벌은 안쪽에 있는 벌이 있는 꿀을 제외해야 한다.
    2. 가장 좌측에 둠.
    - 위에서 언급한 우측에 둔 것과 같다. 편한 연산을 위해 reverse 후 1번과 똑같은 방법으로 구한다.
    3. 중간에 둔 경우(외곽이 아님)
    - 이 경우, 두 벌은 양 외곽에서 꿀을 모으며 꿀통에 도착해야 최대한 많은 꿀을 얻을 수 있다.
    또한, 꿀통의 위치는 벌이 방문할 때 얻을 수 있다. 즉, 두 번 얻을 수 있으므로 가장 큰 값 mx를 구한 후 두 번 얻는다.
    - n의 크기가 크므로, 누적 합을 이용하여 빠르게 구할 수 있도록 한다.
    etc.) 어려웠음.
    참고)
    이론: https://david0506.tistory.com/68
 */

#include <iostream>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int n; // 정수의 수 (3 ≤ n ≤ 100,000)
int v[MAX], pSum[MAX]{};
int mx = 0;

int get_ans(bool rvs = false)
{
    if (rvs)
        reverse(v, v + n);

    for (int i = 0; i < n; i++)
        pSum[i + 1] = v[i] + pSum[i];

    int ret = 0;
    int a = pSum[n] - v[0]; // 외곽에 위치한 벌이 모은 꿀
    for (int i = 1; i < n - 1; i++)
    {
        int b = pSum[n] - pSum[i] - v[i]; // 안에 위치한 벌이 모은 꿀

        ret = max(ret, a - v[i] + b);
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i], mx = max(mx, v[i]);

    int a = get_ans();                      // right (l to r)
    int b = get_ans(true);                  // left (r to l)
    int c = pSum[n] - v[0] - v[n - 1] + mx; // mid

    cout << max({a, b, c});
}