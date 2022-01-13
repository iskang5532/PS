// 1003 피보나치 함수
// https://www.acmicpc.net/problem/1003
/*
    DP (2,020KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 피보나치 수는 i-1, i-2의 수를 가져와 i번째 수를 구한다.
    그러므로, i-1, i-2를 만들 때 사용한 [0]과 [1]을 저장한다면, i번쨰에 사용한 [0], [1]의 개수를 파악할 수 있다.
    1) 2차원 배열 Fibo를 선언하여 수 i를 만들 때 사용한 [0], [1]의 개수를 저장한다.
    2) Fibo의 초깃값을 설정해준다. (0을 만들 때는 [0]이 1개, 1을 만들 때는 [1]이 1개 필요하므로 저장해준다.)
    3) n이 될 수 있는 최댓값 40까지 Fibo를 구해준다.
    4) 입력된 값 k에 맞는 [0], [1]의 개수인 [k][0], [k][1]을 출력해준다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 40 + 1

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    int Fibo[MAX][2]; // Fibo[i][1] = k일 때, i를 만들 때 필요한 [1]의 개수는 k개
    fill(&Fibo[0][0], &Fibo[0][0] + sizeof(Fibo) / sizeof(Fibo[0][0]), 0);

    Fibo[0][0] = 1, Fibo[1][1] = 1;
    for (int i = 2; i < MAX; i++)
        Fibo[i][0] = Fibo[i - 1][0] + Fibo[i - 2][0],
        Fibo[i][1] = Fibo[i - 1][1] + Fibo[i - 2][1]; // 이전 값(-1, -2)들의 [0], [1]의 개수를 가져옴

    while (tc--)
    {
        int k;
        cin >> k;
        cout << Fibo[k][0] << ' ' << Fibo[k][1] << endl;
    }
}