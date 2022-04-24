// 2022-04-20
// 2503 숫자 야구
// https://www.acmicpc.net/problem/2503
/*
    구현, 완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    etc.)
    참고)
 */

#include <iostream>
#include <vector>
#include <algorithm> // permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    string num; // 수
    int st, b;  // 스트라이크, 볼
};

int main()
{
    FAST_IO;

    int n; // 질문 (1 ≤ n ≤ 100)
    cin >> n;
    vector<P> v(n);
    for (auto &[num, st, b] : v)
        cin >> num >> st >> b;

    int ans = 0;
    vector<int> bit = {0, 0, 0, 0, 0, 0, 1, 2, 3};
    do
    {
        string num;
        num.resize(3);
        for (int i = 0; i < 9; i++)
            if (bit[i])
                num[bit[i] - 1] = 1 + (i + '0');

        bool flag = true;
        for (int t = 0; t < n && flag; t++)
        {
            int st = 0;
            for (int i = 0; i < 3; i++) // get strike
                if (v[t].num[i] == num[i])
                    st++;

            int b = -st;
            for (const auto &c : num) // get ball
                if (v[t].num.find(c) != string::npos)
                    b++;

            if (v[t].st != st || v[t].b != b)
                flag = false;
        }
        if (flag)
            ans++;

    } while (next_permutation(bit.begin(), bit.end()));

    cout << ans;
}