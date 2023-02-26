// 2023-02-25
// 10813 공 바꾸기
// https://www.acmicpc.net/problem/10813
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - v[]에 값을 넣은 후, 입력된 a와 b에 맞춰 v[a]와 v[b]를 스왑한다.
    이후, 1부터 n까지 v의 값을 출력한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103 // max n

int v[MAX];

int main()
{
    FAST_IO;

    for (int i = 0; i < MAX; i++)
        v[i] = i;

    int n, m; // 공의 개수 n(1 ≤ n ≤ 100), 스왑 횟수 m(1 ≤ m ≤ 100)
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        swap(v[a], v[b]);
    }

    for (int i = 1; i <= n; i++)
        cout << v[i] << ' ';
}