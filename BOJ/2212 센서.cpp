/*
    2212 센서
    그리디 (2,184KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2212
    풀이)
    - n개의 센서를 k개의 그룹으로 나누는 문제.
    2개 이상의 그룹으로 나뉘었을 때 각 그룹 간 끝에 존재하는 센서끼리는 가까운 집중국으로 연결이 되며, 이는 불필요한 거리를 제거하게 된 것이다.
    이러한 필요없는 거리를 제거한 후, 집중국까지의 거리가 구해야 할 집중국의 수신 가능 영역이며, 필요없는 거리의 최댓값을 제거하게 된다면 남아있는 센서와 집중국의 거리는 최소가 될 것이다.
    1) 집중국 간의 거리를 구한 후 저장해줌. (= gap, 오름차순 정렬)
    2) 2개의 영역부터 1개의 필요 없는 거리가 제거(= k-1개)되므로, gap의 앞에서부터 값을 더해주되 k-1개는 빼줌. (큰 값을 k-1개 제외)
    이후 더해진 값을 출력.
    - 자세한 설명은 밑에 이론 사이트 참고
    etc.) 어려웠음. 그리디, DP는 난이도가 낮아도 감이 안잡힘..
    참고)
    - 이론: https://journeytosth.tistory.com/16
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // accumulate

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, k; // 센서의 개수 N(1 ≤ N ≤ 10k), 집중국의 개수 K(1 ≤ K ≤ 1k)
    cin >> n >> k;

    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;
    sort(arr.begin(), arr.end());

    vector<int> gap;
    for (int i = 1; i < n; i++)
        gap.push_back(arr[i] - arr[i - 1]);
    sort(gap.begin(), gap.end());

    k = min(k, n); // n > k일 수도 있으므로, k의 값은 항상 n 이하로 만들어줌
    cout << accumulate(gap.begin(), gap.end() - (k - 1), 0);
}