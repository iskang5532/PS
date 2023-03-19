// 2023-03-18
// 11504 돌려 돌려 돌림판
// https://www.acmicpc.net/problem/11504
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - x와 y의 입력이 자릿수로 입력되므로, m개의 입력에 맞춰 수로 만들어주는 함수를 구현하여 사용.
    - 돌림판의 값을 board[]에 저장.
    - 지점 st에서부터 m개의 값을 이용하여 z를 만듦.
    st + i가 돌림판의 크기 n을 넘을 수 있으므로, 나머지 연산을 사용.
    etc.) 재밌는 문제
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 103 // max n

int board[MAX];

int get_z(int st, int n, int m) // 돌림판에서 st의 위치에서 m개의 수를 이어 붙인 값을 반환
{
    string ret;
    for (int i = st; i < st + m; i++)
        ret += board[i % n] + '0';

    return stoi(ret);
}

int in_num(int m) // m개의 수를 받아서 만든 값을 반환
{
    string ret;
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        ret += k + '0';
    }

    return stoi(ret);
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m; // 등분 개수 n(1 ≤ n ≤ 100), 수의 길이 m(1 ≤ m ≤ 9, m ≤ n)
        cin >> n >> m;
        int x = in_num(m), y = in_num(m);
        for (int i = 0; i < n; i++)
            cin >> board[i];

        int ans = 0;
        for (int st = 0; st < n; st++)
        {
            int z = get_z(st, n, m);
            if (x <= z && z <= y)
                ans++;
        }

        cout << ans << endl;
    }
}