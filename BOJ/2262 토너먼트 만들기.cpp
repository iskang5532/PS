// 2262 토너먼트 만들기
// https://www.acmicpc.net/problem/2262
// <B>는 11이 아닌 '10'이다.
/*
    sol.1) 그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 시합은 순위가 낮은 사람(= 큰 값) 먼저 진행한다.
    - 상대는 양 옆 중에서 더 큰 값과 진행한다.
    만약 가장 왼쪽 혹은 오른쪽 사람일 경우, 옆 사람과 시합을 진행한다. (한 명밖에 없으므로)
    - 가장 큰 값만을 이용하므로, 우선순위 큐를 이용.
    1. 입력된 값을 우선순위 큐에 저장.
    2. 가장 높은 값(= pq.top())을 빼어 k에 저장. 이후 배열 v에서 k의 위치인 pos를 찾음.
    3. k(= v[pos])와 시합할 사람을 탐색.
    - 만약 pos가 가장 왼쪽인 경우, 우측 사람과 대결 (= v[pos+1])
    - 만약 pos가 가장 오른쪽인 경우, 좌측 사람과 대결 (= v[pos-1])
    - 만약 pos의 양옆에 두 사람이 존재하는 경우, 두 사람 중 값이 더 큰 사람과 대결.
    4. 랭킹의 차이인 gap을 ans에 저장하며, v[pos]는 v에서 제외한다.
    k가 졌기 때문. (k가 승리하여 토너먼트를 진행할 경우는 없음.)
    5. 시합을 더 이상 진행할 수 없을 때까지 반복. (= 큐의 크기가 2 이상이 아닌 경우. 이는 대결할 사람이 둘이 아니게 된다면 종료)
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<int> v(n);
    priority_queue<int> pq;
    for (auto &k : v)
        cin >> k, pq.push(k);

    int ans = 0;
    while (pq.size() >= 2)
    {
        int k = pq.top(); // 가장 큰 값
        pq.pop();

        int pos = 0;
        for (pos = 0; pos < v.size(); pos++) // v에서 k의 위치를 탐색
            if (v[pos] == k)
                break;

        int gap = 0;
        if (v[pos] == v.front()) // 왼쪽? (= 시합할 사람이 오른쪽밖에 없음)
            gap = abs(v[pos] - v[pos + 1]);
        else if (v[pos] == v.back()) // 오른쪽? (= 시합할 사람이 왼쪽밖에 없음)
            gap = abs(v[pos - 1] - v[pos]);
        else // 양쪽의 사람 중 값이 큰 사람과 대결
            gap = abs(v[pos] - max(v[pos - 1], v[pos + 1]));

        ans += gap;
        v.erase(v.begin() + pos);
    }

    cout << ans;
}

/*
    sol.2) DP (2,416KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 이 문제의 특징은 서로 '인접'한 파일이 합쳐져야 한다는 것.
    - dp[i][j]일 경우, 구간 (i, j)까지의 최솟값을 저장.
    - dp를 구하기 위해 구간의 범위(= l, r) 및 구간의 크기(sz)를 이용.
    범위는 0부터 n-1까지이며, 크기는 1부터 n-1까지이다. (크기는 시작점에서부터)
    - dp를 구할 때 랭킹 차이의 합을 이용하며, 시합 후에는 작은 값(= 높은 순위)이 올라오게 된다. (= 구간에서 최종적으로 승리한 사람)
    만약 sz >= 3일 시, 각 범위에서는 이전에 시합을 치뤄 승리하게 된 순위(= l_w, r_w)가 존재할 것이며, dp[l][r]을 구하기 위해서는 이 두 순위를 대결시켜야 한다.
    두 순위는 각 범위에서의 최솟값일 것이다. 이를 고려해 각 범위에서의 최솟값을 저장할 winner를 만들어준다.
    0. winner를 만들어 각 범위에서 가장 작은 값을 저장함.
    1. 범위를 len에 맞춰 탐색.
    1-1. 1인 경우
    - 구간을 나눌 방법은 한 개이다. 서로 인접한 값의 차이가 가장 작은 값이 되므로 dp에 저장.
    이후 l, r값을 변경해가며 나머지 범위를 탐색.
    1-2. 2인 경우
    - 구간을 나눠주며, [1][2]+[3], [1]+[2][3]의 결과중 가장 작은 값을 dp에 저장.
    이후 l, r값을 변경해가며 나머지 범위를 탐색.
    2. ~n-1까지 탐색. 최종적으로 dp[0][n-1]의 값이 두 선수의 랭킹 차이의 총 합의 최솟값이 된다.
    etc.)
    - DP가 먼저 떠올랐던 문제. 11066 파일 합치기와 비슷한 문제.
    - winner를 안만들고 비교 때마다 l_w, rval을 구해줬는데 시간이 오래걸림. (TLE는 아녔음)
    참고)
    - 이론: https://justicehui.github.io/ps/2019/01/15/BOJ2262/
            https://cocoon1787.tistory.com/317
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 258

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 256
    cin >> n;
    vector<int> v(n);
    for (auto &k : v)
        cin >> k;

    int dp[MAX][MAX]; // dp[i][j] = k일 경우, 구간 (i, j)에서 랭킹 차이의 합의 최솟값은 k
    fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), 0);

    int winner[MAX][MAX]; // 구간에서의 최솟값 (winner[1][3] = 2일 경우, 구간 (1, 3)에서 가장 작은 값은 2 (= 1번과 2번, 3번의 시합에서 올라오게 된 사람은 2위이며, 이는 구간 (1, 3)에서 가장 높은 순위))
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                winner[i][i] = v[i];
            else
                winner[i][j] = min(winner[i][j - 1], v[j]);

    for (int sz = 1; sz < n; sz++) // 구간의 크기
        for (int l = 0; l < n - sz; l++)
        {
            int r = l + sz;

            dp[l][r] = INF;
            for (int mid = l; mid < r; mid++)
            {
                int l_w = winner[l][mid], r_w = winner[mid + 1][r]; // 각 구간에서의 가장 작은 값 (= 각 구간에서 토너먼트를 통해 올라온 순위)
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r] + abs(l_w - r_w));
            }
        }

    cout << dp[0][n - 1];
}

// 1 1
// ans: 0

// 3 2 1 3
// ans: 3