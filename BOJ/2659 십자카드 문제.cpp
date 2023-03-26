// 2023-03-24
// 2659 십자카드 문제
// https://www.acmicpc.net/problem/2659
/*
    완전 탐색, 정렬 (2,160KB, ms)
    시간 복잡도: ?
    풀이)
    - 1111부터 9999까지 구한 시계수를 v에 저장. 단, 수에 0이 들어있을 경우 제외.
    구한 시계수를 정렬 후, 중복된 값을 제거.
    - 입력된 값의 시계수를 구한 후 v에 몇 번째로 위치할 값인지 구함.
    이는 앞에 존재하는 작은 값의 개수가 정답이므로, upper_bound()를 이용.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int get_k(string s)
{
    string ret = "9999";
    for (int st = 0; st < 4; st++)
    {
        string _s;
        for (int j = 0; j < 4; j++)
            _s += s[(st + j) % 4];

        ret = min(ret, _s);
    }

    return stoi(ret);
}

int main()
{
    FAST_IO;

    vector<int> v;
    for (int i = 1111; i <= 9999; i++)
    {
        string s = to_string(i);
        if (s[0] == '0' || s[1] == '0' || s[2] == '0' || s[3] == '0')
            continue;

        v.push_back(get_k(s));
    }

    sort(v.begin(), v.end());

    v.erase(unique(v.begin(), v.end()), v.end());

    string s;
    for (int i = 0; i < 4; i++)
    {
        char k;
        cin >> k;
        s += k;
    }

    cout << upper_bound(v.begin(), v.end(), get_k(s)) - v.begin();
}