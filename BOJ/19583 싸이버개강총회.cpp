// 2022-06-22
// 19583 싸이버개강총회
// https://www.acmicpc.net/problem/19583
/*
    셋 (12,864KB, 132ms)
    시간 복잡도: ?
    풀이)
    - stringstream을 이용하여 입력된 시간을 시와 분으로 나눈 후, 분으로 바꿈.
    - 출석한 인원을 셋에 저장. 이후, 퇴장한 인원이면서 셋에 있을 경우 ans++.
 */

#include <iostream>
#include <unordered_set>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define conv(h, m) h * 60 + m

unordered_set<string> us;

int main()
{
    FAST_IO;

    string s;
    getline(cin, s);

    int S, E, Q; // 시작한 시간 S, 끝낸 시간 E, 스트리밍 Q (00:00 ≤ S < E < Q ≤ 23:59)
    {
        stringstream ss(s);
        int h, m;
        char idx;
        ss >> h >> idx >> m;
        S = conv(h, m);
        ss >> h >> idx >> m;
        E = conv(h, m);
        ss >> h >> idx >> m;
        Q = conv(h, m);
    }

    int ans = 0;
    while (getline(cin, s))
    {
        int h, m;
        string name;
        char idx;

        stringstream ss(s);
        ss >> h >> idx >> m >> name;
        int t = conv(h, m);

        if (t <= S)
            us.insert(name);
        else if (E <= t && t <= Q && us.find(name) != us.end())
            ans++, us.erase(name);
    }

    cout << ans;
}