// 2023-03-07
// 20055 컨베이어 벨트 위의 로봇
// https://www.acmicpc.net/problem/20055
/*
    덱, 구현 (2,024KB, 64ms)
    시간 복잡도: ?
    풀이)
    - 컨테이너의 값을 옮기는 행위와 인덱스를 확인할 수 있는 덱을 사용.
    덱으로 hp를 생성 후, 각 칸의 내구도를 저장.
    - 해당 위치에 로봇이 존재하는지를 저장할 robot[].
    1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
    - hp 및 robot을 한 칸 옮김
    2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
    - 우측에 존재하는 로봇일수록 우선적으로 올라온 로봇이다. 그러므로, 우측부터 확인.
     2-1. 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1 이상 남아 있어야 한다.
     - 다음 위치의 robot과 hp를 확인.
    3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
    - hp[0]을 확인하여 robot[0]을 결정
    4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
    - 모든 hp의 인덱스를 확인.
 */

#include <iostream>
#include <deque>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 203

int n, k;        // 길이 n(2 ≤ n ≤ 100), 필요 개수 k(1 ≤ 2n)
deque<int> hp;   // 1 ≤ hp ≤ 1,000
bool robot[MAX]; // robot[i] = true일 경우, i번 위치에 로봇은 존재

bool is_done()
{
    int cnt = 0;
    for (const int i : hp)
        if (i == 0)
            cnt++;

    return (cnt >= k) ? true
                      : false;
}

void added_robot()
{
    if (!robot[0] && hp.front()) // 시작 위치에 로봇이 없으면서 내구도가 1 이상인 경우
        robot[0] = true, hp.front()--;
}

void moved_robot()
{
    for (int pos = (n - 1) - 1; pos >= 0; --pos) // 움직일 로봇의 위치
    {
        if (robot[pos + 1]) // 다음 위치에 로봇이 있을 경우
            continue;
        if (robot[pos] && hp[pos + 1]) // 현재 위치에 로봇이 있으면서 다음 칸의 내구도가 1 이상인 경우
            robot[pos] = false, robot[pos + 1] = true, hp[pos + 1]--;
    }
}

void rotated()
{
    hp.push_front(hp.back()), hp.pop_back();
    for (int i = MAX - 1; i >= 0; --i)
        robot[i] = robot[i - 1];
    robot[0] = robot[n - 1] = false;
}

int main()
{
    FAST_IO;

    cin >> n >> k;

    for (int i = 0; i < n * 2; i++)
    {
        int k;
        cin >> k;

        hp.push_back(k);
    }

    int ans = 0;
    do
    {
        rotated(); // 1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.

        moved_robot(); // 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.
        added_robot(); // 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.

    } while (++ans && !is_done()); // 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.

    cout << ans;
}