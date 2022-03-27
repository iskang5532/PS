// 1417 국회의원 선거
// https://www.acmicpc.net/problem/1417
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 i번 후보의 표를 v[]에 저장. (v[i] = k일 때, i번 후보의 표는 k개.
    - 1번 후보의 표를 변수 k에 저장.
    - 매수해야 하는 사람의 수를 저장할 ans.
    - k+ ans보다 크면서 가장 차이가 많이 나는 후보 pos를 찾음. (= get_pos(), 2번 후보부터 n번 후보까지)
    이후 pos번쨰 후보의 표를 하나 깎은 후, ans++.
    만약 k + ans보다 큰 값이 없을 경우, ans 출력. (이떄의 get_pos() 반환값은 0. v[0]은 0이기 때문)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53

int n;      // 후보의 수 (1 ≤ n ≤ 50)
int v[MAX]; // v[i] = k일 때, i번 후보의 표는 k개

int get_pos(int k) // 1번 후보보다 표가 많은 사람 중에서 가장 많은 사람
{
    int ret = 0; // 기본값은 0번, 즉 0개의 표
    for (int i = 2; i <= n; i++) // 2번부터 탐색
        if (k <= v[i])
            k = v[i], ret = i;
    return ret;
}

int main()
{
    FAST_IO;

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int k = v[1]; // 1번 후보의 표 개수

    int ans = 0;
    while (true)
    {
        int pos = get_pos(k + ans);
        if (k + ans > v[pos]) // 1번 후보의 표가 가장 많아졌을 경우
            break;
        v[pos]--, ans++;
    }

    cout << ans;
}