// 2022-05-03
// 9028 Iris (비밀번호)
// https://www.acmicpc.net/problem/9028
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어 및 텍스트를 대문자로 변경.
    - 텍스트를 탐색하며 단어에 존재하는 문자일 시, 큐에 문자의 위치를 저장.
    - 단어의 문자와 큐에 저장된 문자의 위치 pos를 이용.
    만약 현재 문자의 pos보다 이전 문자의 pos가 더 클 경우, 종료.
    - 현재 문자의 pos가 이전 문자의 pos보다 앞 혹은 뒤에 존재할 수 있으므로, 큐에 존재하는 값을 모두 확인해야 함.
    이를 위해 현재 문자의 pos가 더 클 때까지 값을 뺌. (단, 큐에 값이 존재할 경우)
    - 단어의 모든 문자를 탐색하면서 pos가 모두 올바른 경우, 벡터 v에 pos를 추가.
    - v의 크기와 v에 존재하는 값을 출력. 이때, 출력은 최대 3개임에 주의.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int t; // 1 ≤ T ≤ 20
    cin >> t;

    cin.ignore();
    while (t--)
    {
        string word, txt; // word.len ≤ 10, txt.len ≤ 200,000
        getline(cin, word), getline(cin, txt);

        queue<int> q[100];
        for (auto &c : word)
            c = toupper(c);
        for (int i = 0; i < txt.length(); i++)
            q[toupper(txt[i])].push(i + 1);

        vector<int> v; // v.size() ≤ 40,000
        int pos = 0;
        bool valid = true;
        while (valid)
        {
            for (const auto &c : word)
            {
                while (q[c].size() && pos > q[c].front())
                    q[c].pop();

                if (q[c].size() && pos < q[c].front())
                    pos = q[c].front(), q[c].pop();
                else
                    valid = false;
            }

            if (valid)
                v.push_back(pos), pos = 0;
        }

        cout << v.size() << ' ';
        for (int i = 0; i < v.size() && i < 3; i++)
            cout << v[i] << ' ';
        cout << endl;
    }
}