// 2022-10-12
// 9996 한국이 그리울 땐 서버에 접속하지
// https://www.acmicpc.net/problem/9996
/*
    sol.1) 문자열, 구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 별표가 하나이므로, 별표를 기준으로 문자열을 두 개로 나눈다.
    이후, s 또한 두 문자열로 나눈 후 비교한다.
    - 별표를 기준으로 나눠진 왼쪽 문자열의 길이 l만큼 s의 부분 문자열과 비교한다.
    만약 다를 경우, false.
    - 별표를 기준으로 나눠진 오른쪽 문자열의 길이 r만큼 s의 부분 문자열과 비교한다.
    만약 다를 경우, false.
    - l + r보다 s의 길이가 작을 수 있다. 이 또한 false.
    참고)
    - 반례: https://www.acmicpc.net/board/view/20672
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

bool isValid(const string &pt, const string &s)
{
    int pos = 0;
    while (pt[pos++] != '*')
        ;

    int l = pos - 1, r = pt.length() - pos; // 별표 왼쪽과 오른쪽

    if (s.length() < l + r) // s가 너무 짧은 경우
        return false;
    if (pt.substr(0, l) != s.substr(0, l)) // 왼쪽의 문자열이 다른 경우
        return false;
    if (string(pt.end() - r, pt.end()) != string(s.end() - r, s.end())) // 오른쪽의 문자열이 다른 경우
        return false;

    return true;
}

int main()
{
    FAST_IO;

    int n; // 파일의 개수 (1 ≤ n ≤ 100)
    cin >> n;
    string pt;
    cin >> pt;

    for (int i = 0; i < n; i++)
    {
        string s; // s.length() ≤ 100
        cin >> s;

        cout << (isValid(pt, s) ? "DA" : "NE") << endl;
    }
}

/*
    sol.2) 정규표현식 (2,308KB, 8ms)
    시간 복잡도: ?
    풀이)
    - pt를 정규표현식에 필요한 문법으로 바꾸기 위해 별표('*')를 "\w*"로 변경.
    이후, regex_match()를 이용하여 입력된 문자열 s가 패턴을 만족하는지 확인.
    - "\w*"로 변경됨에 따라, 그 자리에는 0개 이상의 문자가 존재해도 된다.
    참고)
    - 코드: https://congsoony.tistory.com/132
    - 정규표현식: https://blog.naver.com/jinhan814/222090272427
 */

#include <iostream>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 파일의 개수 (1 ≤ n ≤ 100)
    cin >> n;
    string pt;
    cin >> pt;

    pt.replace(pt.find('*'), 1, "\\w*"); // pt를 정규표현식 문법으로 변경
    for (int i = 0; i < n; i++)
    {
        string s; // s.length() ≤ 100
        cin >> s;

        cout << (regex_match(s, regex(pt)) ? "DA" : "NE") << endl;
    }
}