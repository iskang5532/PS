// 1475 방 번호
// https://www.acmicpc.net/problem/1475
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수의 개수를 저장할 배열 v. (v[i] = k일 때, 수 i의 개수는 k)
    - 입력된 값을 문자열로 받은 후, 문자 하나를 v에 저장.
    - 6번과 9번은 서로 보완할 수 있음. 그러므로, 하나의 값에 합쳐줌.
    이때 주의할 점은, 2로 나눠주므로 소수점이 생길 수 있다. 만약 1.2일 경우 2세트가 필요하므로, 값을 올림한다.
    - v[0]부터 v[9]까지의 값을 탐색한 후, 가장 큰 값을 출력해준다. (세트마다 하나의 값이 존재할 수 있으므로, 가장 큰 값은 세트의 필요한 개수가 됨)
 */

#include <iostream>
#include <cmath> // ceil

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 11

int main()
{
    FAST_IO;

    string n; // 방 번호 (1 ≤ n ≤ 1,000,000)
    cin >> n;

    int v[MAX]; // v[i] = k일 때, 수 i의 개수는 k
    fill(v, v + MAX, 0);
    for (const char &c : n)
        v[c - '0']++;

    v[6] = (v[6] + v[9] + 1) / 2, v[9] = 0; // 6번과 9번을 합친 후, 올림 수행
    // v[6] = ceil((1.0 * v[6] + v[9]) / 2)

    int ans = 0;
    for (int i = 0; i <= 9; i++)
        ans = max(ans, v[i]);

    cout << ans;
}