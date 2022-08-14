// 2022-08-12
// 3663 고득점
// https://www.acmicpc.net/problem/3663
/*
    그리디, 완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자를 맞추기 위한 변경 횟수와 `A`가 아닌 문자까지의 이동 횟수를 구해야 한다.
    추가로, 둘은 서로 간섭하지 않는다. 즉, 별개이다.
    - 변경 횟수는 정방향과 역방향 중에서 작은 값을 더한다.
    - 이동 횟수를 구하는 방법은 어떤 문자의 위치를 le, `A`가 아닌 문자의 위치를 ri라 할 때, 총 세 가지 방법으로 구할 수 있다.
     1. 원점 → 끝점
     - 모든 문자열이 `A`가 아닌 문자이다. 즉, 문자의 개수만큼이 거리가 된다.
     2. 원점 → le → 원점 → ri
     - le에서 ri까지 가는 거리보다 원점으로 돌아온 후 ri까지 역방향으로 이동하는 거리가 짧은 경우이다.
     3. 원점 → ri → 원점 → le
     - 역방향으로 ri까지 간 후, 원점으로 돌아와 le까지 가는 거리가 최단 거리일 경우이다.
    - ri까지 역방향 거리를 구할 때는, 문자열의 길이에서 ri를 빼줘야 역방향 거리가 된다.
    - 주의할 점은, le는 'A'여도 된다는 점이다. (반례 확인)
    etc.) 어려웠음
    - 1차 풀이로는 현재 위치에서 가장 가까운 'A'가 아닌 문자로 이동 후 변경하는 식으로 했지만 실패.
    참고)
    - 이론: https://developingbear.tistory.com/169 (이동 횟수 참고)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 0x3f3f3f

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 100
    cin >> tc;
    while (tc--)
    {
        string s; // 1 ≤ s.length ≤ 1,000
        cin >> s;

        int ans = 0;
        for (int i = 0; i < s.length(); i++)
            ans += min(s[i] - 'A', 'Z' + 1 - s[i]); // 알파벳 변경 최소 횟수

        int mn = INF;
        for (int le = 0; le < s.length(); le++) // 기준점 a
        {
            int ri = le + 1; // 기준점 b
            while (s[ri] == 'A' && ri < s.length())
                ri++;

            ri = s.length() - ri; // 마지막 글자로 넘어감

            int l = min(le, ri) * 2 + max(le, ri); // 거리
            // int a = le * 2 + ri,
            //     b = ri * 2 + le;

            mn = min(mn, l);
        }

        cout << ans + mn << endl;
    }
}

// input:
// 1
// AAB
// ans:
// 2