// 2022-12-14
// 1414 불우이웃돕기
// https://www.acmicpc.net/problem/1414
/*
    MST, 크루스칼 (2,168KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 컴퓨터 간 랜선의 길이를 기준으로 오름차순 정렬.
    이후, 랜선이 작은 값을 우선적으로 사용.
    입력되는 컴퓨터 간 랜선은 두 개이므로, 둘 중 최솟값을 이용함.
    - 두 컴퓨터 a, b, 길이 k가 있을 때, a와 b가 연결되었는지 확인.
    만약 연결되지 않았을 경우, 두 컴퓨터를 연결하는 랜선의 길이 k를 mn에 저장. (mn은 컴퓨터를 연결할 때 사용한 랜선의 길이를 저장)
    이때, k가 0일 수 있음. 이때는 컴퓨터를 연결할 수 없으므로 제외.
    - 유니온 파인드를 이용하여 위 과정을 구현.
    etc.)
    - 요상한 방법으로 풀어보려다가 실패.
    - 풀이가 생각나지 않아서 알고리즘 분류 확인.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n
#define INF 0x3f3f3f3f

int board[MAX][MAX]; // board[i][j] = k일 경우, i에서 j로 연결하는 랜선의 길이는 k (board[j][i]와는 다를 수 있음)

struct P
{
    int a, b, k;
    friend bool operator<(const P &p1, const P &p2) { return p1.k < p2.k; } // 랜선의 길이를 기준으로 오름차순 정렬
};

struct Union_Find
{
    int parent[MAX];

    Union_Find() { iota(parent, parent + MAX, 0); }

    int find_parent(int x) { return x == parent[x] ? parent[x] : parent[x] = find_parent(parent[x]); }
    void union_parent(int a, int b) { a < b ? parent[b] = a : parent[a] = b; } // 두 컴퓨터를 연결
} uf;

int main()
{
    FAST_IO;

    int n; // 컴퓨터의 개수 (1 ≤ n ≤ 50)
    cin >> n;

    int sum = 0; // 모든 랜선 길이의 합
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
        {
            char c;
            cin >> c;
            int k = islower(c)   ? c - 'a' + 1  // 소문자
                    : isupper(c) ? c - 'A' + 27 // 대문자
                                 : INF;         // '0'
            board[y][x] = k, (k != INF ? sum += k : '\0');
        }

    vector<P> v; // 컴퓨터를 연결하는 랜선의 정보를 저장 (v[i] = {a, b, k}일 경우, a와 b를 연결하는 랜선의 길이는 k)
    for (int y = 1; y < n; y++)
        for (int x = 0; x < y; x++)
            v.push_back({y, x, min(board[y][x], board[x][y])}); // 두 랜선 중 짧은 것을 저장

    sort(v.begin(), v.end());

    int mn = 0, cnt = 0; // 컴퓨터를 연결할 때 사용한 랜선의 길이 mn, 사용한 랜선의 개수 cnt
    for (int i = 0; i < v.size(); i++)
    {
        auto [a, b, k] = v[i];
        if (k == INF) // 랜선의 길이가 0일 경우
            continue;

        a = uf.find_parent(a), b = uf.find_parent(b);
        if (a != b) // 두 컴퓨터가 연결되어 있지 않은 경우
        {
            uf.union_parent(a, b);
            mn += k, cnt++;
        }
    }

    cout << (cnt == n - 1 ? sum - mn : -1); // 필요한 개수만큼 사용하였는가?
}

// input:
// 9
// adfdsAdas
// AdsfwfRTQ
// awfqqPOIs
// adwoqeLLL
// aldPpoOOI
// WQDlwodkf
// QOWIEkals
// Aodowkfq0
// ans:
// 1421