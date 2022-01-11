// 15652 N과 M (4)
// 중복조합(nHm) 구하기. (n개의 수에서 중복을 허용해서 m개의 수를 고르는 모든 경우)
// https://www.acmicpc.net/problem/15652
/*
    백트래킹 (2,020KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 재귀를 통해 n개의 수 중 m개를 골라줌.
    중복되는 수가 존재해도 되지만, 비내림차순을 만족해야 한다.
    즉, 수를 고를 때 이전에 고른 수부터 선택할 수 있게 한다.
    - 고른 수는 idx에 저장. (idx[i] = k일 시, i번째 고른 수는 k)
    - m개의 수를 골랐을 경우, 0부터 m-1까지 idx를 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 8 + 1

int n, m; // 1 ≤ M ≤ N ≤ 8
int v[MAX], idx[MAX];

void dfs(int k, int len)
{
    if (len == m)
    {
        for (int i = 0; i < m; i++)
            cout << idx[i] << ' ';
        cout << endl;
        return;
    }

    for (int i = k; i <= n; i++)
    {
        idx[len] = i;
        dfs(i, len + 1);
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    dfs(1, 0);
}