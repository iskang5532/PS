// 2022-04-23
// 1157 단어 공부
// https://www.acmicpc.net/problem/1157
/*
    구현 (4,916KB, 40ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 입력받은 후, 문자를 하나씩 확인하여 개수를 파악하여 cnt[]에 저장.
    이떄, 소문자와 대문자가 섞여 있을 수 있으므로, 확인중인 문자는 대문자로 바꿔줌.
    - 가장 많은 문자의 개수를 mx에 저장.
    - 입력된 문자의 개수를 탐색. 만약 현재 문자의 개수가 mx와 같은 경우, 다음 주 가지 경우를 수행.
    만약 ans에 문자가 저장된 적이 없다면, 현재 문자를 ans에 저장.
    만약 ans에 문자가 저장되어 있다면, '?'를 출력 후 종료. (이미 문자가 저장되어 있다면, 동일한 개수임)

 */

#include <iostream>
using namespace std;
#define MAX 30

int main()
{
    int cnt[MAX]{};

    string s;
    cin >> s;

    for (const auto &c : s)
        cnt[(c & ~(1 << 5)) - 'A']++;

    int mx = 0;
    for (int i = 0; i < MAX; i++)
        mx = max(mx, cnt[i]);

    char ans = '\0';
    bool flag = true;
    for (int i = 0; i < MAX && flag; i++)
        if (cnt[i] == mx)
            if (ans != '\0')
                flag = false;
            else
                ans = 'A' + i;

    cout << (flag ? ans : '?');
}