// 2022-12-20
// 7432 디스크 트리
// https://www.acmicpc.net/problem/7432
/*
    sol.1) 트라이 (4,796KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 입력된 디렉토리를 폴더로 나눈 후, 트라이 구조인 root에 폴더를 저장.
    이후, 저장된 폴더를 출력 형식에 맞춰 출력.
    1. 입력된 디렉토리 dir에 있는 '\'를 찾아내어 폴더를 쪼갠 후, folders에 저장.
    2. folders에 저장된 폴더를 root에 저장.
    이때, 맵 m을 사용하여 중복을 제거하며, 폴더 속에 또 다른 폴더를 추가할 수 있도록 만듦.
    - 현재 추가할 폴더인 folders[pos]가 m에 존재하는지 확인.
    만약 존재하지 않을 경우, 새로운 폴더를 추가.
    - 현재 폴더가 folders의 마지막이 아닌 경우, 다음 폴더를 현재 폴더 안에 추가.
    이후 반복.
    3. 문제의 출력 형식에 맞춰 출력.
    맵은 키 값(폴더)을 기준으로 오름차순 정렬이 되므로, 별다른 정렬 없이 맵에 저장된 값을 출력해줌.
    이때, 깊이에 따라 들여쓰기를 해줘야 하므로 indent 변수를 이용함.
    만약 폴더 안에 다른 폴더가 존재할 경우, 현재 indent + 1의 값과 함께 다음 폴더를 출력.
    etc.)
    - 단순히 맵 혹은 정규 표현식을 이용한 문제일 듯싶었으나, TLE가 날 것 같아서 다른 풀이를 떠올림
    - 트라이를 떠올린 이후로는 의외로 쉽게 풀린 문제.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

struct Node
{
    map<string, Node *> m; // {폴더, 폴더 속 폴더}

    void add(const vector<string> &folders, int pos = 0) // 폴더들(디렉토리) 추가
    {
        string folder = folders[pos]; // pos번 폴더

        if (m.find(folder) == m.end()) // 동일한 이름의 폴더가 없는 경우 (= 이전에 저장한 적이 없음)
            m[folder] = new Node;      // 새로운 폴더 추가

        if (pos + 1 == folders.size()) // 마지막 폴더인 경우, 종료
            return;
        m[folder]->add(folders, pos + 1); // 다음 폴더를 추가
    }

    void print(int indent = 0) // 디렉토리 구조를 출력; 들여쓰기의 개수 indent
    {
        for (const auto &[s, idx] : m)
        {
            for (int i = 0; i < indent; i++)
                cout << ' ';
            cout << s << endl;

            m[s]->print(indent + 1); // 폴더 안에 저장된 다른 폴더 출력
        }
    }
} root;

vector<string> get_folders(const string &dir) // 디렉토리를 폴더로 나눔
{
    vector<string> folders;

    int prev = 0, pos = -1; // 이전 역슬래시의 위치+1인 prev, 역슬래시의 위치 pos
    while ((pos = dir.find('\\', prev + 1)) != string::npos)
        folders.push_back(string(dir.begin() + prev, dir.begin() + pos)), prev = pos + 1;
    folders.push_back(string(dir.begin() + prev, dir.end())); // 마지막 역슬래시 이후의 폴더

    return folders;
}

int main()
{
    FAST_IO;

    int n; // 경로의 개수 (1 ≤ n ≤ 500)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string dir;
        cin >> dir;

        vector<string> folders = get_folders(dir); // 1. 폴더들 구하기

        root.add(folders); // 2. root에 폴더들 추가
    }

    root.print(); // 3. 출력
}

/*
    sol.2) (81,334KB, 80ms)
    시간 복잡도: ?
    etc.) 트라이의 첫 번째 풀이
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 503 // max n

struct Node
{
    map<string, int> m; // {폴더의 이름, 폴더의 위치(next[])}
    Node *next[MAX];

    void add(const vector<string> &folders, int cur = 0) // 폴더들(디렉토리) 추가
    {
        string folder = folders[cur]; // pos번 폴더

        int pos = -1; // 맵에 존재하는 문자열의 값(= 위치)

        auto itr = m.find(folder);
        if (itr == m.end()) // 동일한 이름의 폴더가 없는 경우 (= 이전에 저장한 적이 없음)
        {
            pos = m[folder] = m.size(); // 폴더의 위치를 저장
            next[pos] = new Node;       // 새로운 폴더 추가
        }
        else // 폴더가 존재할 경우, 저장된 위치를 가져옴
            pos = (*itr).second;

        if (cur + 1 == folders.size()) // 마지막 폴더인 경우, 종료
            return;

        next[pos]->add(folders, cur + 1); // 다음 폴더를 추가
    }

    void print(int indent = 0) // 디렉토리 구조를 출력; 들여쓰기의 개수 indent
    {
        for (const auto &[s, idx] : m)
        {
            for (int i = 0; i < indent; i++)
                cout << ' ';
            cout << s << endl;

            next[i]->print(indent + 1); // 폴더 안에 저장된 다른 폴더 출력
        }
    }
} trie;

vector<string> get_folders(const string &dir) // 디렉토리를 폴더로 나눔
{
    vector<string> folders;

    int prev = 0, pos = -1; // 이전 역슬래시의 위치+1인 prev, 역슬래시의 위치 pos
    while ((pos = dir.find('\\', prev + 1)) != string::npos)
        folders.push_back(string(dir.begin() + prev, dir.begin() + pos)), prev = pos + 1;
    folders.push_back(string(dir.begin() + prev, dir.end())); // 마지막 역슬래시 이후의 폴더

    return folders;
}

int main()
{
    FAST_IO;

    int n; // 경로의 개수 (1 ≤ n ≤ 500)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string dir;
        cin >> dir;

        vector<string> folders = get_folders(dir); // 1. 폴더들 구하기

        trie.add(folders); // 2. root에 폴더들 추가
    }

    trie.print();
}