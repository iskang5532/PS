// 1331 나이트 투어
// https://www.acmicpc.net/problem/1331
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 나이트의 첫 번째 위치 st와 마지막 위치 ed.
    - 나이트의 현재 위치 cur와 이전 위치 prev.
    - 위치 (i, j)에 나이트의 방문 횟수를 저장할 visited.
    - 함수 isValid()를 선언하여 입력된 나이트가 유효한지를 확인.
    리턴 값이 false일 경우, "Invalid", true일 경우 다음 나이트의 위치 탐색
    - 나이트의 위치를 입력받은 후, 이전 위치와 현재 위치를 사용하여 isValid() 함수 사용.
    위치 prev에서 위치 cur로 이동할 수 있는 확인. cur에 도달할 수 없다면 false.
    현재 위치의 visited의 값이 1을 넘는 경우 false. (두 번 이상 방문)
    나이트의 마지막 위치가 입력될 때(i == 35), 추가로 st와 ed에 대해 isValid()를 수행. (ed에서 st로 이동할 수 있는지 확인)
    - isValid() 함수를 수행하여 false를 반환한 적이 없다면, "Valid" 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 6

constexpr int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1}; // 1시부터 시계방향으로
constexpr int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

struct pii
{
    int x, y;
    friend bool operator==(const pii &p1, const pii &p2) { return p1.x == p2.x && p1.y == p2.y; }
};

int visited[MAX][MAX];

bool isValid(const pii &prev, const pii &cur)
{
    if (visited[cur.x][cur.y] != 1)
        return false;

    for (int i = 0; i < 8; i++)
    {
        auto [nx, ny] = pii{prev.x + dx[i], prev.y + dy[i]};
        if (cur == pii{nx, ny})
            return true;
    }

    return false;
}

int main()
{
    FAST_IO;

    pii st, prev, ed;
    string s;

    cin >> s;
    st = prev = {s[0] - 'A', s[1] - '0'};
    visited[st.x][st.y]++;
    for (int i = 1; i < MAX * MAX; i++)
    {
        cin >> s;
        pii cur = {s[0] - 'A', s[1] - '0'};
        visited[cur.x][cur.y]++;

        if (!isValid(prev, cur))
        {
            cout << "Invalid";
            return 0;
        }

        if (i == 35 && !isValid(st, cur))
        {
            cout << "Invalid";
            return 0;
        }

        prev = cur;
    }

    cout << "Valid";
}