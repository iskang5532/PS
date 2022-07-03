// 2022-06-30
// 11508 2+1 세일
// https://www.acmicpc.net/problem/11508
/*
    그리디 (2,288KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 큰 값을 없애면 최소비용으로 구매할 수 있음.
    - 세 가지 제품 중 가장 낮은 값이지만 다른 제품에 비해 상대적으로 비싼 값일 경우 제외.
    - 입력된 값을 전체 가격인 ans에 저장 및 배열 v에 저장한 후 내림차순 정렬.
    - v의 세 번째 값마다 ans에서 제외. (세 가지 제품 중 마지막 제품은 구매 가격에서 제외)
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int ans = 0;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i], ans += v[i];
    sort(v, v + n, greater<int>());

    for (int i = 2; i < n; i += 3)
        ans -= v[i];
    cout << ans;
}