// 15649 N과 M (1)
// 순열(nPm) 구하기. (n개의 수에서 중복 없이 m개의 수를 뽑아서 만들 수 있는 순열)
// https://www.acmicpc.net/problem/15649
/*
    sol.1) 백트래킹 (2,020KB, 20ms)
    시간 복잡도: ?
    풀이)
    - dfs를 이용하여 1부터 n까지의 수 중 m개를 선택.
    값의 선택 여부는 visited에 저장하며, 선택한 값은 v에 저장. (v에 값을 저장할 때 i번째에 저장하지 않도록 주의)
    1) 1부터 n까지 한 개의 값을 선택.
    만약 i가 선택된 적이 없을 경우, visited 및 v에 저장.
    이후 깊이(= 선택한 수의 개수) + 1 시킨 후 dfs.
    2) 이후 선택한 값의 개수와 m개가 같을 때까지 1번을 반복.
    만약 같게 되었을 경우, v에 저장된 값들을 출력.
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222604405729
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 8 + 1

int n, m;   // 1 ≤ M ≤ N ≤ 8
int v[MAX]; // v[i] = k일 때, i번째로 고른 수는 k
bool visited[MAX];

void dfs(int dep)
{
    if (dep == m)
    {
        for (int i = 0; i < dep; i++)
            cout << v[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            visited[i] = true, v[dep] = i + 1;
            dfs(dep + 1);
            visited[i] = false;
        }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    fill(visited, visited + n, false);

    dfs(0);
}

/*
    sol.2) 완전 탐색 (5,228KB, 28ms)
    시간 복잡도: ?
    풀이)
    1) 벡터 v에 1부터 n까지의 수를 저장하며, bits에는 m만큼의 수를 사용할 수 있도록 m개의 1을 저장. (그 외의 값은 0)
    2) next_permutation을 이용하여 bits를 돌려줌.
    3) bits[i]가 true일 때, v[i]의 값을 가져와 str에 저장.
    4) 저장된 str를 next_permutation을 돌려 다른 순서의 값들도 구해줌. ([1, 4], [4, 1])
    구한 값은 res에 저장.
    5) 2번 과정부터 수행하며, 완료되었을 시 res를 정렬한 후, res안에 존재하는 값들을 출력 양식에 맞춰 출력.
    etc.)
    - [1, 4], [4, 1] 값을 구하는 과정은 입력된 수열에 중복된 값이 없다는 점과 next_permutation의 특징으로 인해 가능한듯
    참고)
    - 이론: https://blog.naver.com/jinhan814/222568774582
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

void solution(int n, int m)
{
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    vector<bool> bits(n, false);
    fill(bits.end() - m, bits.end(), true);

    vector<string> res;
    do
    {
        string str;
        for (int i = 0; i < n; i++)
            if (bits[i])
                str.push_back(v[i] + '0');

        do // 순서 섞기
            res.push_back(str);
        while (next_permutation(str.begin(), str.end()));
    } while (next_permutation(bits.begin(), bits.end()));

    sort(res.begin(), res.end());

    for (const auto &str : res)
    {
        for (const auto &c : str)
            cout << c << ' ';
        cout << endl;
    }
}

int main()
{
    FAST_IO;

    int n, m; // 1 ≤ M ≤ N ≤ 8
    cin >> n >> m;

    solution(n, m);
}