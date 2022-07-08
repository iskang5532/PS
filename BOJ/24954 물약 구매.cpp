// 2022-06-17
// 24954 물약 구매
// https://www.acmicpc.net/problem/24954
/*
    sol.1) DFS (2,020KB, 528ms)
    시간 복잡도: O(n!)?
    풀이)
    - n의 개수가 10이므로, dfs를 이용하여 최적화된 구매 비용을 구함.
    - i번째로 구매할 물약의 번호를 order에 저장.
    - order에 저장된 순으로 물약을 구매.
     - 물약을 구매할 때 사용한 가격을 저장할 sum.
     - 물약의 가격을 저장할 price. (따로 변수를 만든 이유는, 구매 순서에 따라 물약의 가격이 달라지므로 dfs 수행마다 따로 생성)
     - 현재 물약의 가격 price[cur]를 sum에 저장. 만약 price[cur] <= 0일 경우, 1을 저장.
     - 현재 구매할 물약의 번호가 cur일 때, info[cur]의 값을 이용하여 다른 물약의 가격을 낮춤.
     - ans에 sum과 비교하여 더 작은 값을 저장.
    etc.)
    - c를 n개가 아닌 4개만 받아놓고 TLE난다고 난리쳤던 문제
    - 물약은 여러번이 아닌 한번만 구매 가능한듯.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x7fffffff
#define MAX 11 // max n

int n;                 // 물약의 개수 (2 ≤ n ≤ 10)
vector<int> c(MAX);    // 물약의 가격 (1 ≤ c ≤ 1k)
vector<pii> info[MAX]; // info[i] = {a, d}일 때, i번 물약을 구매할 시 a번 가격 -= d
bool visited[MAX];
int order[MAX];
int ans = INF;

void dfs(int dep)
{
    if (dep == n)
    {
        int sum = 0;

        auto price = c; // 포션 가격
        for (int i = 0; i < n; i++)
        {
            int cur = order[i];
            sum += max(1, price[cur]);
            for (const auto &[a, d] : info[cur])
                price[a] -= d;
        }

        ans = min(ans, sum);
        return;
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            visited[i] = true, order[dep] = i;
            dfs(dep + 1);
            visited[i] = false;
        }
}

int main()
{
    FAST_IO;

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> c[i];
    for (int i = 0; i < n; i++)
    {
        int p; // 할인 정보 개수 (0 ≤ p ≤ n-1)
        cin >> p;
        for (int j = 0; j < p; j++)
        {
            int a, d;
            cin >> a >> d; // 물약 번호 a, 할인되는 가격 d
            info[i].push_back({a - 1, d});
        }
    }

    dfs(0);

    cout << ans;
}

/*
    sol.2) next_permutation (2,020KB, 436ms)
    시간 복잡도: O(n!)?
    풀이)
    - order에 i번째로 구매할 물약의 번호를 저장한 후, order의 순서대로 물약을 구매.
    - next_permutation()를 이용하여 order를 섞어줌.
 */

#include <iostream>
#include <vector>
#include <algorithm> // next_permutation
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x7fffffff
#define MAX 11 // max n

int main()
{
    FAST_IO;

    int n; // 물약의 개수 (2 ≤ n ≤ 10)
    cin >> n;
    vector<int> c(MAX); // 물약의 가격 (1 ≤ c ≤ 1k)
    for (int i = 0; i < n; i++)
        cin >> c[i];
    vector<pii> info[MAX]; // info[i] = {a, d}일 때, i번 물약을 구매할 시 a번 가격 -= d
    for (int i = 0; i < n; i++)
    {
        int p; // 할인 정보 개수 (0 ≤ p ≤ n-1)
        cin >> p;
        for (int j = 0; j < p; j++)
        {
            int a, d;
            cin >> a >> d; // 물약 번호 a, 할인되는 가격 d
            info[i].push_back({a - 1, d});
        }
    }

    vector<int> order(n); // order[i] = k일 경우, i번째로 구매할 물약의 번호는 k
    iota(order.begin(), order.end(), 0);

    int ans = INF;
    do
    {
        int sum = 0;
        auto price = c; // 포션 가격
        for (auto &cur : order)
        {
            sum += max(1, price[cur]);
            for (const auto &[a, d] : info[cur])
                price[a] -= d;
        }

        ans = min(ans, sum);
    } while (next_permutation(order.begin(), order.end()));

    cout << ans;
}