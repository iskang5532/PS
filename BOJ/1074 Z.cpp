// 1074 Z
// https://www.acmicpc.net/problem/1074
/*
    sol.1) 분할 정복(반복문) (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    etc.)
    - 기준점에서 len만큼 떨어진 구역을 탐색. (기준점은 (0,0), (len,0), (0,len), (len,len))
    만약 범위 안에 (c, r)이 없을 경우, 해당 범위의 탐색을 종료. (= 시간 절약)
    - 좌표에 대한 값은, 영역이 분할되는 횟수(= len) 및 어느 사분면에 속하는지(= *i)를 이용하여 구해줌. (= k + (len^2 * i))
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define pow(a) (a) * (a)

const int dx[4] = {0, 1, 0, 1}; // Z
const int dy[4] = {0, 0, 1, 1};

int r, c; // 1 ≤ r, c < 2N

void quadtree(int y, int x, int len, int k)
{
    if (y == r && c == x)
    {
        cout << k;
        exit(0);
    }
    for (int i = 0; i < 4; i++)
    {
        int ny = y + (dy[i] * len);
        int nx = x + (dx[i] * len);
        int nk = k + (pow(len) * i);
        if (ny <= r && r < ny + len && nx <= c && c < nx + len) // 범위 안에 원하는 위치가 존재할 시 탐색
            quadtree(ny, nx, len >> 1, nk);
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ N ≤ 15
    cin >> n;
    cin >> r >> c;

    quadtree(0, 0, 1 << n, 0);
}

/*
    sol.2) 분할 정복 (2,020KB, 0ms)
    시간 복잡도: ?
    etc.) 정석적인 풀이 느낌
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define pow(a) (a) * (a)

int r, c; // 1 ≤ r, c < 2N

void quadtree(int y, int x, int len, int k)
{
    if (y == r && c == x)
    {
        cout << k;
        exit(0);
    }

    if (y <= r && r < y + len && x <= c && c < x + len)
    {
        int n_len = len >> 1;
        quadtree(y, x, n_len, k + pow(n_len) * 0);
        quadtree(y, x + n_len, n_len, k + pow(n_len) * 1);
        quadtree(y + n_len, x, n_len, k + pow(n_len) * 2);
        quadtree(y + n_len, x + n_len, n_len, k + pow(n_len) * 3);
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ N ≤ 15
    cin >> n;
    cin >> r >> c;

    quadtree(0, 0, 1 << n, 0);
}