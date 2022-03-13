// 9205 맥주 마시면서 걸어가기
// https://www.acmicpc.net/problem/9205
/*
    BFS (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 시작점에서부터 도착점까지 편의점을 거쳐 도달할 수 있는지를 판별하는 문제.
    - 임의의 지점에서 다음 지점까지의 거리는 1000 이하여야 한다. (단, 거리는 맨하튼 거리)
    - 방문 여부를 저장할 visited.
    2차원 배열로 선언 시 약 60,000^2이며, 엄청난 메모리를 차지한다.
    그러므로, 입력된 편의점의 인덱스를 사용한다. (visited[i] = true일 경우, i번째 편의점은 방문 가능)
    - 만약 현재 탐색중인 시작점 혹은 편의점에서 도착점까지 도달 가능한 거리가 된 경우, "happy" 출력.
    모두 탐색을 하였지만 도착점까지 도달할 수 없을 경우, "sad" 출력.
    etc.) 풀이가 BFS인게 신기했던 문제.
    참고)
    - 반례: https://www.acmicpc.net/board/view/33032
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 103

struct pii
{
    int x, y;
};

bool isValid(const vector<pii> &v, pii st, pii ed) // 시작점에서 도착점까지 도달 가능한가?
{
    queue<pii> q;
    q.push(st);

    bool visited[MAX]; // visited[i] = true일 경우, i번째 편의점은 방문이 가능
    fill(visited, visited + MAX, false);

    while (q.size())
    {
        auto [x, y] = q.front();
        q.pop();

        if (abs(x - ed.x) + abs(y - ed.y) <= 1000) // 도착점에 도달 가능한 거리인가
            return true;

        for (int i = 0; i < v.size(); i++)
        {
            if (visited[i])
                continue;

            auto [nx, ny] = v[i];
            if (abs(x - nx) + abs(y - ny) > 1000) // 다음 편의점에 도달하지 못할 거리인 경우
                continue;

            q.push({nx, ny}), visited[i] = true;
        }
    }

    return false;
}

int main()
{
    FAST_IO;

    int tc; // 테스트 케이스의 개수 (tc ≤ 50)
    cin >> tc;
    while (tc--)
    {
        int n; // 편의점의 개수 (0 ≤ n ≤ 100)
        cin >> n;

        pii st, ed;       // 집, 페스티버
        vector<pii> v(n); //  편의점

        cin >> st.x >> st.y;
        for (auto &[x, y] : v)
            cin >> x >> y;
        cin >> ed.x >> ed.y;

        if (isValid(v, st, ed)) // 시작점에서 도착점까지 도달 가능한가?
            cout << "happy" << endl;
        else
            cout << "sad" << endl;
    }
}

// input:
// 3
// 0
// 1000 1000
// 1000 1001
// 1
// 0 0
// 1000 0
// 0 2000
// 2
// 0 0
// 10000 0
// 0 1000
// 0 2000
// ans:
// happy
// sad
// happy