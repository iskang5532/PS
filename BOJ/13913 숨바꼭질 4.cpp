/* 
 * 13913 숨바꼭질 4
 * BFS, backtrace
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/13913
 */

#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"
#define MAX 100000 + 1

struct Link
{
    int prev_pos = 0, cnt = 0;
};

// visited[n]일 때, start(시작점)에서 n번까지의 최소 횟수(cnt)와 n번 이전의 위치(prev_pos)를 저장 (이전 위치는 -1번째가 아닌 n번에 방문하기 이전의 위치임)
vector<Link> visited(MAX);

void BFS(const int start, const int end)
{
    queue<int> q;  // +1, -1, *2 연산을 위한 저장 공간
    q.push(start); // 시작점에서 출발

    while (!q.empty())
    {
        int curr_pos = q.front(); // 현재 위치는, q에 입력된 순서대로
        if (curr_pos == end)      // 만약 현재 위치가 목적지와 같은 경우 (= 도착)
            return;
        q.pop(); // 현재 위치 값에 대한 연산을 마칠 예정이니, 값을 빼줌 (중복된 연산으로 인한 무한 루프 방지)

        const int calc[3] = {1, -1, curr_pos}; // 세 가지 연산
        for (int i = 0; i < 3; i++)
        {
            int next_pos = curr_pos + calc[i]; // 다음 위치는 i번쨰 연산을 통한 위치

            if (!(0 <= next_pos && next_pos <= MAX) || visited[next_pos].cnt != 0) // 만약 정해진 위치를 벗어났거나, 이미 탐색한 장소일 경우 다음 위치를 탐색 (이미 탐색한 곳을 재탐색할 경우, 무한 루프)
                continue;

            visited[next_pos].cnt = visited[curr_pos].cnt + 1; // 현재 위치까지의 카운트에 +1
            visited[next_pos].prev_pos = curr_pos;             // 다음 위치에 현재 위치를 저장함 (= 현재 위치에서 다음 위치로 이동)

            q.push(next_pos);
        }
    }
}

void backtrace(const int start, int idx) // idx에서 start까지 역추적
{
    if (idx == start) // 도착한 경우
    {
        cout << start << " ";
        return;
    }

    // if (idx != start)
    backtrace(start, visited[idx].prev_pos); // 이전 위치들을 찾아감
    cout << idx << " ";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int start, end;      // 시작점 및 도착점
    cin >> start >> end; // 0 <= 100k

    BFS(start, end); // BFS를 이용하여 목적지까지의 연산 횟수와 방문한 장소들을 구함

    cout << visited[end].cnt << endl; // 목적지까지의 횟수 출력
    backtrace(start, end);            // 저장이 뒤로 되어있기 때문에 backtrace 실행하여 출력
}