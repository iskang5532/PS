// 2022-10-09
// 20291 파일 정리
// https://www.acmicpc.net/problem/20291
/*
    sol.1) 정규표현식, 맵 (11,148KB, 268ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 문자열이 형식이 존재하며, 점 이후에 나오는 확장자를 필요로 함.
    이를 정규표현식을 이용하여 확장자만을 구함.
    - 입력된 확장자의 수를 저장해야 하므로, 맵을 사용.
    또한, 출력할 확장자는 사전순으로 출력해야 함. (이는 맵이 해결)
 */

#include <iostream>
#include <map>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

const regex _REGEX(R"(\w+.(\w+))"); // 확장자만을 검색
map<string, int> m;

int main()
{
    FAST_IO;

    int n; // 파일의 개수 (1 ≤ n ≤ 50,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        auto it = *sregex_iterator(s.begin(), s.end(), _REGEX);

        m[it[1]]++;
    }

    for (const auto &[s, cnt] : m)
        cout << s << ' ' << cnt << endl;
}

/*
    sol.2) 맵 (11,004KB, 104ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 문자열이 형식이 존재하며, 점 이후에 나오는 확장자를 필요로 함.
    즉, 입력된 문자열에서 점의 위치를 구한 후, 그 이후에 나오는 문자열은 확장자가 됨.
    - 입력된 확장자의 수를 저장해야 하므로, 맵을 사용.
    또한, 출력할 확장자는 사전순으로 출력해야 함. (이는 맵이 해결)
    - 확장자가 시작되는 위치 pos를 구한 후, s[pos]에서부터 시작되는 문자열을 맵에 저장.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

map<string, int> m;

int main()
{
    FAST_IO;

    int n; // 파일의 개수 (1 ≤ n ≤ 50,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        int pos = 0; // 확장자가 시작되는 위치
        while (s[pos++] != '.')
            ;

        m[string(s.begin() + pos, s.end())]++;
    }

    for (const auto &[s, cnt] : m)
        cout << s << ' ' << cnt << endl;
}