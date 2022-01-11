// 15651 N과 M (3)
// 중복순열(nΠm) 구하기. (n개의 수에서 중복을 허용해서 m개의 수를 고른 뒤 나열하는 모든 경우)
// https://www.acmicpc.net/problem/15651
/*
    백트래킹 (2,020KB, 388ms)
    시간 복잡도: ?
    풀이)
    - 재귀를 이용해 n개중 m개를 뽑는 경우를 모두 탐색.
    - 수는 중복이 가능하므로, 재귀 시마다 선택할 수는 1부터 탐색.
    - 선택한 수는 idx에 저장.
    - 선택한 수의 개수가 m개가 되었을 경우, idx에 저장된 수를 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 7 + 1

int n, m; // 1 ≤ M ≤ N ≤ 7
int idx[MAX];

void dfs(int len)
{
    if (len == m)
    {
        for (int i = 0; i < m; i++)
            cout << idx[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        idx[len] = i;
        dfs(len + 1);
    }
}
int main()
{
    FAST_IO;

    cin >> n >> m;

    dfs(0);
}

/*
    완전 탐색 (2,020KB, 396ms)
    시간 복잡도: ?
    풀이)
    - 경우의 수 p를 구한 후, 0:p-1까지의 값 i을 이용해 r개를 선택함.
    i를 n진법으로 만들 시, k번째에 값을 모두 선택되는 순간 k+1번째에 값을 선택하는 형식으로 바뀜.
    - 배열 val를 선언하여 각 for문마다 k번째에 어떠한 값이 선택되었는지 저장 후 출력.
    etc.) 헷갈리는 문제.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222579884777
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 7 + 1

int Pow(int n, int r)
{
    int ret = 1;
    for (int i = 0; i < r; i++)
        ret *= n;

    return ret;
}

void solution(int n, int r)
{
    int p = Pow(n, r);          // n^r (경우의 수)
    for (int i = 0; i < p; i++) // n진법에 사용할 값
    {
        int val[MAX]; // val[k] = 3일 경우, k번째에 선택한 값은 3
        int curr = i;
        for (int pos = 0; pos < r; pos++) // 값을 n진법으로 바꿔줌
        {
            val[pos] = curr % n + 1;
            curr /= n;
        }
        for (int pos = r - 1; pos >= 0; pos--) // 값이 앞에서부터 저장됨. (사전 순이 아니며, 이는 뒤에서부터 출력 시 해결)
            cout << val[pos] << ' ';
        cout << endl;
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 범위 n, 개수 m (1 ≤ m ≤ n ≤ 7)
    cin >> n >> m;

    solution(n, m);
}