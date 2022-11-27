// 2022-11-25
// 23059 리그 오브 레게노
// https://www.acmicpc.net/problem/23059
/*
    위상정렬 (54,380KB, 620ms)
    시간 복잡도: ?
    풀이)
    - 입력이 문자열이므로, 문자열과 숫자끼리 서로 쉽게 변환할 수 있도록 conv를 생성 후 저장. (단순 숫자 부여 x. 밑에서 추가 설명)
    - in_degree[]에 선행 아이템의 개수를 저장.
    - 출력할 값은 오름차순 정렬된 상태여야 하며, 구매 순서 또한 따져야함.
    그러므로, 값을 이용하여 인접한 값을 탐색할 때 문자열과 구매 순서(구매 단계?)를 비교할 수 있는 pq를 이용. (순서를 먼저 비교, 같을 경우 값을 비교)
    이때, pq의 cmp 함수에서 정렬 때마다 문자열을 비교하게 될 경우 TLE.
    그러므로 conv된 값을 이용해야 하며, conv 또한 까다롭게 변환해야 함.
    단순히 입력된 문자열을 임의의 숫자로 변환하는게 아닌, 변환 과정에서 오름차순 정렬이 된 문자열에 숫자를 부여하여 숫자의 오름차는 문자열의 오름차가 되게끔 해줌.
    - pq에 있는 값을 빼내 탐색 및 ans에 저장.
    - ans에 저장된 값의 개수외 conv에 저장된 값의 개수를 비교. (conv에 저장된 값은 중복이 제거된 모든 아이템이며, ans 또한 모든 아이템이 저장되어 있어야 함)
    만약 같을 경우, conv를 이용하여 값을 문자열로 변환 후 출력.
    만약 다를 경우, -1 출력.
    etc.) 맵을 이용한 변환만을 사용하다가 벡터를 사용해봤는데 생각보다 편한듯
    참고)
    - 벡터를 이용한 변환: https://blog.naver.com/jinhan814/222342237665
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 400'003 // 아이템의 최대 개수 (= 관계의 최대 개수*2)
#define endl '\n'
using pii = pair<int, int>;

vector<int> adj[MAX];
int in_degree[MAX];  // in_degree[i] = k일 경우, i번 아이템을 구매하기 위해서는 k개의 선행 아이템이 존재
vector<string> conv; // 입력된 문자열들에서 중복 제거 및 오름차순 정렬 상태를 저장

struct cmp
{
    bool operator()(pii p1, pii p2) { return p1.second != p2.second ? p1.second > p2.second : p1.first > p2.first; }
};

vector<int> get_ans()
{
    vector<int> ret;

    priority_queue<pii, vector<pii>, cmp> pq; // {값, 순서}
    for (int i = 0; i < conv.size(); i++)
        if (in_degree[i] == 0)
            pq.push({i, 1});

    while (pq.size())
    {
        auto [cur, pos] = pq.top();
        pq.pop();
        ret.push_back(cur);
        for (const int &next : adj[cur])
            if (--in_degree[next] == 0)
                pq.push({next, pos + 1});
    }

    return ret;
}

int main()
{
    FAST_IO;

    int n; // 관계의 수 (1 ≤ n ≤ 200,000)
    cin >> n;
    vector<pair<string, string>> v(n);
    for (auto &[s1, s2] : v) // 1 ≤ s.length ≤ 15
    {
        cin >> s1 >> s2;
        conv.push_back(s1), conv.push_back(s2);
    }

    sort(conv.begin(), conv.end());
    conv.erase(unique(conv.begin(), conv.end()), conv.end());

    for (const auto &[s1, s2] : v)
    {
        int a = lower_bound(conv.begin(), conv.end(), s1) - conv.begin(); // conv s1
        int b = lower_bound(conv.begin(), conv.end(), s2) - conv.begin(); // conv s2

        adj[a].push_back(b), in_degree[b]++;
    }

    vector<int> ans = get_ans();
    if (ans.size() == conv.size())
        for (const int &i : ans)
            cout << conv[i] << endl;
    else
        cout << -1;
}