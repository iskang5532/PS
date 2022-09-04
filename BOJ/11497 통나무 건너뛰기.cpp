// 2022-08-24
// 11497 통나무 건너뛰기
// https://www.acmicpc.net/problem/11497
/*
    그리디, 정렬 (2,312KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 통나무 간의 높이의 차이를 최소화해야 하는 문제. 주의할 점은, 첫 번째 통나무와 마지막 통나무 간 차이 또한 포함된다는 것이다.
    - 입력된 통나무의 높이를 arr[]에 저장 후, 오름차순 정렬.
    - 재배치할 통나무를 저장할 v[].
    - arr의 첫 번째 통나무 arr[0]부터 v에 저장한다.
    이후 다음 통나무를 v에 추가해야 하는데, arr[i]와 인접한 통나무 arr[i+1]이 아닌 arr[i+2]를 v에 추가하여 arr[i]의 옆에 둔다.
    - arr의 마지막(n-1. 혹은 n-2일 수 있음) 통나무까지 v에 저장하였을 경우, 나머지 통나무 또한 v에 추가하여 재배치해야 한다.
    이번에 재배치할 통나무는 arr의 앞에 존재하는 통나무부터가 아닌 뒤에 존재하는 통나무부터 사용한다.
    - 사용되지 않은 마지막에서 가장 가까운 통나무에서부터 마찬가지로 인접한 통나무를 건너뛴 arr[i-2]를 v에 추가한다.
    마지막 통나무가 첫 번째 재배치에서 사용된 통나무일 수 있음에 주의.
    - v에 저장된 통나무 간의 높이 차이 중에서 최댓값을 ans에 저장.
    이때, v[0]과 v[n-1] 또한 빼먹지 않고 비교해야 한다.
    etc.) 증명을 못하겠음
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003 // max n

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 통나무의 개수 (5 ≤ n ≤ 10,000)
        cin >> n;
        vector<int> arr(n); // 1 ≤ k ≤ 100,000
        for (auto &i : arr)
            cin >> i;
        sort(arr.begin(), arr.end());

        vector<int> v; // 새로 배치된 통나무를 저장
        for (int i = 0; i < n; i += 2)
            v.push_back(arr[i]);
        for (int i = n - 1 - (n & 1); i >= 0; i -= 2) // 뒤에서부터 값을 추가. (n이 홀수일 경우 [n-2], 짝수일 경우 [n-1]부터)
            v.push_back(arr[i]);

        int ans = 0;
        for (int i = 0; i < n - 1; i++)
            ans = max(ans, abs(v[i] - v[i + 1])); // 인접한 두 통나무의 차이

        cout << max(ans, abs(v[0] - v[n - 1])) << endl; // [0]과 [n-1]의 차이
    }
}

/*
    이분 탐색 (TLE)
    시간 복잡도: O(n^2 * log(l))
    풀이) 정답일 수 있는 통나무간의 최소 높이 h를 이분 탐색으로 구함
    etc.) 시간복잡도 생각 안하고 이분탐색으로 풀어보고 싶어서 풀어봄. 답인지 아닌지는 TLE라 모름
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003 // max n

bool isValid(int v[], int n, int h)
{
    bool used[MAX]{
        true,
    };

    int cur = v[0];
    for (int idx = 0; idx < n - 1; idx++)
    {
        bool valid = false; // 다음 나무를 선택했는가
        for (int i = n - 1; i >= 0 && !valid; --i)
            if (!used[i] && abs(cur - v[i]) <= h) // 사용한 적이 없으면서 두 나무의 차이가 h 이하인 경우
            {
                cur = v[i], used[i] = true;
                valid = true;
            }

        if (!valid)
            return false;
    }
    return abs(v[0] - cur) <= h; // 첫 번째 나무와 마지막 나무의 차이
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 통나무의 개수 (5 ≤ n ≤ 10,000)
        cin >> n;
        int v[MAX]; // 1 ≤ vi ≤ 100,000
        for (int i = 0; i < n; i++)
            cin >> v[i];

        sort(v, v + n);

        int ans = 0;
        int l = -1, r = 100'003; // max vi
        while (l <= r)
        {
            int mid = (l + r) / 2;

            isValid(v, n, mid) ? r = mid - 1, ans = mid
                               : l = mid + 1;
        }

        cout << ans << endl;
    }
}