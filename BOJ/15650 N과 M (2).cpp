// 15650 N과 M (2)
// https://www.acmicpc.net/problem/15650
/*
    sol.1) 백트래킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 재귀를 통해 n개의 수 중 m개를 골라줌.
    단, 중복되는 수가 존재하면 안 되므로 이전에 선택한 수가 포함되지 않도록 한다.
    즉, 선택할 수를 탐색할 때 이전에 고른 수의 다음 수부터 선택할 수 있게 한다.
    - 고른 수는 idx에 저장. (idx[i] = k일 시, i번째 고른 수는 k)
    - m개의 수를 골랐을 경우, 0부터 m-1까지 idx를 출력.
 */

#include <iostream>
#include <numeric> // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 8 + 1

int n, m;             // 1 ≤ M ≤ N ≤ 8
int v[MAX], idx[MAX]; // idx[i] = k일 때, i번째로 고른 수는 k

void dfs(int pos, int len)
{
    if (len == m)
    {
        for (int i = 0; i < m; i++)
            cout << idx[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = pos; i < n; i++)
    {
        idx[len] = v[i];
        dfs(i + 1, len + 1);
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    iota(v, v + n, 1);

    dfs(0, 0);
}
/*
    sol.2) 완전 탐색 (2,028KB, 0ms)
    시간 복잡도: ?
    풀이)
    nCm 구하기. (n개의 수에서 중복 없이 m개의 수를 골라서 만들 수 있는 조합)
    1) n개의 비트를 이용하며, m개의 비트를 true로 만든 후 i번째 비트가 true일 시 v[i]의 값을 str에 저장함.
    2) str을 구했다면, ans에 저장함.
    3) next_permutation을 이용하여 선택할 m개의 수를 바꾸며, 1번 과정 반복
    4) ans에 저장된 값은 정렬된 상태가 아니므로, 오름차순 정렬 후 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 8 + 1;

int main()
{
    FAST_IO;

    int n, m; // 1 ≤ M ≤ N ≤ 8
    cin >> n >> m;

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    vector<bool> bits(n, false);
    fill(bits.end() - m, bits.end(), true);

    vector<string> ans;
    do
    {
        string str;
        for (int i = 0; i < n; i++)
            if (bits[i])
                str.push_back(v[i] + '0');
        ans.push_back(str);
    } while (next_permutation(bits.begin(), bits.end()));

    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++, cout << endl)
        for (const auto &c : ans[i])
            cout << c << ' ';
}