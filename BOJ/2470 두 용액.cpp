// 2470 두 용액
// https://www.acmicpc.net/problem/2470
/*
    투 포인터 (2,288KB, 16ms)
    시간 복잡도: 최대 O(n)?
    풀이)
    1) 입력된 정수를 배열 v에 저장한 후, 오름차순 정렬.
    2) 이후 왼쪽과 오른쪽에서부터 각각 값을 하나씩 빼낸 후 조사.
    - 만약 두 값의 합의 절댓값이 이전에 조사한 합 mn보다 작거나 같을 시, mn을 갱신해주며 두 용액을 ans에 저장.
    - 만약 두 값이 0보다 작을 시, l++ (l값을 올려 낮은 값을 높은 값으로 바꿈)
    - 만약 두 값이 0보다 클 시, r++ (r값을 내려 높은 값을 낮은 값으로 바꿈)
    - 주의할 점은, l값과 r값 조정 시 비교값을 mn이 아닌 0으로. (기준 및 구하려는 값은 0에 가까운 값이므로)
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 2'100'000'000
#define MAX 100'000 + 1
typedef pair<int, int> pii;

int main()
{
    FAST_IO;

    int n; // 용액의 수 (2 ≤ n ≤ 100,000)
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i]; // |vi| ≤ 1,000,000,000

    sort(v, v + n);

    pii ans = {0, 0};
    int mn = INF;
    int l = 0, r = n - 1;
    while (l < r)
    {
        if (abs(v[l] + v[r]) <= mn)
            mn = abs(v[l] + v[r]), ans = {v[l], v[r]};

        if (v[l] + v[r] <= 0)
            l++;
        else
            r--;
    }

    cout << ans.first << " " << ans.second;
}