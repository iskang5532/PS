// 2022-11-19
// 21276 계보 복원가 호석
// https://www.acmicpc.net/problem/21276
/*
    위상정렬, 맵 (5,132KB, 256ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 이용하여 그래프를 구성하기엔 불편하므로, {문자열, 숫자}로 이루어진 맵을 이용하여 숫자로 변환하여 사용.
    conv_s[]에는 입력된 문자열을 숫자로, conv_i[]는 변환된 숫자를 문자열로 변환.
    - 자식 여부까지 알아야 하므로, 시조를 기준으로 bfs를 수행.
    - 자식(후대)의 수를 저장할 in_degree[].
    - bfs를 이용하여 자식을 구하며, 구한 자식은 childs[]에 저장.
    저장 시, conv_i를 이용하여 문자열로 변환 후 저장.
    in_degree == 0일 경우 시조가 됨.
    - conv_s에 저장된 값은 정렬된 상태임. 맵의 key인 문자열을 기준으로 오름차순 정렬이 되어 있으므로, 부모와 자식을 출력할 때 사용.
    etc.) 부모의 자식을 어떻게 구해야 하는지 몰랐는데, 참고 사이트를 통해 시작점을 시조로 잡으면 해결됨을 알아냄
    참고)
    - 트리 역발상: https://blog.naver.com/jinhan814/222342237665
 */

#include <iostream>
#include <map>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'003 // max n

vector<int> adj[MAX];
int in_degree[MAX];                // in_degree[i] = k일 경우, 자식(후대)의 수는 k
vector<string> sijos, childs[MAX]; // childs[i] = {s1, s2}일 경우, i번의 자식은 s1, s2
map<string, int> conv_s;           // 문자열을 번호로 변환
map<int, string> conv_i;           // 변환된 번호를 문자열로 변환

void bfs(int n)
{
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0) // 시조인가?
            q.push(i), sijos.push_back(conv_i[i]);

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (const int &next : adj[cur])
            if (--in_degree[next] == 0)
                q.push(next), childs[cur].push_back(conv_i[next]); // 부모에게 자식 추가
    }
}

void print_ans();
int main()
{
    FAST_IO;

    int n; // 가문의 수 (1 ≤ N ≤ 1,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        conv_s[s] = conv_s.size(), conv_i[conv_s.size() - 1] = s;
    }

    int m; // 정보의 개수 (0 ≤ M ≤ N×(N-1)/2)
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string x, y; // 자식 x, 조상 y
        cin >> x >> y;

        int _x = conv_s[x], _y = conv_s[y];
        adj[_y].push_back(_x), in_degree[_x]++;
    }

    bfs(n);

    print_ans();
}

void print_ans()
{
    sort(sijos.begin(), sijos.end());

    cout << sijos.size() << endl;
    for (const string &sijo : sijos)
        cout << sijo << ' ';
    cout << endl;

    for (const auto &[parent, pos] : conv_s)
    {
        sort(childs[pos].begin(), childs[pos].end());

        cout << parent << ' ' << childs[pos].size() << ' ';
        for (const string &child : childs[pos])
            cout << child << ' ';
        cout << endl;
    }
}