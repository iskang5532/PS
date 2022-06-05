// 2022-06-01
// 2002 추월
// https://www.acmicpc.net/problem/2002
/*
    sol.1) 구현, 맵 (2,160KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 차랑이 들어간 순서를 저장할 um. (um[s] = k일 경우, 차량 번호 s는 터널에 k번째로 들어감)
    - 차량이 빠져나갔는지 여부를 저장할 used. (used[k] = true일 경우, k번째 차량은 터널을 빠져나감)
    - 가장 먼저 들어간 차량의 번호 및 아직 빠져나가지 않은 번호를 저장할 top.
    = 빠져나간 차량 번호 s를 입력받음.
     - 빠져나간 차량을 used에 처리.
     - 현재 차량의 순서가 앞서 들어온 차량보다 빠른 경우, s는 추월함. (= um[s] > top)
     - 현재 차량의 순서가 앞서 들어온 차량보다 느리거나 같은 경우, s는 추월하지 않음 (= um[s] <= top)
     used를 이용해 top을 갱신. (아직 빠져나가지 않은 차량 중 가장 먼저 들어온 차량의 순서를 구함)
    etc.) LIS를 이용하는 전봇대 문제와 같은줄
    참고)
    - 반례: https://www.acmicpc.net/board/view/78417
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

unordered_map<string, int> um; // um[s] = k일 경우, 차량 번호 s는 터널에 k번째로 들어감
bool used[MAX];                // used[k] = true일 경우, k번째 차량은 터널을 빠져나감

int main()
{
    FAST_IO;

    int n; // 차의 대수 (1 ≤ N ≤ 1,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        um[s] = i;
    }

    int ans = 0, top = 0; // 먼저 터널에 들어갔으면서 아직 터널을 빠져나가지 않은 번호
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        used[um[s]] = true;

        if (um[s] > top)
            ans++;
        else
            while (used[top])
                top++;
    }

    cout << ans;
}

/*
    sol.2) 구현, 맵 (2,160KB, 0ms)
    시간 복잡도: O(logN)
    풀이)
    - 차랑이 들어간 순서를 저장할 um. (um[s] = k일 경우, 차량 번호 s는 터널에 k번째로 들어감)
    = i번째로 빠져나간 차량이 몇 번째로 터널에 들어왔는지를 저장할 v. (v[i] = k일 때, i번째 차량은 k번째로 터널에 들어옴)
    - 터널에서 빠져나간 차량 s를 기준으로, 아직 터널에 남아 있는 차량 중에서 s보다 일찍 들어온 차량이 있을 시 ans++.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

unordered_map<string, int> um; // um[s] = k일 경우, 차량 번호 s는 터널에 k번째로 들어감

int main()
{
    FAST_IO;

    int n; // 차의 대수 (1 ≤ N ≤ 1,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        um[s] = i;
    }

    vector<int> v(n); // v[i] = k일 때, i번째 차량은 k번째로 터널에 들어옴
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        v[i] = um[s];
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) // 현재 빠져나간 차량 i
        for (int j = i + 1, flag = true; j < n && flag; j++)
            if (v[i] > v[j]) // 차량 i가 더 늦게 들어온 경우
                ans++, flag = false;
    cout << ans;
}

// 5 1 2 3 4 5 5 4 3 2 1
// ans: 4
// 5
// 1   5 x
// 2   4 x
// 3   3 x
// 4   2 x
// 5   1

// 4 1 2 3 4 4 1 3 2
// ans: 2
// 4
// 1   4 x
// 2   1
// 3   3 x
// 4   2
