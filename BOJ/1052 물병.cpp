// 2022-08-25
// 1052 물병
// https://www.acmicpc.net/problem/1052
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 처음에 물병에는 1리터의 물이 들어 있으며, 옮길 때는 서로 같은 양의 물이 들어있는 물병끼리 가능하다.
    즉, 임의의 물병에는 1, 2, 4, 8, ...과 같은 등비수열만큼 존재한다.
    - 물병을 옮겨닮는 압축을 수행한 결과를 저장할 v[].
    - 입력된 물병의 수를 이용하여 최대한 물병을 옮겨 닮는다.
    방법은, n보다 작으면서 가장 큰 2^n을 구한다.
    - 물병은 최대 k개까지 허용한다.
    만약 v에 존재하는 원소의 개수가 k 이하일 경우 추가적으로 구매할 물병은 0이다.
    만약 v에 존재하는 원소의 개수가 k 초과일 경우, k개를 맞춰야 한다.
     - 선택된 k개 중 가장 작은 값, 즉 v[k-1]과 v[k-1]보다 작은 나머지 값을 합친다면 k개를 맞출 수 있다.
 */

#include <iostream>
#include <vector>
#include <numeric> // accumulate

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10'000'003 // max n

int main()
{
    FAST_IO;

    int n, k; // 물병의 개수 n(1 ≤ n ≤ 10,000,000), 제한 k(1 ≤ k ≤ 1,000)
    cin >> n >> k;

    vector<int> v; // 압축된 물병을 저장. {8, 4, 1}일 경우 13개의 물병을 3개로 압축
    while (n)
    {
        int pos = 1;
        while (1 << pos <= n) // n보다 작으면서 가장 큰 값을 구함
            pos++;

        v.push_back(1 << (pos - 1)), n -= 1 << (pos - 1);
    }

    if (v.size() <= k)
        cout << 0;
    else
    {
        int mx = v[k - 1];
        int sum = accumulate(v.begin() + k, v.end(), 0);

        cout << mx - sum;
    }
}