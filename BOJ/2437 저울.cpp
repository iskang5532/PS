// 2022-07-21
// 2437 저울
// https://www.acmicpc.net/problem/2437
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 저울추를 v[]에 저장한 후, 오름차순 정렬.
    - 측정할 수 있는 무게를 저장할 ans. (ans = k일 경우, k까지 측정할 수 있음)
    - 측정할 수 없는 무게 중 최솟값을 구해야 하므로, ans + 1의 값이 정답이 됨.
    - v에 저장된 저울추를 하나씩 사용.
    만약 저울추가 ans + 1보다 작거나 같은 경우, ans + 1을 만들 수 있으며 ans + v[i] 또한 만들 수 있음. (= ans += v[i])
    만약 저울추가 ans + 1보다 큰 경우, ans + 1은 만들 수 없음. (= 정답은 ans + 1)
    - 위 풀이가 가능한 이유는 만들 수 있는 무게 ans + 1가 1부터 시작해서라고 생각.
    이전 값들을 만들 수 있으므로, 이전 값의 추가 존재하는지를 신경쓰지 않아도 됨.
    etc.) 어려움
    참고)
    이론: https://blog.naver.com/jinhan814/222281324898
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);

    int ans = 0; // 만들 수 있는 값
    for (int i = 0; i < n; i++)
    {
        if (v[i] > ans + 1)
            break;
        ans += v[i];
    }

    cout << ans + 1;
}