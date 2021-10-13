/* 
 * 2615 오목
 * 구현, brute-force (2020KB, 0ms)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2615
 * etc.) 육목을 어떻게 막느냐가 관건이었던 문제였으며, 구현 또한 헷갈렸음.
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 19 // 판의 크기

const int dim_col[4] = {1, 1, 0, -1}; // |, \, ㅡ, /
const int dim_row[4] = {0, 1, 1, 1};

vector<vector<int>> arr(MAX + 2, vector<int>(MAX + 2)); // 판 외곽에 공간을 두어 런타임 에러를 방지

bool isValid(int col, int row, int dir) // 오목이 달성되었는지를 판단
{
    int next_col = col + dim_col[dir];
    int next_row = row + dim_row[dir];
    int cnt = 1; // 기준점으로부터 연속된 돌의 개수 (함수에 들어온 순간부터 돌이 하나 존재)

    for (int i = 0; i < 4; i++)                                        // 진행 방향의 나미자 4개의 돌을 순차적으로 확인
        if (arr[next_col][next_row] == arr[col][row])                  // 만약 다음 위치의 돌이 기준점의 돌과 같은 경우
            cnt++, next_col += dim_col[dir], next_row += dim_row[dir]; // 연속된 돌의 개수를 늘리며 다음 위치를 업데이트
        else
            break;

    if (cnt == 5 && (arr[next_col][next_row] != arr[col][row])) // 5개의 연속이며 다음 돌이 같은 돌이 아닌 경우 (= 6개 이상을 방지)
        return true;
    return false;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    for (int col = 1; col <= MAX; col++)
        for (int row = 1; row <= MAX; row++)
            cin >> arr[col][row];

    for (int row = 1; row <= MAX; row++) // 왼쪽 돌이 우선시되기 때문에 row값 먼저
        for (int col = 1; col <= MAX; col++)
            if (arr[col][row]) // 돌이 존재하는 경우
                for (int dir = 0; dir < 4; dir++)
                {
                    int prev_col = col - dim_col[dir]; // 진행 방향의 반대편 위치
                    int prev_row = row - dim_row[dir];
                    if (arr[prev_col][prev_row] == arr[col][row]) // 이전 돌이 현재 돌과 같을 경우, 이전에 탐색을 진행했기 때문에 종료
                        continue;
                    if (isValid(col, row, dir)) // 현재 위치에서 진행 방향으로 오목인가?
                    {
                        cout << arr[col][row] << endl;
                        cout << col << " " << row << endl;
                        return 0;
                    }
                }
    cout << '0';
}