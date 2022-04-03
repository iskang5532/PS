// 1037 약수
// https://www.acmicpc.net/problem/1037
/*
    정렬. 수학 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 정답 N의 약수(본인을 제외) m개가 입력으로 들어온다.
    가장 작은 수와 가장 큰 수를 곱하게 된다면 N을 구할 수 있다.
    이를 위해 입력된 약수를 정렬시킨 후, [0]값과 [m-1]값을 곱한다.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53 // max n

int main()
{
    FAST_IO;

    int m; // 1 ≤ m ≤ 50
    cin >> m;
    int v[MAX];
    for (int i = 0; i < m; i++)
        cin >> v[i];

    sort(v, v + m);

    cout << v[0] * v[m - 1];
}