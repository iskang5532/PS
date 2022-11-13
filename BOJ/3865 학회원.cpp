// 2022-11-09
// 3865 학회원
// https://www.acmicpc.net/problem/3865
/*
    DFS, 맵, 셋, 문자열 (2,300KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열을 학회(왼쪽 문자열) aca와 학회원(오른쪽 문자열) people로 나눔.
    이후, 협회의 목록인 l에 aca를 저장하며, 협회와 협회에 소속된 회원을 보관하는 r에 해당 협회와 인원을 저장.
    r[l] = {a, b}일 경우, 학회 l에 소속된 회원은 a와 b.
    이때, a와 b는 협회일 수 있음에 주의.
    - 제일 처음으로 주어지는 학회를 이용해야 하므로, st에 첫 학회를 저장.
    - st에 속한 회원들을 확인하여 ans에 저장.
    만약 회원이 아닌 학회일 경우, 그 학회에 포함된 인원을 ans에 저장.
    - dfs를 이용하여 ans를 구함.
    이때, 임의의 학회에 여러 번 방문할 수 있으므로 이를 방지하기 위해 visited에 방문한 학회를 저장하여 사용.
    etc.) 학생을 어떤 식으로 저장해야 하는지가 관건이었던 문제였음
 */

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

set<string> l;              // 학회
map<string, set<string>> r; // 학생
set<string> visited, ans;

void dfs(const string &cur)
{
    for (const string &next : r[cur])
    {
        if (visited.find(next) != visited.end()) // 탐색한 적이 있는가
            continue;

        visited.insert(next);
        if (l.find(next) != l.end()) // 협회인가?
            dfs(next);
        else
            ans.insert(next);
    }
}

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 100
    while (cin >> n)
    {
        if (!n)
            break;
        l.clear(), r.clear(), visited.clear(), ans.clear();

        string st; // 기준이 되는 학회
        for (int _ = 0; _ < n; _++)
        {
            string s;
            cin >> s;

            int pos = s.find(':', 0);
            string aca = s.substr(0, pos); // 학회 (좌측 문자열)
            l.insert(aca);
            if (_ == 0)
                st = aca;

            int prev = pos + 1;
            while ((pos = s.find(',', pos + 1)) != string::npos) // 학회원을 추출 (우측 문자열)
            {
                string people = string(s.begin() + prev, s.begin() + pos);
                r[aca].insert(people);

                prev = pos + 1;
            }
            r[aca].insert(string(s.begin() + prev, s.end() - 1));
        }

        for (const string &cur : r[st])
            if (l.find(cur) != l.end())
                dfs(cur);
            else
                visited.insert(cur), ans.insert(cur);

        cout << ans.size() << endl;
    }
}