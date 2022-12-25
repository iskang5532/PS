// 2022-12-21
// 2529 부등호
// https://www.acmicpc.net/problem/2529
/*
    백트래킹, 순열 (2,024KB, 12ms)
    시간 복잡도: O(k!)
    풀이)
    - k의 최대 개수가 적지 않으므로, 알고리즘에 내장된 순열을 이용. (O(k!))
    - 최댓값을 구하는 get_max(), 최솟값을 구하는 get_min()을 만들어 정답을 구함.
    - get_max()같은 경우, k개의 수로 만들 수 있는 가장 큰 값을 num에 넣은 후 prev_permutation()를 이용.
    이후, 가장 빠르게 조건(괄호; v)을 만족하는 수를 찾을 경우, 해당 수를 반환.
    - get_min()같은 경우, k개의 수로 만들 수 있는 가장 작은 값을 num에 넣은 후 next_permutation()을 이용.
    이후, 가장 빠르게 조건을 만족하는 수를 찾을 경우, 해당 수를 반환.
    etc.) 지저분
 */

#include <iostream>
#include <vector>
#include <algorithm> // permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

string get_max(const vector<char> &v)
{
    string ret;

    vector<int> num(v.size() + 1);
    for (int i = 9; i >= 9 - (int)v.size(); i--)
        num[9 - i] = i;

    do
    {
        bool flag = true;
        for (int i = 0; i < num.size() - 1 && flag; i++)
            if (v[i] == '<' && !(num[i] < num[i + 1]))
                flag = false;
            else if (v[i] == '>' && !(num[i] > num[i + 1]))
                flag = false;

        if (flag)
        {
            for (const int &i : num)
                ret += i + '0';
            break;
        }
    } while (prev_permutation(num.begin(), num.end()));

    return ret;
}

string get_min(const vector<char> &v)
{
    string ret;

    vector<int> num(v.size() + 1);
    for (int i = 0; i <= v.size(); i++)
        num[i] = i;
    do
    {
        bool flag = true;
        for (int i = 0; i < num.size() - 1 && flag; i++)
            if (v[i] == '<' && !(num[i] < num[i + 1]))
                flag = false;
            else if (v[i] == '>' && !(num[i] > num[i + 1]))
                flag = false;

        if (flag)
        {
            for (const int &i : num)
                ret += i + '0';
            break;
        }
    } while (next_permutation(num.begin(), num.end()));

    return ret;
}

int main()
{
    FAST_IO;

    int k; // 부등호의 개수 (1 ≤ k ≤ 9)
    cin >> k;
    vector<char> v(k);
    for (auto &c : v)
        cin >> c;

    string mx = get_max(v);
    string mn = get_min(v);

    cout << mx << '\n'
         << mn;
}