/*
    카카오프렌즈 컬러링북 (코딩테스트 연습 > 2017 카카오코드 예선 > 카카오프렌즈 컬러링북)
    BFS
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/1829?language=cpp
    etc.)
    - 모든 칸을 조사함.
    1) 현재 위치의 색을 받음. (첫 위치는 (0, 0))
     - 칸의 색이 1 이상인 경우, 영역의 개수를 +1.
     - 칸의 색이 0인 경우, 기준을 다른 칸으로 옮기며 1)부터 재수행.
    2) 현재 칸과 인접한 칸을 조사함.
     - 현재 칸과 인접한 칸의 색이 같은 경우, 발견한 칸의 인접한 칸을 탐색시키며 영역의 크기 +1.
        또한, 다음에 중복된 탐색을 하지 않도록 기록해줘야 함 (여기서는 visited[][])
     - 인접한 칸과의 색이 다른 경우, 다른 인접한 칸을 살피며 모든 칸을 살폈을 시 구한 영역의 크기를 반환하며 기준을 다른 칸으로 옮긴 뒤 1)부터 수행.

 */

#include <string>
#include <queue>

using namespace std;

#define MAX 100 + 1
typedef pair<int, int> pii;

const int dim_col[4] = {0, 1, 0, -1};
const int dim_row[4] = {-1, 0, 1, 0};

bool visited[MAX][MAX];

int get_size(const vector<vector<int>> &picture, int m, int n, int i, int j)
{
    queue<pii> q;
    q.push(pii{i, j});
    visited[i][j] = true;

    int _size = 1;
    while (!q.empty())
    {
        auto [row, col] = q.front();
        q.pop();

        int curr = picture[row][col];
        for (int i = 0; i < 4; i++)
        {
            int next_col = col + dim_col[i];
            int next_row = row + dim_row[i];

            if (!(0 <= next_col && next_col < n) || !(0 <= next_row && next_row < m)) // 범위
                continue;
            if (visited[next_row][next_col]) // 방문 이력
                continue;
            if (picture[next_row][next_col] != curr) // 값이 같은가
                continue;

            visited[next_row][next_col] = true;
            q.push(pii{next_row, next_col});
            _size++;
        }
    }

    return _size;
}

vector<int> solution(int m, int n, vector<vector<int>> picture)
{
    int number_of_area = 0;
    int max_size_of_one_area = 0;

    for (int i = 0; i < m; i++)
        fill(visited[i], visited[i] + MAX, false); // 전역 변수 초기화
    for (int row = 0; row < m; row++)
        for (int col = 0; col < n; col++)
            if (picture[row][col] && visited[row][col] == false) // 0이 아니면서 방문한 적이 없는 경우
                max_size_of_one_area = max(max_size_of_one_area, get_size(picture, m, n, row, col)), number_of_area++;

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     auto vec = solution(6, 4,
//                         {{1, 1, 1, 0},
//                          {1, 2, 2, 0},
//                          {1, 0, 0, 1},
//                          {0, 0, 0, 1},
//                          {0, 0, 0, 3},
//                          {0, 0, 0, 3}});
//     cout << vec.front() << " " << vec.back(); // 4 5
// }