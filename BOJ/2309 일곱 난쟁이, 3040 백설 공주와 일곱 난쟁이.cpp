// 2309 일곱 난쟁이, 3040 백설 공주와 일곱 난쟁이
// https://boj.kr/2309 https://boj.kr/3040
/*
    sol.1) 백트래킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 9개 중에서 고른 7개의 합이 100이 됐을 때, 각 값을 출력해줌.
    - 7개를 골라주기 위해 DFS를 사용.
    - 배열 idx에 사용할 값을 순차적으로 저장함.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 9 // 입력

int v[MAX];
int idx[MAX];

void dfs(int dep = 0, int pos = 0, int sum = 0)
{
    if (dep > 7)
        return;

    if (sum == 100)
    {
        for (int i = 0; i < 7; i++)
            cout << idx[i] << '\n';
        exit(0);
    }

    for (int i = pos; i < MAX; i++)
    {
        if (sum + v[i] > 100) //  값이 초과함
            continue;

        idx[dep] = v[i];
        dfs(dep + 1, i + 1, sum + v[i]);
    }
}

int main()
{
    FAST_IO;

    for (auto &i : v)
        cin >> i;

    sort(v, v + MAX);

    dfs();
}

/*
    sol.2) 완전 탐색 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 9C7 == 9C2임을 이용한 풀이.
    - 9개 중 두 개를 제외한 나머지 값의 합이 100이 되었을 경우, 두 개를 제외한 나머지 값을 출력.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222579884777
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 9 // 입력

int v[MAX];
bool visited[MAX];
int sum = 0; // 입력된 값의 합

void solution()
{
    for (int i = 0; i < MAX; i++)
        for (int j = i + 1; j < MAX; j++)
            if (sum - v[i] - v[j] == 100)
            {
                for (int k = 0; k < MAX; k++)
                    if (k != i && k != j)
                        cout << v[k] << '\n';

                return;
            }
}

int main()
{
    FAST_IO;

    for (auto &i : v)
        cin >> i, sum += i;

    sort(v, v + MAX);

    solution();
}