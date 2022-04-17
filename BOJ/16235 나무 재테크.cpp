// 2022-04-15
// 16235 나무 재테크
// https://www.acmicpc.net/problem/16235
/*
    구현 (2,028KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 봄에 죽어 여름에 양분이 되는 나무를 저장할 dead.
    죽은 나무를 하나씩 탐색할 경우 TLE. 그러므로 양분의 양을 dead에 저장한 후, 한 번에 추가.
    - Autumn()에서 tree의 값을 가져와 새로운 나무를 구하여 tree에 넣는다. 이때, tree에 값이 추가됨에 따라 트리의 메모리 위치가 바뀔 수 있음.
    그러므로, 값을 가져올 때 참조하거나 할 경우 값이 변경될 수 있음에 주의.
    참고)
    - 죽은 나무의 양분에 대해: https://www.acmicpc.net/board/view/78741
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 13 // max n

constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 북에서부터 시계방향
constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

struct P
{
    int y, x, age; // 나무의 위치 y,x, 나무의 나이 age(1 ≤ age ≤ 10)

    friend bool operator<(const P &p1, const P &p2) { return p1.age < p2.age; }; // 나이 기준 오름차순 정렬
};

int n, m, k;     // 땅의 크기 n(1 ≤ n ≤ 10), 나무의 개수 m(1 ≤ m ≤ N^2), 시간 k(1 ≤ k ≤ 1,000)
int A[MAX][MAX]; // 추가되는 양분 (1 ≤ A[r][c] ≤ 100)
vector<P> tree;
int board[MAX][MAX], dead[MAX][MAX]; // 현재 땅의 양분의 양 board, 여름에 추가될 양분의 양 dead

void Spring()
{
    sort(tree.begin(), tree.end()); // 나이 기준 오름차순 정렬

    vector<P> temp;
    for (int i = 0; i < tree.size(); i++)
    {
        const auto &[y, x, age] = tree[i];
        if (age <= board[y][x])
            board[y][x] -= age, temp.push_back({y, x, age + 1});
        else
            dead[y][x] += age / 2;
    }
    tree = temp;
}

void Summer()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] += dead[i][j], dead[i][j] = 0;
}

void Autumn()
{
    int sz = tree.size();
    for (int i = 0; i < sz; i++)
    {
        const auto [y, x, age] = tree[i];

        if (age % 5 == 0) // 5의 배수
            for (int d = 0; d < 8; d++)
            {
                const auto &[ny, nx] = pii{y + dy[d], x + dx[d]};
                if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                    continue;

                tree.push_back({ny, nx, 1});
            }
    }
}

void Winter()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] += A[i][j];
}

int main()
{
    FAST_IO;

    cin >> n >> m >> k;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            cin >> A[r][c];

    for (int i = 0; i < m; i++)
    {
        int y, x, age;
        cin >> y >> x >> age;
        tree.push_back({y - 1, x - 1, age});
    }

    fill(&board[0][0], &board[0][0] + MAX * MAX, 5);
    while (k--)
    {
        Spring();
        Summer();
        Autumn();
        Winter();
    }

    cout << tree.size();
}