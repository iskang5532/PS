// 2022-09-27
// 10610 30
// https://www.acmicpc.net/problem/10610
/*
    정수론, 그리디 (2,300KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값 s의 각 수들의 합 sum이 3의 배수일 경우, s를 재배열해도 3의 배수이다.
    - 가장 큰 수를 출력해야 하므로, s의 문자를 기준으로 내림차순 정렬을 수행.
    - 30의 배수가 되야 하므로, s의 마지막 문자가 '0'인지를 확인.
    만약 마지막 문자가 '0'이면서 3의 배수일 경우, s 출력.
    만약 마지막 문자가 '0'이 아니거나 3의 배수가 아닐 경우, -1 출력.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222198273553
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    sort(s.begin(), s.end(), greater<char>());

    int sum = 0;
    for (const char &c : s)
        sum += c - '0';

    cout << (s.back() == '0' && sum % 3 == 0 ? s : "-1");
}
