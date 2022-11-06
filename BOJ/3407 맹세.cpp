// 2022-10-30
// 3407 맹세
// https://www.acmicpc.net/problem/3407
/*
    sol.1) BFS (2,332KB, 40ms)
    시간 복잡도: ?
    풀이)
    - 원소 기호를 셋 S에 저장.
    - 원소의 길이는 1 혹은 2이다. 그러므로, 입력된 문자열 s의 시작점 st에서부터 1 혹은 2의 l만큼의 문자열이 S에 있는지 확인.
    있을 경우, st += l 이후, 반복하여 해당 문자열이 발음할 수 있는 단어인지 확인.
    - 주의할 점은, 조사하는 길이의 순서에 따라 정답의 여부가 바뀔 수 있음.
    3의 길이를 가졌으면서 정답인 문자열 s가 있다면
     1. 1의 길이만큼 조사 후 나머지 2의 길이를 조사.
     2. 1의 길이만큼 조사 후 나머지 2의 길이 또한 1의 길이만큼 조사.
     3. 2의 길이만큼 조사 후 나머지 1의 길이를 조사.
    위 세 경우가 모두 정답은 아닐 수 있다.
    그러므로, 모든 경우를 확인해야 한다.
    - 가지치기를 하지 않으면서 모든 경우를 확인하게 될 경우 TLE.
    그러므로, 탐색 여부를 visited[]에 저장. (visited[i] = true일 경우, i번 문자부터의 탐색은 이미 수행함)
    etc.) visited[] 없이 구현했다가 TLE.
    참고)
    - TLE 해결: https://yabmoons.tistory.com/164
 */

#include <iostream>
#include <queue>
#include <set>

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using namespace std;
#define endl '\n'
#define MAX 50'003 // max s.length()

const set<string> _S = {
    "H", "He",
    "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
    "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe",
    "Cs", "Ba", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Fl", "Lv",
    "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu",
    "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr"};
set<string> S;

bool isValid(const string &s) // bfs
{

    queue<int> q;
    q.push(0);

    bool visited[MAX]{};
    visited[0] = true;

    while (q.size())
    {
        int st = q.front();
        q.pop();

        for (int l = 1; l <= min(2, (int)s.length() - st); l++)
            if (!visited[st + l] && S.find(s.substr(st, l)) != S.end())
            {
                if (st + l == s.length())
                    return true;
                q.push(st + l), visited[st + l] = true;
            }
    }

    return false;
}

int main()
{
    FAST_IO;

    auto toLower = [](const string &s) -> string
    {
        string ret;
        for (const char &c : s)
            ret += (c | 32);

        return ret;
    };
    for (const string &s : _S)
        S.insert(toLower(s));

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        cout << (isValid(s) ? "YES" : "NO") << endl;
    }
}

/*
    sol.2) DFS (5,544KB, 28ms)
    시간 복잡도: ?
 */

#include <iostream>
#include <set>

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using namespace std;
#define endl '\n'
#define MAX 50'003 // max s.length()

const set<string> _S = {
    "H", "He",
    "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
    "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe",
    "Cs", "Ba", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Fl", "Lv",
    "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu",
    "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr"};
set<string> S;
bool visited[MAX]; // visited[i] = true일 경우, i번 문자부터의 탐색은 이미 수행함

bool isValid(const string &s, int st = 0) // dfs
{
    if (st == s.length())
        return true;

    visited[st] = true;

    bool valid = false;
    for (int l = 1; l <= min(2, (int)s.length() - st) && !valid; l++)
        if (!visited[st + l] && S.find(s.substr(st, l)) != S.end())
            valid |= isValid(s, st + l);

    return valid;
}

int main()
{
    FAST_IO;

    auto toLower = [](const string &s) -> string
    {
        string ret;
        for (const char &c : s)
            ret += (c | 32);

        return ret;
    };
    for (const string &s : _S)
        S.insert(toLower(s));

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        fill(visited, visited + MAX, false);

        cout << (isValid(s) ? "YES" : "NO") << endl;
    }
}