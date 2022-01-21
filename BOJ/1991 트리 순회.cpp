// 1991 트리 순회
// https://www.acmicpc.net/problem/1991
/*
    트리, 재귀 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자 a의 두 자식들을 v에 저장.
    - 최상위 루트는 'A'이므로, 'A'의 자식들을 확인해가며 출력함. (자식이 '.'일 경우, 반환)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

pair<char, char> v[26]; // v[0] = {B, C}일 경우, 'A'의 왼쪽 자식은 'B', 오른쪽 자식은 'C'

void preorder(char root) // 전위 순회 (부모 - 좌측 - 우측)
{
    if (root == '.')
        return;

    auto [left, right] = v[root - 'A'];

    cout << root;
    preorder(left);
    preorder(right);
}

void inorder(char root) // 중위 순회 (좌측 - 부모 - 우측)
{
    if (root == '.')
        return;

    auto [left, right] = v[root - 'A'];

    inorder(left);
    cout << root;
    inorder(right);
}

void postorder(char root) // 후위 순회 (좌측 - 우측 - 부모)
{
    if (root == '.')
        return;

    auto [left, right] = v[root - 'A'];

    postorder(left);
    postorder(right);
    cout << root;
}

int main()
{
    FAST_IO;

    int n; // 노드의 개수 (1 ≤ n ≤ 26)
    cin >> n;

    fill(&v[0], &v[0] + sizeof(v) / sizeof(v[0]), pair<char, char>{'.', '.'});

    for (int i = 0; i < n; i++)
    {
        char a, b, c;
        cin >> a >> b >> c;

        v[a - 'A'] = {b, c};
    }

    preorder('A');
    cout << endl;
    inorder('A');
    cout << endl;
    postorder('A');
    cout << endl;
}