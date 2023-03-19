// 2023-03-15
// 9037 The candy war
// https://www.acmicpc.net/problem/9037
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 홀수개의 사탕을 가진 아이에게 하나의 사탕을 주는 함수 get_candy().
    - 모든 아이가 같은 개수의 사탕을 가지는지 확인하는 함수 is_done().
    - 옆 아이에게 절반의 사탕을 주는 함수 moved().
    - 예제와 같이 첫 입력과 홀수를 짝수로 만드는 함수만으로 답이 나올 수 있음에 주의.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 13 // max n

int n; // 인원 (1 ≤ n ≤ 10)
int v[MAX];

bool is_done() // 모든 아이가 같은 개수의 사탕을 가지는가
{
    for (int i = 0; i < n - 1; i++)
        if (v[i] != v[i + 1])
            return false;

    return true;
}

void get_candy() // 홀수개의 사탕을 가지고 있는 아이에게 하나의 사탕을 줌
{
    for (int i = 0; i < n; i++)
        if (v[i] & 1)
            v[i]++;
}

void moved()
{
    int tmp[MAX]{}; // i에게 줄 1/2개의 사탕
    tmp[0] = v[n - 1] / 2, v[n - 1] -= tmp[0];
    for (int i = 1; i < n; i++)
        tmp[i] = v[i - 1] / 2, v[i - 1] -= tmp[i];

    for (int i = 0; i < n; i++)
        v[i] += tmp[i];
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> v[i];

        get_candy();

        int ans = 0;
        while (!is_done() && n != 1)
        {
            ans++;

            moved();
            get_candy();

            if (is_done())
                break;
        }

        cout << ans << endl;
    }
}