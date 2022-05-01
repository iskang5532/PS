// 2022-04-29
// 9733 꿀벌
// https://www.acmicpc.net/problem/9733
/*
    구현 (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 명령이 몇 번 입력됐는지를 저장할 맵을 선언한 후, 명령이 들어올 때마다 횟수 저장.
    또한, 전체 횟수를 tot에 저장.
    - 모든 입력이 끝난 후, 출력 순서에 맞게 맵에서 명령의 횟수와 tot을 이용하여 값을 출력.
    - fixed 및 precision을 이용하여 소숫점 고정 및 반올림을 해줌.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 7

string cmd[] = {"Re", "Pt", "Cc", "Ea", "Tb", "Cm", "Ex"};
map<string, int> m;

int main()
{
    FAST_IO;

    int tot = 0;
    string s;
    while (cin >> s)
        m[s]++, tot++;

    cout << fixed, cout.precision(2);
    for (int i = 0; i < MAX; i++)
        cout << cmd[i] << ' ' << m[cmd[i]] << ' ' << (double)m[cmd[i]] / tot << endl;
    cout << "Total" << ' ' << tot << ' ' << "1.00";
}