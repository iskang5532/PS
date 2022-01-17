// 3273 두 수의 합
// https://www.acmicpc.net/problem/3273
/*
    투 포인터 (2,288KB, 12ms)
    시간 복잡도: 최대 O(n)
    풀이)
    1) 입력된 수열을 정렬.
    2) 왼쪽과 오른쪽의 두 방향에서 시작하여 현재 위치의 값을 선택하며, 값을 더함. (만약 더한 값이 x와 같을 시, ans++)
    - 만약 더한 값이 x보다 클 경우, r-- (l < r이므로 r값을 줄여 x에 가까워지도록 함.)
    - 만약 더한 값이 x보다 작을 경우, l++ (l < r이므로 l값을 키워 x에 가까워지도록 함.)
    3) 두 위치가 서로 만나기 전까지 2) 반복.
    etc.)
    - 문제에 "서로 다른 양의 정수..."라는 문구가 존재. 고로 [1, 1, 4, 4]와 같은 입력은 들어오지 않음. (문제를 제대로 안봐서 엄청 헤맸음)
    https://www.acmicpc.net/board/view/63700
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 100'000 + 1 // max n

int main()
{
    FAST_IO;

    int n; // 수열의 크기 (1 ≤ n ≤ 100,000)
    cin >> n;
    int v[MAX]; // 1 ≤ k ≤ 1,000,000
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int x; // 1 ≤ x ≤ 2,000,000
    cin >> x;

    sort(v, v + n);
    int ans = 0;
    int l = 0, r = n - 1;
    while (l < r) // '=='가 없는 이유는 서로 다른 정수를 이용해야 하므로. (1 ≤ i < j ≤ n)
    {
        if (v[l] + v[r] == x)
            ans++;

        if (v[l] + v[r] > x)
            r--;
        else
            l++;
    }

    cout << ans;
}

/*
    셋 (6,820KB, 24ms)
    시간 복잡도: 최대 O(2n) (erase, find: O(1))
    풀이)
    1) 셋에 모든 값을 저장함.
    2) 셋에서 임의의 원소 cur를 하나 뺀 후, a - cur == x가 되는 a값이 셋에 있는지 확인.
    만약 있을 경우, ans++해주며 a를 셋에서 빼줌.
    3) 셋에 원소가 없을 때까지 2) 반복.
 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 100'000 + 1 // max n

int main()
{
    FAST_IO;

    int n; // 수열의 크기 (1 ≤ n ≤ 100,000)
    cin >> n;
    unordered_set<int> us;
    for (int i = 0; i < n; i++)
    {
        int k; // 1 ≤ k ≤ 1,000,000
        cin >> k;
        us.insert(k);
    }
    int x; // 1 ≤ x ≤ 2,000,000
    cin >> x;

    int ans = 0;
    while (us.size())
    {
        int cur = *us.begin();
        us.erase(us.begin());

        int diff = x - cur;
        if (us.find(diff) != us.end())
            ans++, us.erase(diff);
    }

    cout << ans;
}

/*
    sol.3) 완전 탐색(3,852KB, 8ms)
    시간 복잡도: O(x/2)
    풀이)
    - 값이 존재하는지의 여부를 cnt배열에 저장. (입력된 값은 true)
    - 1부터 값을 탐색.
    만약 현재 값이 존재하면서 a-i == x를 만족하는 a가 존재할 시 ans++.
    - for문의 "(x + 1) >> 1"는 x가 짝수일 때에는 (x/2)-1까지, 홀수일 때에는 (x-1)/2까지 탐색하도록 해줌.
    - 주의할 점은, for문에서 a의 여부를 확인하기 위해 [x - i]를 하게 되는데, 이때 x의 값은 2M일 수 있음.
    즉, 배열의 크기는 입력되는 k의 최댓값(= 1M)이 아닌 x의 최댓값에 맞춰줘야 함.
    etc.) TLE 적정선은 k <= 1M인가?
    참고)
    - 반례: https://www.acmicpc.net/board/view/73734
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 1'000'001 // max k(= ai)

int main()
{
    FAST_IO;

    int n; // 수열의 크기 (1 ≤ n ≤ 100,000)
    cin >> n;
    bool cnt[MAX * 2]; // cnt[i] = true일 경우, 수 i는 존재.
    fill(&cnt[0], &cnt[0] + sizeof(cnt[0]) / sizeof(cnt), false);
    for (int i = 0; i < n; i++)
    {
        int k; // 1 ≤ k ≤ 1,000,000
        cin >> k;
        cnt[k] = true;
    }
    int x; // 1 ≤ x ≤ 2,000,000
    cin >> x;

    int ans = 0;
    for (int i = 1; i < (x + 1) >> 1; i++)
        if (cnt[i] && cnt[x - i])
            ans++;

    cout << ans;
}