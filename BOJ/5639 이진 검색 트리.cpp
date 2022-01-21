// 5639 이진 검색 트리
// https://www.acmicpc.net/problem/5639
/*
    sol.1) 트리, 재귀 (100,24KB, 752ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 이용한 풀이. (값의 범위는 노드의 수보다 많으며, 메모리 사용량이 높음.)
    - 값이 입력될 때마다, 해당 값의 위치를 찾아줌.
    첫 번째 값은 최상위 노드이므로, 이후 입력된 값은 최상위 노드에서부터 탐색.
    만약 최상위 노드보다 작은 경우, 최상위 노드의 왼쪽 값(= [root].LEFT)을 최상위 노드로 가진 후 재탐색.
    만약 최상위 노드보다 큰 경우, 최상위 노드의 오른쪽 값(= [root].RIGHT)을 최상위 노드로 가진 후 재탐색.
    만약 해당 노드의 값이 INF일 경우, 노드의 위치에 값을 추가.
    - 출력 시, [좌측 - 우측 - 루트] 순으로 출력해줌.
    etc.) 유니온 파인드 느낌인듯
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
#define MAX 1'000'000 + 1 // 키의 최댓값 10^6
#define LEFT first
#define RIGHT second

using pii = pair<int, int>;

pii node[MAX];

void added(int num, int root) // num != root
{
    if (num < root) // 왼쪽
    {
        if (node[root].LEFT == INF)
            node[root].LEFT = num;
        else
            added(num, node[root].LEFT);
    }
    else // 오른쪽
    {
        if (node[root].RIGHT == INF)
            node[root].RIGHT = num;
        else
            added(num, node[root].RIGHT);
    }
}

void preorder(int root)
{
    if (node[root].LEFT != INF)
        preorder(node[root].LEFT);
    if (node[root].RIGHT != INF)
        preorder(node[root].RIGHT);

    cout << root << endl;
}

int main()
{
    FAST_IO;

    int num;
    cin >> num;

    fill(&node[0], &node[0] + sizeof(node) / sizeof(node[0]), pii{INF, INF});

    int root = num;
    while (cin >> num)
        added(num, root);

    preorder(root);
}

// 입력 종료: Ctrl + Z