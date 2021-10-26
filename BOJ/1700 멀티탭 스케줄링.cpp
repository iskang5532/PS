/*
    1700 멀티탭 스케줄링
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1700
    etc.) 첫 풀이에서는 맵을 이용하여 개수를 이용하여 풀었지만 실패하였으며, 이후 가장 늦게 사용하는 플래그를 제거하는 쪽으로 풀이. (이를 구현하는 방법이 조금 이상하며, 더 쉬운 방법이 있을 텐데 귀찮았음.)
    - 멀티탭 구멍의 개수만큼 입력된 플래그를 꽂아 주며 카운팅(= cnt). (여기서 주의할 점은, 동일한 플래그가 입력으로 들어올 수 있는데, 이를 카운팅하면 안됨)
    - 모든 멀티탭의 구멍이 사용 중이며 입력이 남은 경우
    1) 입력된 플래그가 현재 사용 중인 플래그인 경우, 다음 입력을 확인. (= continue)
    2) 입력된 플래그가 현재 사용 중이 아닌 플래그인 경우, 교체.
    - 남아 있는 입력을 앞에서부터 확인하며, 사용 중인 플래그들과 같은 플래그가 나오면 플래그의 순서를 기억. 이는 남은 입력이 끝날 때까지 or 순서가 n개가 될 때까지 탐색
    기억된 플래그의 순서 중 가장 마지막인 플래그를 사용 중인 플래그에서 빼내어 현재 대기 중인 플래그와 교체. 이후 다음 입력을 확인.
    - 풀이에서는 플래그의 순서가 아닌 사용 여부를 기억(= check[i] == true)했으며 n-1개만을 기억 후, 사용 중인 플래그이면서 이후 사용이 가장 느린(= false) 플래그 찾아 제거.
    참고)
    - 반례 https://www.acmicpc.net/board/view/52676
 */

#include <iostream>
#include <vector>

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

    int n, k; // 멀티탭 구멍의 개수 N(1 ≤ N ≤ 100), 사용횟수 K(1 ≤ K ≤ 100)
    cin >> n >> k;
    int mx = 0;         // 플러그의 가장 높은 값
    vector<int> arr(k); // 전기용품의 이름 (1 ≤ Ai ≤ k)
    for (auto &elem : arr)
        cin >> elem, mx = max(mx, elem);

    vector<bool> plug(mx + 1, false); // plug[i]일 경우, i번째 플러그를 사용 중
    int cnt = 0, ans = 0;             // 멀티탭 사용 개수 cnt, 교체 횟수 ans
    for (auto curr = arr.begin(); curr != arr.end(); curr++)
        if (plug[*curr]) // 사용 중인 플래그인 경우
            continue;
        else if (cnt != n) // 멀티탭 공간이 남는 경우
            plug[*curr] = true, cnt++;
        else if (plug[*curr] == false && cnt == n) // 공간 부족
        {
            vector<bool> check(mx + 1, false); // 남아 있는 플래그들을 이용해 사용 중인 플래그의 이용 순서를 확인
            int t = 0;                         // 확인 완료한 사용 중 플래그의 개수
            for (auto itr = curr + 1; itr != arr.end() && t + 1 != n; itr++) // 모든 플래그 확인 or 제일 늦게 사용될 플래그를 확인할 때까지 (+1인 이유는 어차피 plug[curr] == false이기 때문)
                if (plug[*itr] && check[*itr] == false)                      // 만약 사용 중 플래그 && 확인이 안 된 경우
                    t++, check[*itr] = true;                                 // 확인 플래그 개수 +1, 플래그 확인

            for (int i = 1; i <= mx; i++) // 사용 중인 플래그를 확인하기 위해 모두 탐색
                if (plug[i] && !check[i]) // 사용 중 && 마지막에 사용되는 경우
                {
                    plug[i] = false, plug[*curr] = true, ans++; // 플래그 교체
                    break;
                }
        }

    cout << ans;
}

/* 27%
3 4
1 2 1 3
ans: 0

2 15
3 2 1 2 1 2 1 2 1 3 3 3 3 3 3
ans: 2

3 14
1 4 3 2 5 4 3 2 5 3 4 2 3 4
ans: 4
*/