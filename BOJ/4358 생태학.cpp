/* 
 * 4358 생태학
 * map
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/4358
 * ETC.) 소수점 출력이 포함되기 때문에 그와 관련된 코드가 있음 (fixed, cout.precision, double cast)
 */

#include <iostream>
#include <map>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    map<string, int> m; // 나무의 이름(= str) 및 언급 횟수 저장
    string str;
    int total = 0; // 입력 횟수
    while (getline(cin, str))
        m[str]++, total++; // 해당 str의 값 +1, 입력 횟수 +1

    cout << fixed, cout.precision(4);                    // 소수점 네 자리로 고정
    const double per = static_cast<double>(100) / total; // 백분율화 시켜주기 위한 값
    for (const auto &[str, cnt] : m)                     // 출력
        cout << str << " " << per * cnt << endl;
}