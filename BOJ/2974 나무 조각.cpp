// 2974 나무 조각
// https://www.acmicpc.net/problem/2974
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 수의 개수가 적으므로 완전 탐색을 이용.
    - 입력된 수의 순서가 스왑이 일어나지 않을 때까지 반복.
    etc.) 정렬?
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 5

int main()
{
    FAST_IO;

    int v[MAX];
    for (int i = 0; i < MAX; i++)
        cin >> v[i];

    while (true)
    {
        bool swapped = false; // 스왑 됐는가?

        for (int i = 0; i < MAX - 1; i++)
            if (v[i] > v[i + 1])
            {
                swap(v[i], v[i + 1]), swapped = true;

                for (int i = 0; i < MAX; i++)
                    cout << v[i] << ' ';
                cout << endl;
            }

        if (!swapped)
            break;
    }
}