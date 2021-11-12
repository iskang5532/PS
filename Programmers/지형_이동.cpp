/*
    지형 이동 (코딩테스트 연습 > Summer/Winter Coding(2019) > 지형 이동)
    유니온 파인드, MST(최소 신장 트리, 크루스칼 알고리즘), BFS
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/62050
    풀이)
    1) BFS를 이용하여 구역의 영역을 나눠줌 (예제의 색별로 나누는 것과 동일)
    - 인접한 두 구역의 높이 차이가 주어진 height와 비교하여 더 작은 경우, 같은 구역으로 취급.
    2) 서로 다른 구역간 인접한 지형(= 칸)을 모두 구함. (= arr)
    3) 구해진 arr를 MST를 이용하여 풀이. (모든 구역을 연결했을 때 드는 가장 적은 비용을 구해야 함)
    - arr를 비용을 기준으로 오름차순 정렬을 함.
    - 각 구역마다 연결하며, 연결 시에 드는 비용을 저장함.
    - 최종적으로 구해진 비용을 출력.
    etc.) 여러 알고리즘을 알고 있어야 하며, 응용할 줄 알아야 했던 문제. 다익스트라 비슷하게 풀려고 했으나 실패했음.
    참고)
    - 유니온 파인드 이론: https://m.blog.naver.com/ndb796/221230967614
    - 풀이 이론: https://velog.io/@front/%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4-%EC%A7%80%ED%98%95-%EC%9D%B4%EB%8F%99
                https://yabmoons.tistory.com/470
 */

#include <queue>
#include <algorithm> // sort

using namespace std;

typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; // 위, 오, 아, 왼
const int dy[4] = {-1, 0, 1, 0};

int n; // 지형의 크기

struct P // 구역간 사다리의 비용을 저장할 변수
{
    int a, b, c; // 두 구역 a, b 및 사다리의 비용
};
bool _greater_c(const P &p1, const P &p2) { return p1.c < p2.c; } // 사다리의 비용을 기준으로 오름차순 정렬

struct Union_Find
{
    vector<int> parent;

    Union_Find(int n) // 벡터 초기화
    {
        parent.resize(n + 1, 0);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    int find_parent(int x) { return x == parent[x] ? x : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[b] = a; } // 두 구역 연결
};

vector<vector<int>> bfs(const vector<vector<int>> &land, int height)
{
    vector<vector<int>> visited(n, vector<int>(n, 0)); // 각 지형(= 칸)의 구역을 저장

    int cnt = 1; // 구역의 번호
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!visited[i][j]) // 방문한 적이 없는 경우 (= 구역이 정해지지 않음)
            {
                queue<pii> q;
                q.push({i, j});
                visited[i][j] = cnt;

                while (!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();

                    for (int i = 0; i < 4; i++) // 인접한 다음 지형
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (!(0 <= nx && nx < n) || !(0 <= ny && ny < n)) // 범위
                            continue;
                        if (visited[nx][ny] == cnt) // 같은 구역인 경우 (= 앞서 탐색했던 지형이며, (nx, ny)에서 가는 다른 지형 또한 앞서 탐색 완료)
                            continue;

                        int gap = abs(land[x][y] - land[nx][ny]); // 지형간 높이의 차이 (= 사다리 설치 비용)
                        if (height < gap)                         // 사다리가 필요한 경우 (= 다른 구역)
                            continue;

                        visited[nx][ny] = cnt; // 현재 지형의 구역을 지정
                        q.push({nx, ny});
                    }
                }

                cnt++;
            }

    return visited;
}

int solution(vector<vector<int>> land, int height)
{
    n = land.size();

    auto visited = bfs(land, height); // 각 지형마다 구역을 지정함

    int mx = 0; // 구역의 마지막 번호 (유니온 파인드에 사용)
    vector<P> arr;
    for (int x = 0; x < n; x++) // 구역간 인접한 지형과 높이 차이를 구함
        for (int y = 0; y < n; y++)
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!(0 <= nx && nx < n) || !(0 <= ny && ny < n)) // 범위
                    continue;

                mx = max(mx, visited[x][y]);
                if (visited[x][y] != visited[nx][ny]) // 구역이 다른 경우, 각 지형의 위치와 사다리 설치 비용을 저장
                    arr.push_back(P{visited[x][y], visited[nx][ny], abs(land[x][y] - land[nx][ny])});
            }
    sort(arr.begin(), arr.end(), _greater_c); // 사다리 설치 비용을 기준으로 오름차순 정렬

    int ans = 0;
    Union_Find uf(mx);
    for (auto [a, b, c] : arr)
    {
        a = uf.find_parent(a), b = uf.find_parent(b);
        if (a != b)
            uf.union_parent(a, b), ans += c; // 사다리 연결 및 비용 추가
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution({{1, 4, 8, 10}, {5, 5, 5, 5}, {10, 10, 10, 10}, {10, 10, 10, 20}}, 3) << endl;  //	15
//     cout << solution({{10, 11, 10, 11}, {2, 21, 20, 10}, {1, 20, 21, 11}, {2, 1, 2, 1}}, 1) << endl; // 18
// }