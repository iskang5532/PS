// 2023-03-17
// 2980 도로와 신호등
// https://www.acmicpc.net/problem/2980
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 시간이 지남에 따라 위치를 변경하며, 이동할 다음 위치의 신호가 빨간색이 아니면 이동하며, 이후 신호의 정보를 갱신.
    - 입력된 신호의 색상에 따른 지속시간을 info[]에 저장.
    - 해당 위치에 신호등이 존재하는지를 light[]에 저장.
    - 각 신호의 색상에 따른 시간을 cnt[][]에 저장.
    - 이동할 다음 위치의 신호가 초록 혹은 -1(초깃값)일 경우, 이동.
    이동 후 light[]를 이용하여 cnt의 값을 변경.
    신호가 초록이면서 cnt[pos][GREEN]의 값이 info에 저장된 지속 시간과 일치할 경우, 값을 0으로 바꿔주며, 상태를 RED로 바꿈.
    신호가 빨강이면서 cnt[pos][RED]의 값이 info에 저장된 지속 시간과 일치할 경우, 값을 0으로 바꿔주며, 상태를 GREEN으로 바꿈.
    etc.) 무지성 구현
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define red first
#define green second
#define RED 0
#define GREEN 1
#define MAX 1'003 // max l

pii info[MAX]; // info[pos] = {r, g}일 경우, 위치 pos에 있는 신호등의 빨간색 시간은 r, 초록색 시간은 g

int main()
{
    FAST_IO;

    int n, l; // 신호등의 개수 n(1 ≤ N ≤ 100), 도로의 길이(1 ≤ L ≤ 1000)
    cin >> n >> l;
    int light[MAX]; // light[pos] = true일 경우, 해당 위치에 신호등이 존재
    fill(light, light + MAX, -1);
    for (int i = 0; i < n; i++)
    {
        int d, r, g; // 위치 d, 빨간색 시간 r, 초록색 시간 g
        cin >> d >> r >> g;

        info[d] = {r, g}, light[d] = RED;
    }

    int ans = 0;
    int cnt[MAX][2]{}; // cnt[pos][GREEN] = t일 경우, 위치 pos에 있는 신호등은 GREEN 상태로 t초 지남
    for (int pos = 1; pos < l; ans++)
    {
        if (light[pos] != RED)
            pos++;

        for (int i = 1; i < MAX; i++)
            if (light[i] == GREEN && ++cnt[i][GREEN] == info[i].green) // 신호의 시간이 다 되었을 경우
                cnt[i][GREEN] = 0, light[i] = RED;
            else if (light[i] == RED && ++cnt[i][RED] == info[i].red)
                cnt[i][RED] = 0, light[i] = GREEN;
    }

    cout << ans;
}