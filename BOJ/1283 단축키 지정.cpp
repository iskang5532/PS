// 2022-06-15
// 1283 단축키 지정
// https://www.acmicpc.net/problem/1283
/*
    구현, 문자열 (2,084KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 사용된 문자인지를 저장할 셋.
    대소문자를 구분치 않으므로, 문자를 저장할 때 대문자로 저장.
    - 입력된 문자열을 stringstream을 이용하여 나눈 후, 벡터 v에 저장.
    - v에 저장된 문자열을 탐색하며, 셋에 저장되어 있지 않은 문자가 나왔을 시 pos에 위치를 저장.
    - v에 저장된 문자열을 출력하되, 출력하는 값의 위치가 pos와 같을 시 괄호로 묶어 출력.
    etc.) 지저분한듯
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream> // stringstream

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
using pii = pair<int, int>;

unordered_set<char> S;

pii get_pos(const vector<string> &v)
{
    for (int i = 0; i < v.size(); i++) // 첫 글자 확인
    {
        char c = toupper(v[i].front());
        if (S.find(c) == S.end())
        {
            S.insert(c);
            return {i, 0};
        }
    }

    for (int i = 0; i < v.size(); i++) // 왼쪽에서부터
        for (int j = 1; j < v[i].length(); j++)
        {
            char c = toupper(v[i][j]);
            if (S.find(c) == S.end())
            {
                S.insert(c);
                return {i, j};
            }
        }

    return {-1, -1};
}

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 30
    cin >> n;
    cin.ignore();
    while (n--)
    {
        string sentence;
        getline(cin, sentence);

        stringstream ss(sentence);

        vector<string> v;
        string s;
        while (!ss.eof())
            ss >> s, v.push_back(s);

        pii pos = get_pos(v);

        for (int i = 0; i < v.size(); i++, cout << ' ') // print
            for (int j = 0; j < v[i].length(); j++)
                if (pos == pii{i, j})
                    cout << '[' << v[i][j] << ']';
                else
                    cout << v[i][j];

        cout << endl;
    }
}