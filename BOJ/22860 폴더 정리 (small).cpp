// 2022-12-28
// 22860 폴더 정리 (small)
// https://www.acmicpc.net/problem/22860
/*
    트라이, bfs (2,720KB, 196ms)
    시간 복잡도: ?
    풀이)
    - 트라이를 만든 후, 폴더 혹은 파일을 저장.
    트라이 안에는 폴더를 저장할 맵 folder, 파일을 저장할 셋 files가 존재.
    - 입력받은 p와 f, c를 M에 저장. (M에는 상위 폴더와 하위 폴더 혹은 파일의 상하 관계를 저장)
    이후, 사전에 저장한 M의 값을 이용하여 "main" 폴더를 트라이 안에 추가.
    M["main"] 안에는 main 하위의 폴더 혹은 파일이 존재할 것이며, 이를 꺼내어 folder 혹은 files에 저장.
    - 입력된 쿼리에서 '/'를 제거하여 폴더로 변환 후 v에 저장하여 사용.
    - 트라이에서 v에 저장된 폴더를 따라 이동하여 마지막 폴더를 st에 저장.
    이후, bfs를 이용하여 st에 저장된 폴더 혹은 파일을 탐색.
    etc.) 의외로 엄청 어려웠는데, 쉽다는 평이 있는듯
 */

#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define FOLDER 1
#define FILE 0

map<string, map<string, int>> M; // M[folder][name] = FILE일 경우, 폴더 folder안에 이름이 name이 존재하며, 타입은 FILE.

struct Node
{
    map<string, Node *> folder;
    set<string> files;

    void add(const string &cur, int _type)
    {
        for (const auto &[child, _type] : M[cur])
            if (_type == FOLDER)
            {
                if (folder.find(child) == folder.end()) // 폴더가 생성된 적이 없는 경우
                    folder[child] = new Node;
                folder[child]->add(child, _type); // 자식 폴더 추가
            }
            else if (_type == FILE)
                files.insert(child); // 파일 추가
    }
    pii get_cnt(const vector<string> &v)
    {
        auto st = this; // in main
        for (int i = 1; i < v.size(); i++)
            st = st->folder[v[i]]; // 입력된 쿼리의 마지막 폴더로 이동

        set<string> total;
        int cnt = 0;

        queue<Node *> q;
        q.push(st);
        while (q.size())
        {
            auto cur = q.front(); // 현재 탐색중인 폴더
            q.pop();
            for (const string &file : cur->files) // 폴더 속 파일 확인
                total.insert(file), cnt++;
            for (const auto &[idx, next] : cur->folder) // 폴더 속 다른 폴더 확인
                q.push(next);
        }

        return {total.size(), cnt};
    }
} root; // folder main

vector<string> get_folders(const string &dir) // 문자열을 폴더로 나눔
{
    vector<string> ret;
    int pos = -1, prev = 0;
    while ((pos = dir.find("/", prev + 1)) != string::npos)
        ret.push_back(string(dir.begin() + prev, dir.begin() + pos)), prev = pos + 1;
    ret.push_back(string(dir.begin() + prev, dir.end()));

    return ret;
}

int main()
{
    FAST_IO;

    int n, m; // 폴더의 총 개수 n(1 ≤ n ≤ 1,000), 파일의 총 개수 m(1 ≤ m ≤ 1,000)
    cin >> n >> m;
    for (int i = 0; i < n + m; i++)
    {
        string parent, child;
        int _type;
        cin >> parent >> child >> _type;

        M[parent][child] = _type;
    }

    root.add("main", FOLDER); // 메인 폴더와 함께 입력된 폴더와 파일 추가

    int q; // 쿼리의 개수 (1 ≤ q ≤ 1,000)
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        string dir;
        cin >> dir;

        vector<string> v = get_folders(dir);

        auto [a, b] = root.get_cnt(v);

        cout << a << ' ' << b << endl;
    }
}