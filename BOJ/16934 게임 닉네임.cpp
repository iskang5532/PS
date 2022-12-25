// 2022-12-22
// 16934 게임 닉네임
// https://www.acmicpc.net/problem/16934
/*
    트라이 (62,960KB, 108ms)
    시간 복잡도: ?
    풀이)
    - 트라이 구조를 이루는 root에 입력된 문자열 s를 추가함.
    s를 추가하는 과정에서 해당 문자가 존재하지 않을 경우, 해당 문자까지의 문자열 prefix가 별칭.
    단, prefix가 s와 같을 경우 s와 같은 문자열이 앞서 몇 번 입력됐는지 확인하여 별칭을 정함. (= 동일한 닉네임의 개수 파악)
    - s의 마지막 문자를 추가한 후, cnt++하여 닉네임의 개수를 늘림.    
    etc.) cnt를 잘못해서 헤맴.
    - prefix를 좀 더 이쁘게 배치할 수는 없는가? (구조체 안에 넣는다던가)
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

vector<string> prefix;

struct Node
{
    map<char, Node *> m;
    int cnt = 0; // 동일한 닉네임의 개수

    void add(const string &s, int pos = 0, bool valid = false) // s[pos], 별칭을 정했는지를 저장할 valid
    {
        if (pos == s.length())
        {
            cnt++;
            if (!valid) // 아직까지 별칭을 구하지 못한 경우
                prefix.push_back(s + (cnt == 1 ? "" : to_string(cnt))), valid = true;
            return;
        }

        const char next = s[pos];
        const auto &itr = m.find(next);
        if (itr == m.end()) // 해당 문자가 없을 경우
        {
            if (!valid) // 별칭을 구하지 못한 경우, pos까지의 문자열을 별칭으로 사용
                prefix.push_back(string(s.begin(), s.begin() + 1 + pos)), valid = true;

            m[next] = new Node;
        }

        m[next]->add(s, pos + 1, valid);
    }
} root;

int main()
{
    FAST_IO;

    int n; // 유저의 수 (1 ≤ n ≤ 100,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        root.add(s);
    }

    for (const string &s : prefix)
        cout << s << endl;
}