// 5639 이진 검색 트리
// https://www.acmicpc.net/problem/5639
/*
    sol.1) 트리, 재귀 (10,024KB, 752ms)
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

using pii = pair<int, int>; // {left, right}

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

void postorder(int root)
{
    if (node[root].LEFT != INF)
        postorder(node[root].LEFT);
    if (node[root].RIGHT != INF)
        postorder(node[root].RIGHT);

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

    postorder(root);
}

/*
    sol.2) 트리, 재귀 (2,252KB, 24ms)
    시간 복잡도: ?
    풀이)
    - 최상위 노드와 값을 비교하여, 큰 값들이 모여 있는 우측 부분을 찾음.
    이를 이용하면 좌측의 값을 우선적으로 확인할 수 있게 되며, 후위 순회를 만들 수 있게 된다.
    - 우측 부분 노드들의 값은 최상위 노드의 값보다 클 것이며, 순서(= cnt) 또한 클 것이다. (입력은 전위 순회이므로)
    그러므로 위와 같은 풀이가 가능해진다.
    etc.) 입력이 전위 순회여서 가능한 풀이인듯
    - mid를 hi부터 탐색하는게 아닌 lo부터 탐색하여 구해보려 했지만 실패. 불가능한가?
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 10'000 + 1 // 노드의 최대 개수

int node[MAX];

void postorder(int lo, int hi)
{
    if (lo > hi)
        return;

    int root = node[lo];
    int mid = hi;
    while (node[mid] > root) // 최상위 노드보다 큰 값, 즉 우측 값들의 범위를 탐색
        mid--;

    postorder(lo + 1, mid);
    postorder(mid + 1, hi);

    cout << root << endl;
}

int main()
{
    FAST_IO;

    int num, cnt = 0;
    while (cin >> num)
        node[cnt] = num, cnt++;

    postorder(0, cnt - 1);
}

// 입력 종료: Ctrl + Z