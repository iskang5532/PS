// 2022-07-27
// 5002 도어맨
// https://www.acmicpc.net/problem/5002
/*
    그리디, 투 포인터? (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 앞에서부터 두 사람 중 선택하여 입장시킬 수 있음.
    이 둘의 위치를 관리할 l, r. (l은 상대적으로 앞사람의 위치, r은 상대적으로 뒷사람의 위치를 가리킴)
    - 남자와 여자의 차이를 저장할 cnt. (cnt가 양수일 경우 남자가, 음수일 경우 여자가 cnt만큼 많음)
    - s[l]과 s[r]의 성별을 1 또는 -1로 바꾸어 a, b에 저장.
    s[l]과 s[r]을 입장시켰을 시의 비율을 확인.
     만약 s[l]을 입장시켜도 비율이 맞을 시, s[l] 입장.
    (s[l]이 안됐으면서) 만약 s[r]을 입장시켜도 비율이 맞을 시, s[r] 입장.
    위 두 가지 모두 안 됐을 시, 비율을 맞출 수 있는 인원은 클럽에 입장해 있는 인원이 최대.
    - 주의할 점은, l의 위치가 이미 조사한 사람의 위치로 갈 수 있다는 것이다.
    이를 막기 위해, l은 r의 값을 받는다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103 // max str length

int main()
{
    FAST_IO;

    int x;
    cin >> x;
    string s;
    cin >> s;

    int ans = 0, cnt = 0; // cnt가 양수일 경우 남자가, 음수일 경우 여자가 cnt만큼 많음
    for (int l = 0, r = 1; l < s.length(); ans++)
    {
        int a = s[l] == 'M' ? 1 : -1, // s[l]의 성별
            b = s[r] == 'M' ? 1 : -1; // s[r]의 성별

        if (abs(cnt + a) <= x) // s[l]을 입장시켰을 시, x 이하인가?
            l = r, r++, cnt += a;
        else if (r != s.length() && abs(cnt + b) <= x) // s[r]을 입장시켰을 시, x 이하인가?
            r++, cnt += b;
        else
            break;
    }

    cout << ans;
}