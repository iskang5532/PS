// 2022-05-12
// 5766 할아버지는 유명해!
// https://www.acmicpc.net/problem/576
/*
    구현 (2,020KB, 9ms)
    시간 복잡도: ?
    풀이)
    - 입력된 선수 번호를 카운팅하여 배열 v에 저장.
    - v에서 가장 큰 값을 탐색. (= mx; 최고점인 선수)
    - v에서 두 번째로 큰 값을 탐색. (= prev; 2등인 선수의 점수)
    - v[i] == prev가 되는 i를 출력.
    etc.) 은근 어려웠음.
    - 첫 풀이는 맵을 사용함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003

int main()
{
    FAST_IO;

    int n, m; // 2 ≤ n, m ≤ 500
    while (cin >> n >> m && (n && m))
    {
        int v[MAX]{};
        for (int i = 0; i < n * m; i++)
        {
            int k; // 선수 번호 (1 ≤ k ≤ 10,000)
            cin >> k;
            v[k]++;
        }

        int mx = 0, prev = 0;
        for (const auto &k : v)
            mx = max(mx, k);
        for (const auto &k : v)
            if (k < mx)
                prev = max(prev, k);

        for (int i = 0; i < MAX; i++)
            if (v[i] == prev)
                cout << i << ' ';
        cout << endl;
    }
}

// 2 2
// 2 3 3 3
// 2 2
// 1 1 1 2
// 0 0
// ans:
// 2 2