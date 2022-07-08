// 13335 트럭
// https://www.acmicpc.net/problem/13335
/*
    완전 탐색 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 매초 일어날 수 있는 일을 수행.
     - 다리 위로 트럭이 올라올 수 있음.
     - 다리 위에 있던 트럭이 밖으로 나갈 수 있음.
    - 다리 위의 무게가 0인 경우(= 모든 트럭이 다리를 지남), 경과된 시간 ans를 출력.
    - cnt에 i번째 차량이 다리 위를 건너는 시간을 저장한 후, 경과된 시간이 cnt[i]와 같을 경우, i번째 트럭을 다리 위에서 제거.
    etc.) 완전 탐색에서 더 최적화를 해보는 식으로 풀려다가 실패.
    참고)
    - 이론: https://www.secmem.org/blog/2022/01/16/How_to_approach_problems_7/
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'000 + 1 // 트럭의 최대 개수

int main()
{
    FAST_IO;

    int n, w, l; // 트럭의 수 n(1 ≤ n ≤ 1k), 다리의 길이 w(1 ≤ w ≤ 100), 다리의 최대하중 L(10 ≤ L ≤ 1,000)
    cin >> n >> w >> l;
    int v[MAX]; // v[i] = k일 떄, i번째 트럭의 무게
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int t = 1;          // 소모된 시간
    int weight = 0;     // 다리 위에 있는 트럭들의 무게
    int le = 0, ri = 0; // 다리에서 내려갈 트럭의 번호 le, 다리에 올라갈 트럭의 번호 ri
    int cnt[MAX];       // cnt[i] = k일 때, i번째 차량이 다리를 건너는 시간은 k
    while (true)
    {
        if (weight != 0 && cnt[le] == t) // 다리 위의 가장 앞에 있는 트럭이 건널 시간이 됐을 경우
            weight -= v[le], le++;
        if (ri < n && l >= weight + v[ri]) // 다리에 올라갈 차량이 남았으며, 해당 트럭을 추가해도 다리가 버틸 수 있을 경우
            weight += v[ri], cnt[ri] = t + w, ri++;

        if (weight == 0) // 모든 트럭이 다리를 건넌 경우
            break;

        t++;
    }

    cout << t;
}

// 3 5 10
// 5 5 5
// t: 11