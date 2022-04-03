// 2303 숫자 게임
// https://www.acmicpc.net/problem/2303
/*
    완전 탐색 (2,020KB, 0ms)
    시간 복잡도: O(5C3 * n)
    풀이)
    - 받은 수로 만들 수 있는 가장 큰 일의 자리 수를 구함. (= get_unit())
    - 일의 자리 수를 구하기 위해 순열을 사용.
    5개의 수 중 3개만을 이용하면 되므로 3개는 true, 나머지 2개는 false로 만든 후 permutation().
    이후 true인 값의 위치에 해당하는 값을 모두 더한 후 일의 자리 수를 구해주며, 구한 값 중 가장 큰 값을 저장 및 반환.
    반환된 값이 이전에 구한 수 mx보다 크거나 같다면 현재 사람의 번호와 수를 저장.
 */

#include <iostream>
#include <algorithm> // permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

int get_unit(int v[])
{
    int ret = 0;

    bool bit[5]{};
    fill(bit, bit + 3, true);
    do
    {
        int unit = 0;
        for (int i = 0; i < 5; i++)
            if (bit[i])
                unit += v[i];

        unit %= 10;
        ret = max(ret, unit);

    } while (prev_permutation(bit, bit + 5));

    return ret;
}

int main()
{
    FAST_IO;

    int n; // 사람의 수 (2 ≤ n ≤ 1,000)
    cin >> n;

    int ans, mx = 0; // 만들어진 수의 최댓값을 저장
    for (int people = 1; people <= n; people++)
    {
        int v[5]; // 1 ≤ k ≤ 10
        for (int i = 0; i < 5; i++)
            cin >> v[i];

        int unit = get_unit(v); // 만들 수 있는 가장 큰 일의 자리 수를 구함
        if (mx <= unit)
            ans = people, mx = unit;
    }

    cout << ans;
}
