/*
 * 1799 비숍
 * 백트래킹 (2020KB, 32ms)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1799
 * etc.)
 * - 9663 N-queen과 같이 모든 영역에 대해 조사할 경우 TLE 발생.
 * 따라서 두 영역으로 나눈 후 조사를 수행. (비숍은 대각선으로밖에 이동할 수 없다는 특성을 이용)
 * 체스판에 나눠진 흰색 부분과 검은색 부분을 따로 탐색하여 시간 복잡도를 줄임.
 * - dfs를 시키기 위해 입력을 1차원으로 받았으며, col값과 row값을을 따로 만들어 2차원으로 활용.
 * - 이 풀이는 흰색과 검은색의 입력이 합쳐진 arr를 그대로 사용하며 위치를 +2씩 시켜줌으로써 탐색할 구간을 맞춰줌. (흰색 or 검은색 칸만 조사)
 * 이때, n == even일 때 구간 탐색이 제대로 되지 않음. 따라서 예외 처리를 해줘야 함.
 * 참고: https://blog.naver.com/jinhan814/222102000087 (시간 복잡도에 대해)
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10 // 체스판의 최대 크기

int n; // 체스판의 크기 (1 <= 10)
vector<int> arr;
bool visited_l[MAX * 2 + 1], visited_r[MAX * 2 + 1];
int idx; // dfs시에 구할 수 있는 비숍의 개수

bool isValid(const int col, const int row)
{
    if (visited_l[col + row] || visited_r[n - 1 + col - row]) // 좌하단 혹은 우하단으로 중복을 탐색
        return false;
    return true;
}

void dfs(int _len, int cnt = 0)
{
    if (_len >= n * n) // 조사 범위를 벗어난 경우
        return;

    for (int len = _len; len < n * n; len += 2)
    {
        int col = len / n;
        int row = len % n;
        if (!(n & 1)) // if n == even
            if (col && row == 0) // 첫 번째 줄이 아니며 0번 칸인 경우, 앞으로 한 칸
                len++, row++;
            else if (col && row == 1) // 첫 번째 줄이 아니며 1번 칸인 경우, 뒤로 한 칸
                len--, row--;

        if (arr[len] && isValid(col, row)) // 놓을 수 있는 위치인 경우
        {
            visited_l[col + row] = true, visited_r[n - 1 + col - row] = true;
            idx = max(idx, cnt + 1);
            dfs(len + 2, cnt + 1);
            visited_l[col + row] = false, visited_r[n - 1 + col - row] = false;
        }
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n;
    for (int i = 0; i < n * n; i++)
    {
        int k;
        cin >> k;
        arr.push_back(k);
    }

    dfs(0); // 첫 번째 영역 [0, 0]부터 +2씩
    int temp = idx;
    idx = 0;
    dfs(1); // 두 번째 영역 [0, 1]부터 +2씩

    cout << temp + idx;
}

// 9% n == even, 입력이 굉장히 많음
// 10
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1
// idx: 18