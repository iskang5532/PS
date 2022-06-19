// 2022-06-14
// 22233 가희와 키워드
// https://www.acmicpc.net/problem/22233
/*
    셋, 파싱 (17,400KB, 856ms)
    시간 복잡도: ?
    풀이)
    - 메모장에 적은 n개의 키워드를 셋 s에 저장.
    - 문자열을 입력받음.
    입력받은 문자열 s를 쉼표를 구분하여 나눈 후, 셋에서 문자열을 지움.
    셋의 크기를 출력.
    이후 입력받은 문자열도 위와 마찬가지로 진행.
    - 입력된 문자열의 구분은 쉼표를 공백으로 변경 후, stringstream을 이용.
    etc.) 예전 어느 문제에서 어떤 분이 사용한 풀이법.
    - set에서 erase()를 이용해 없는 원소를 지우는 것은 에러가 아닌가?
 */

#include <iostream>
#include <unordered_set>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

unordered_set<string> S;

int main()
{
    FAST_IO;

    int n, m; //  키워드 개수 n, 글의 개수 m (1 ≤ n, m ≤ 2×10^5 )
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s, S.insert(s);
    }

    while (m--)
    {
        string word;
        cin >> word;

        for (auto &c : word)
            if (c == ',')
                c = ' ';

        stringstream ss(word);
        string s;
        while (!ss.eof())
        {
            ss >> s;
            // if (S.find(s) != S.end())
            S.erase(s);
        }

        cout << S.size() << endl;
    }
}