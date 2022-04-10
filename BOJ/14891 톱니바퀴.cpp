// 14891 톱니바퀴
// https://www.acmicpc.net/problem/14891
// 2022-04-06
/*
    구현 (2,024KB, 0ms)
    풀이)
    - 회전할 톱니바퀴를 기준으로 좌측 톱니바퀴들과 우측 톱니바퀴들을 탐색.
    - 인접한 좌측 톱니바퀴 l이 회전 가능할 경우, l-1번쨰 톱니바퀴와 l번째 톱니바퀴를 비교.
    마찬가지로 l-1번쨰 톱니바퀴가 회전 가능할 경우, l-2번째와 l-1번째를 비교.
    이를 첫 번째 톱니바퀴를 확인할 때까지 수행하거나 l번째 톱니바퀴가 회전할 수 없을 때까지 수행.
    r 또한 l과 똑같이 수행하며, 마찬가지로 마지막 톱니바퀴를 확인할 때까지 수행하거나 r번째 톱니바퀴가 회전할 수 없을 때까지 수행.
    - 톱니바퀴의 회전 방향을 저장할 dir[]. (dir[i] = d일 경우, i번째 톱니바퀴의 방향은 d)
    모든 톱니바퀴의 방향을 확인하여 시계 방향 혹은 반시계 방향에 맞춰 회전시킴.
    - k번 회전이 완료된 경우, 모든 톱니바퀴의 12시 방향 값을 확인하여 계산.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 4
#define RIGHT 2
#define LEFT 6

void shift_right(string &s) { s = s[7] + s.substr(0, 7); }                // 시계 
void shift_left(string &s) { s = string(s.begin() + 1, s.end()) + s[0]; } // 반시계

string s[MAX];

void rotated(int pos, int d) // 회전
{
    int dir[MAX]{}; // dir[i] = d일 경우, i번째 톱니바퀴의 방향은 d
    dir[pos] = d;

    for (int l = pos - 1, cur = pos; l >= 0; l--, cur--) // 좌측의 톱니바퀴들 확인
    {
        if (s[l][RIGHT] == s[cur][LEFT])
            break;
        dir[l] = -dir[cur];
    }
    for (int r = pos + 1, cur = pos; r < MAX; r++, cur++) // 우측의 톱니바퀴들 확인
    {
        if (s[cur][RIGHT] == s[r][LEFT])
            break;
        dir[r] = -dir[cur];
    }

    for (int i = 0, bit; i < MAX; i++)
        if (dir[i] == 1) // 시계
            shift_right(s[i]);
        else if (dir[i] == -1) // 반시계
            shift_left(s[i]);
}

int main()
{
    FAST_IO;

    cin >> s[0] >> s[1] >> s[2] >> s[3];

    int k; // 회전 횟수 (1 ≤ K ≤ 100)
    cin >> k;
    while (k--)
    {
        int pos, d; // 1: 시계 방향, -1: 반시계 방향
        cin >> pos >> d;
        pos--;

        rotated(pos, d); // 회전
    }

    int ans = 0;
    for (int i = 0; i < MAX; i++)
        if (s[i][0] == '1')
            ans += 1 << i;
    cout << ans;
}

/*
    sol.2) 구현, 비트셋 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 비트셋을 이용한 풀이.
    주의할 점은, 입력되는 값부터 [7], [6], ... , [0]이다.
    etc.) 풀때 시프트가 필요하다고 생각해서 비트셋으로 풀었는데, 문자열로 구현했어도 크게 상관 없었던 문제
 */

#include <iostream>
#include <bitset>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 4
#define RIGHT 5
#define LEFT 1

bitset<8> wheel[MAX];

void turnned(int pos, int d)
{
    int dir[MAX]{};
    dir[pos] = d;

    for (int l = pos - 1, cur = pos; l >= 0; l--, cur--) // 좌측의 톱니바퀴들 확인
    {
        if (wheel[l][RIGHT] == wheel[cur][LEFT])
            break;
        dir[l] = -dir[cur];
    }
    for (int r = pos + 1, cur = pos; r < MAX; r++, cur++) // 우측의 톱니바퀴들 확인
    {
        if (wheel[cur][RIGHT] == wheel[r][LEFT])
            break;
        dir[r] = -dir[cur];
    }

    for (int i = 0, bit; i < MAX; i++)
        if (dir[i] == 1) // 시계
            bit = wheel[i][0], wheel[i] >>= 1, wheel[i][7] = bit;
        else if (dir[i] == -1) // 반시계
            bit = wheel[i][7], wheel[i] <<= 1, wheel[i][0] = bit;
}

int main()
{
    FAST_IO;

    cin >> wheel[0] >> wheel[1] >> wheel[2] >> wheel[3];

    int k; // 회전 횟수 (1 ≤ K ≤ 100)
    cin >> k;
    while (k--)
    {
        int pos, d; // 1: 시계 방향, -1: 반시계 방향
        cin >> pos >> d;
        pos--;

        rotated(pos, d);
    }

    int ans = 0;
    for (int i = 0; i < MAX; i++)
        if (wheel[i][7] == 1)
            ans += 1 << i;
    cout << ans;
}