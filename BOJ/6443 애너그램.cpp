// 2022-12-06
// 6443 애너그램
// https://www.acmicpc.net/problem/6443
/*
    sol.1) 백트래킹 (2,024KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어의 철자들을 재조합하여 만들 수 있는 모든 단어를 출력해야 한다.
    단, 중복된 단어는 한 번만 출력해야 하며, 오름차순으로 출력해야 한다.
    - next_permutation을 이용하여 해당 단어의 철자로 만들 수 있는 중복 없는 단어를 구하여 출력한다.
    이때, 오름차순 출력 및 모든 단어를 구하기 위해 입력된 문자열을 오름차순 정렬한다.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 단어의 개수
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s; // s.length() ≤ 20
        cin >> s;
        sort(s.begin(), s.end());

        do
            cout << s << endl;
        while (next_permutation(s.begin(), s.end()));
    }
}


/*
    sol.2) 백트래킹 (15,632KB, 72ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어의 철자들을 재조합하여 만들 수 있는 모든 단어를 출력해야 한다.
    단, 중복된 단어는 한 번만 출력해야 하며, 오름차순으로 출력해야 한다.
    - 오름차순 출력을 위해, 입력된 문자열 word를 오름차순 정렬한다.
    - dfs를 이용하여 word의 철자로 만들 수 있는 모든 단어를 구하여 v에 저장하며, visited[]를 이용하여 사용된 문자의 위치를 저장한다.
    - 중복된 단어는 제외해야 한다.
    dfs를 이용하여 단어를 구하는 과정에서 이전에 구한 단어와 동일한 단어가 나올 것 같다면, 더 이상 탐색하지 않고 다음 단어를 구해야 한다.
    이를 알기 위해서는, 현재 s의 마지막 문자를 기억하여 사용한다.
    만약 s[pos]를 추가하는 과정에서 이전 s[pos]와 현재 s[pos]가 같을 경우, 최종적으로 이전에 구한 s와 현재 구해질 s는 같다.
    - s와 word의 길이가 동일한 경우, v에 s를 저장.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 23 // max word.length()

string word; // word.length() ≤ 20
bool visited[MAX];
vector<string> v;

void get_ans(const string &s)
{
    if (s.length() == word.length())
    {
        v.push_back(s);
        return;
    }

    char prev = '\0'; // 이전에 구성된 s의 마지막 문자 (= s.back())
    for (int pos = 0; pos < word.length(); pos++)
        if (!visited[pos] && prev != word[pos]) // 이전에 구한 s와 같은지 확인
        {
            prev = word[pos];
            visited[pos] = true;
            get_ans(s + word[pos]);
            visited[pos] = false;
        }
}

int main()
{
    FAST_IO;

    int n; // 단어의 개수
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> word;
        sort(word.begin(), word.end());

        get_ans("");
    }

    for (const string &word : v)
        cout << word << endl;
}