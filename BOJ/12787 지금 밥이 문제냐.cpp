// 2023-03-27
// 12787 지금 밥이 문제냐
// https://www.acmicpc.net/problem/12787
/*
    구현, 문자열 (2,080KB, 0ms)
    시간 복잡도: ?
    풀이)
    m == 1일 경우
    - 입력된 문자열에 존재하는 8개의 수는 각각 8개의 비트를 사용한다.
    또한, 우측에 있는 수부터 우측 8개의 비트를 사용하므로, 입력된 값의 위치에 맞춰 비트연산을 수행한다.
    m == 2일 경우
    - 입력된 수를 8비트씩 읽어 값을 나누어 ans에 저장.
    - 총 64비트이므로, 8비트씩 8번을 수행한다.
    - 값은 우측 비트를 먼저 읽으므로 출력 시에 주의.
 */

#include <iostream>
#include <sstream> // stringstream

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ull = unsigned long long;
#define endl "\n"

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int m; // 종류 m
        cin >> m;

        if (m == 1) // IPv8 주소를 부호가 없는 정수로 변환
        {
            string s;
            cin >> s;
            stringstream ss(s);

            ull ans = 0;
            for (int i = 7; i >= 0; --i)
            {
                ull k;
                char idx;
                ss >> k >> idx;

                ans += k << (8 * i);
            }

            cout << ans << endl;
        }
        else if (m == 2) // 부호가 없는 정수를 IPv8 주소로 변환
        {
            ull k;
            cin >> k;

            string ans;
            for (int i = 0; i < 8; i++)
                ans = '.' + to_string(k & 0b11111111) + ans, k >>= 8;

            cout << string(ans.begin() + 1, ans.end()) << endl;
        }
    }
}