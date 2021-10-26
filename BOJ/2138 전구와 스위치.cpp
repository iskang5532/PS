/*
    2138 전구와 스위치
    그리디 (2,392KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2138
    etc.) 너무 어려웠음..
    * 풀이는 이론을 참고했던 사이트를 확인.
    - 스위치는 [0]부터 우측으로 하나씩 이동하면서 누를지를 판단한다. (이것이 가능한 이유는 스위치를 누르는 순서가 정답을 구하는 것과 상관이 없기 때문)
    - 판단은, i번째 스위치가 있을 때 왼쪽(i-1)의 스위치를 비교한 후 판단한다.
    - 현재 상태(= start)의 i-1이 원하는 상태(= end)의 i-1과 다를 때, i번째 스위치를 눌러 i-1을 서로 같게 바꿔준다.
    이후 i+1번 스위치로 옮겨가며, 마지막 스위치까지 수행해준다.
    - 여기서 예외를 해줘야 할 점은, start[0] == end[0]일 때도 있고 아닐 때도 있다는 점이다.
    다른 경우, [0]을 한 번만 눌러줘야 하는데 [0]을 누를 수 있는 스위치인 [0]과 [1]을 한 번만 눌러줘야 한다.
    즉, [0]일 누르는 경우 한 번, [1]을 누르는 경우 한 번씩 수행해줘야 한다.
    참고)
    이론: https://staticvoidlife.tistory.com/143
        https://blog.naver.com/jinhan814/222259251875
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890

const int dim[3] = {-1, 0, 1}; // 왼쪽, 가운데, 오른쪽

int n; // 전구 및 스위치의 개수 N(2 ≤ N ≤ 100k)

void click(string &str, const int i)
{
    for (int _i = 0; _i < 3; _i++)
    {
        int curr = i + dim[_i];
        if (!(0 <= curr && curr < n))
            continue;

        str[curr] = (!(str[curr] - '0') + '0');
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n;
    string start, end; //현재 상태 start, 만들고자 하는 전구들의 상태 end
    cin >> start >> end;

    int ans = INF;

    { // [0]을 누르고 시작 (= 0부터)
        string curr = start;
        int cnt = 0;
        click(curr, 0), cnt++; // [0]

        for (int i = 1; i < n; i++)
            if (curr[i - 1] != end[i - 1])
                click(curr, i), cnt++;
        if (curr == end)
            ans = min(ans, cnt);
    }
    { // [0]을 누르지 않고 시작 (= 1부터)
        string curr = start;
        int cnt = 0;

        for (int i = 1; i < n; i++)
            if (curr[i - 1] != end[i - 1])
                click(curr, i), cnt++;
        if (curr == end)
            ans = min(ans, cnt);
    }

    if (ans == INF)
        cout << "-1";
    else
        cout << ans;
}

// 100%
// 000 000
// ans: 0