// 2023-03-03
// 27660 Queue skipping (Hard) 
// https://www.acmicpc.net/problem/27660
/*
    구현 (2,284KB, 524ms)
    시간 복잡도: ?
    풀이)
    - v[]에 해당 값의 우선순위를 저장한다. (값이 클수록 뒤에 존재)
    - 입력된 값 중 마지막에 들어온 값이 가장 앞으로 이동하게 된다. 즉, v에 저장하는 값은 입력 횟수에 맞춰 더 작은 값을 넣는다.
    - v에 저장된 값 중 가장 큰 값을 가진 i를 찾은 후, i를 출력한다.
    - e개의 입력 중 한 번도 입력으로 들어오지 않은 값은 들어온 값들에 비해 뒤에 머물 것이다.
    이를 위해, v의 초깃값은 1부터 n까지 오름차순으로 정하되, 추후 v에 저장할 값보다는 크도록 초기화한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
#define MAX 100'003

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, e;
        cin >> n >> e;

        int v[MAX]; // 값의 우선순위 (값이 클수록 뒤에 존재)
        for (int i = 1; i <= n; i++)
            v[i] = MAX + MAX + i;

        for (int i = 0; i < e; i++)
        {
            int k;
            cin >> k;
            v[k] = MAX - i;
        }

        int ans = 0;
        int mx = 0;
        for (int i = 1; i <= n; i++)
            if (mx < v[i])
                ans = i, mx = v[i];
        cout << ans << endl;
    }
}