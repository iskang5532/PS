// 1013 Contact, 2671 잠수함식별
// https://boj.kr/1013 https://boj.kr/2671
/*
    정규표현식 (2,176KB, 0ms)
    시간 복잡도: ?
    참고)
    - 풀이 방법: https://blog.naver.com/jinhan814/222223626631
 */

#include <iostream>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

regex r(R"((100+1+|01)+)");

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        cout << (regex_match(s, r) ? "YES" : "NO") << endl; // 입력된 문자열 s가 정규표현식 패턴 r을 만족하는가?
    }
}