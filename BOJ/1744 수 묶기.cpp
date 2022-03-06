// 1744 수 묶기
// https://www.acmicpc.net/problem/1744
/*
    sol.1) 그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수는 위치에 상관없이 묶을 수 있다. 그러므로, 양수와 음수로 나눠 값을 구해준다.  (0은 음수쪽에 넣어 홀수개일 때 유용하게 사용해준다.)
    1. 값을 입력받으며, 값이 양수일 경우 l, 0 혹은 음수일 경우 r에 넣는다.
    l과 r은 우선순위 큐이며, l은 내림차순 정렬, r은 오름차순 정렬이다.
    2. 큐에 존재하는 값으로 만들 수 있는 최댓값을 만든다.
     2-1. l일 경우
     - 둘 중 하나의 값이 1일 경우, 두 값을 곱하는 것보다 더해주는 것이 더 높은 값을 얻을 수 있다.
     - 그 외는 두 수를 서로 곱해준다.
     2-2. r일 경우
     - 음수 혹은 0이므로, 두 수를 곱하는 것이 더 높은 값을 얻을 수 있다.
    - 만약 큐에 존재하는 값이 하나일 경우, 그냥 더해준다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53

template <typename T>
int get_ans(priority_queue<int, vector<int>, T> &pq)
{
    int ret = 0;
    int a, b;
    while (pq.size() >= 2)
    {
        a = pq.top(), pq.pop();
        b = pq.top(), pq.pop();

        if (a == 1 || b == 1) // 둘 중 하나의 값이 1일 경우, 두 값을 곱하기보다 더해주는 것이 더 높음
            ret += a + b;
        else
            ret += a * b;
    }
    if (pq.size())
        ret += pq.top();

    return ret;
}

int main()
{
    FAST_IO;

    int n; // 수열의 크기 (1 ≤ n ≤ 50)
    cin >> n;
    priority_queue<int> l; // -1,000 ≤ vi ≤ 1,000
    priority_queue<int, vector<int>, greater<int>> r;
    for (int i = 0, x; i < n; i++)
        cin >> x, x >= 1 ? l.push(x) : r.push(x);

    int ans = get_ans(l) + get_ans(r);
    cout << ans;
}

/*
    sol.2) DP (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - DP[i] = k일 때, v[i]까지의 값을 이용해 만들 수 있는 최댓값은 k.
    - 탐색중인 i번쨰 수를 어떻게 이용하면 더 높은 값을 얻을 수 있는지를 판단.
    곱할 경우, v[i-1] 값과 곱해줘야 하므로 dp[i-2]번째 값을 이용해줘야 한다.
    더할 경우, v[i]를 이전까지의 최댓값인 dp[i-1]에 더해주면 된다.
    위 두 가지 방법을 이용해 dp[i]의 최댓값을 구한다.
    etc.) 2579 계단 오르기(https://boj.kr/2579) 문제와 비슷한듯
    참고)
    - DP 풀이 방법: https://blog.naver.com/jinhan814/222609762108
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    int dp[MAX]; // dp[i] = k일 때, v[i]까지의 값을 이용해 만들 수 있는 최댓값은 k
    dp[0] = v[0];
    dp[1] = max(dp[0] + v[1], v[0] * v[1]);
    for (int i = 2; i < n; i++)
        dp[i] = max(dp[i - 1] + v[i], dp[i - 2] + (v[i - 1] * v[i])); // i번쨰 값을 그대로 더해줄 것인가? 혹은 i-1번째 값과 곱해줄 것인가?

    cout << dp[n - 1];
}

// 5 -5 -3 -2 0 0
// ans: 15

// 4%
// 2 -1 -1
// ans: 1

// 26%
// 3 2 1 -1
// 2

// 31%
// 4 1 1 1 1
// ans: 4

// 59%
// 5 1 1 1 1 1
// ans: 5
