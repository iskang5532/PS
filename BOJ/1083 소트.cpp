// 2022-08-22
// 1083 소트
// https://www.acmicpc.net/problem/1083
/*
    sol.1) 그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 큰 수를 얼마나 앞으로 배치하는지가 관건인 문제.
    - 스왑할 수 있는 횟수가 정해져 있음. 즉, 옮길 수 있는 가장 큰 수를 골라 옮겨야 함.
    - 입력된 수를 v에 저장한 후, n개 혹은 s번만큼 값을 탐색. (n번의 이동 후 사전순으로 가장 뒷서는 배열이 됨)
    - 값을 옮길 위치 st는 0부터 시작.
    최댓값이면서 앞으로 보낼 수 있다면, 값과 위치를 각각 mx와 pos에 저장.
    이후, pos를 st까지 스왑하며 mx를 옮기며 옮긴 횟수 pos-st만큼 횟수 감소.
    etc.) 무작정 큰 값을 앞으로 옮기는 문제인줄 알았으나 아니었음
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n

int main()
{
    FAST_IO;

    int n; // 수의 개수 (1 ≤ n ≤ 50)
    cin >> n;
    int v[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int s; // 교환 횟수 (1 ≤ s ≤ 1,000,000)
    cin >> s;

    for (int st = 0; st < n && s; st++) // 값을 옮길 위치
    {
        int mx = 0, pos; // 스왑할 수 있는 가장 큰 수 mx, mx의 위치 pos
        for (int cur = st; cur < n; cur++)
            if (mx < v[cur] && s + st - cur >= 0)
                mx = v[cur], pos = cur;

        for (int i = pos - 1; i >= st; --i)
            swap(v[i], v[i + 1]);
        s -= pos - st;
    }

    for (int i = 0; i < n; i++)
        cout << v[i] << ' ';
}

/*
    sol.2) 그리디 (5,808KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 앞으로 옮길 수 있는 값 k와 위치 cur를 구한 후, ans[pos]에 저장.
    k는 used에 true로 저장. 이후, 다음 탐색에서 제외.
    pos에서 cur까지 k를 옮김. 이는, 구간에 존재하는 값의 위치가 +1이 됬다는 것이므로, 각 값의 위치를 +1.
    - 사용된 적이 없는 값을 찾은 후, ans에 저장.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n

int main()
{
    FAST_IO;

    int n; // 수의 개수 (1 ≤ n ≤ 50)
    cin >> n;
    int v1[MAX]{};
    pii v2[MAX]; // v2[i] = {a, b}일 때, 수 a는 b번째 값
    for (int i = 0; i < n; i++)
    {
        cin >> v1[i];
        v2[i] = {v1[i], i};
    }
    int s; // 교환 횟수 (1 ≤ s ≤ 1,000,000)
    cin >> s;

    sort(v2, v2 + n, greater<pii>()); // 입력된 수의 내림차순 정렬

    int ans[MAX], used[1'000'003]{};
    int pos = 0; // 스왑 횟수 (= 다음 스왑될 값의 위치)
    while (s)
    {
        bool isSwap = false; // 스왑한 적이 있는가
        for (int i = 0; i < n && s && !isSwap; i++)
        {
            auto [k, cur] = v2[i]; // 현재 수 k와 위치 cur

            if (!used[k] && cur - pos <= s) // 스왑한 적이 없으면서 앞으로 옮길 수 있을 경우
            {
                for (int i = 0; i < n; i++)
                    if (v2[i].second < cur)
                        v2[i].second++;

                ans[pos] = k;

                s -= cur - pos; // 움직인 만큼 감소
                used[k] = true, pos++;

                isSwap = true;
            }
        }

        if (!isSwap) // 더 이상 스왑할 필요가 없는 경우
            break;
    }

    for (int i = 0; i < n; i++)
        if (!used[v1[i]])
            ans[pos] = v1[i], pos++;

    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}

// input:
// 4
// 1 2 9 1
// 2
// ans:
// 2 9 1 1