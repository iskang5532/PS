// 2022-12-03
// 1015 수열 정렬
// https://www.acmicpc.net/problem/1015
/*
    정렬 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수가 정렬되었을 때의 위치를 구해야 한다.
    - v[]에 {입력된 값, 위치} 형식으로 값을 저장.
    이후, 값을 기준으로 오름차순 정렬.
    - 오름차순 정렬된 값을 하나씩 확인해가며, 인덱스의 현재 위치를 ans[]에 저장.
    etc.) 예제 입력과 예제 출력만을 보고 풀어서 지문은 모름
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n

int main()
{
    FAST_IO;

    int n; // 원소의 개수 (1 ≤ n ≤ 50)
    cin >> n;
    pii v[MAX]{}; // {값, 위치}
    for (int i = 0; i < n; i++)
        cin >> v[i].first, v[i].second = i;

    stable_sort(v, v + n); // 값을 기준으로 오름차순 정렬 (안정된 상태)

    int ans[MAX]{}; // 값의 위치를 저장
    for (int i = 0; i < n; i++)
        ans[v[i].second] = i;

    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}