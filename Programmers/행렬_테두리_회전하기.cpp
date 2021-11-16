/*
    행렬 테두리 회전하기 (코딩테스트 연습 > 2021 Dev-Matching: 웹 백엔드 개발자(상반기) > 행렬 테두리 회전하기)
    구현
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/77485
    풀이)
    - 2차원 배열을 arr[x][y]로 구현. (차후 이 풀이를 볼 때 헷갈리지 않도록 주의.)
    - 배열을 시계 방향으로 돌릴 때의 순서는 상, 좌, 하, 우. (자세한 것은 코드 밑에 주석으로)
    돌리며 값을 하나씩 대입하게 되는데, 그 과정에서 값을 읽음. 그렇기에 읽으면서 최솟값을 구해줌.
    etc.)
    - 입력이 (x1, y1, x2, y2)라고 적혀 있는데 기존에 알고 있던 x와 y가 반대 상황의 입력이여서 헷갈렸음.
 */

#include <vector>
using namespace std;
#define INF 123456789

struct pii
{
    int row, col;
};

vector<int> solution(int rows, int columns, vector<vector<int>> queries)
{
    vector<int> answer;
    vector<vector<int>> arr(columns + 1, vector<int>(rows + 1));
    for (int i = 0; i < rows * columns; i++)
        arr[1 + i % columns][1 + i / columns] = 1 + i;

    for (const auto &v : queries)
    {
        int mn = INF;
        pii p1 = {v[0], v[1]}, p2 = {v[2], v[3]}; // 두 좌표

        int idx = arr[p2.col][p1.row];        // 회전 시에 사라질 값 하나를 저장 (이 풀이에서는 [p2.col][p1.row]. 위에서부터 이동시키기 때문)
        for (int i = p2.col; i > p1.col; i--) // 상
            arr[i][p1.row] = arr[i - 1][p1.row], mn = min(mn, arr[i][p1.row]);
        for (int i = p1.row; i < p2.row; i++) // 좌
            arr[p1.col][i] = arr[p1.col][i + 1], mn = min(mn, arr[p1.col][i]);
        for (int i = p1.col; i < p2.col; i++) // 하
            arr[i][p2.row] = arr[i + 1][p2.row], mn = min(mn, arr[i][p2.row]);
        for (int i = p2.row; i > p1.row + 1; i--) // 우
            arr[p2.col][i] = arr[p2.col][i - 1], mn = min(mn, arr[p2.col][i]);
        arr[p2.col][p1.row + 1] = idx, mn = min(mn, idx);

        answer.push_back(mn);
    }
    return answer;
}

// #include <iostream>
// #define endl "\n"
// void print_ans(const vector<int> &ans);
// int main()
// {
//     print_ans(solution(6, 6, {{2, 2, 5, 4}, {2, 2, 5, 4}, {2, 2, 5, 4}}));               // 8 8 8
//     print_ans(solution(6, 6, {{2, 2, 5, 4}, {3, 3, 6, 6}, {5, 1, 6, 3}}));               // 8 10 25
//     print_ans(solution(3, 3, {{1, 1, 2, 2}, {1, 2, 2, 3}, {2, 1, 3, 2}, {2, 2, 3, 3}})); // 1 1 5 3
//     print_ans(solution(100, 97, {{1, 1, 100, 97}}));                                     //	1
//     print_ans(solution(5, 5, {{1, 1, 5, 5}, {1, 1, 5, 5}}));                             //	1 1
// }
// void print_ans(const vector<int> &ans)
// {
//     for (const auto &elem : ans)
//         cout << elem << " ";
//     cout << endl;
// }

// rows = 3, columns = 3에서의 회전.
// 설명에 -라고 적혀 있는 부분은 값은 존재하지만, 보기 편하도록 제거시켰음.
//    1 2 3
//    4 5 6
//    7 8 9

// 0) idx = 3
// 1) - 1 2     // 상
//    4 5 6
//    7 8 9

// 2) 4 1 2     // 좌
//    7 5 6
//    - 8 9

// 3) 4 1 2     // 하
//    7 5 6
//    8 9 -

// 4) 4 1 2     // 우
//    7 5 -
//    8 9 6

// 5) 4 1 2   // idx 삽입
//    7 5 3
//    8 9 6