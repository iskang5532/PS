// 11729 하노이 탑 이동 순서
// https://www.acmicpc.net/problem/11729
/*
    재귀 (2,020KB, 132ms)
    시간 복잡도: ?
    풀이)
    - n개의 원판을 옮기는 방법을 구하기 위해선 n-1개의 원판을 옮기는 방법을 구하는 방식.
    - 시작점 st, 종료점 ed, 그 외의 지점 mid. (default: st = 1, ed = 3, mid = 2)
    1) st에서부터 mid까지 n-1개의 원판, 즉 제일 큰 원판을 제외한 나머지 원판들을 옮김.
    2) 현재 st에 남아 있는 원판은 원판들 중 가장 큰 값임. 그러므로 ed에 옮겨줌.
    3) mid에 남아 있는 원판들 또한 ed로 옮겨줘야 하므로, 1)에서 했던 것과 똑같이 남아 있는 원판들 중 가장 큰 값을 제외한 원판들을 다른 칸으로 옮겨줌.
    이때, mid를 시작점 st로 보며, 나머지 원판을 옮길 장소는 mid로 봄.
    etc.) 어려웠음. DP나 그리디같은 느낌
    참고)
    - 이론: https://blog.naver.com/jinhan814/222587262628
            https://brenden.tistory.com/31
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

void Hanoi(int n, int st, int ed)
{
    if (n == 0)
        return;

    int mid = 6 - st - ed; // 1 + 2 + 3 = 6

    Hanoi(n - 1, st, mid); // 제일 큰 원판을 제외하고 mid로 이동
    cout << st << " " << ed << endl;
    Hanoi(n - 1, mid, ed); // 이동한 원판들(제일 큰 값 제외)을 ed로 이동
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 원판의 개수 N (1 ≤ N ≤ 20)
    cin >> n;

    cout << (1 << n) - 1 << endl;
    Hanoi(n, 1, 3); // st, mid, ed의 첫 위치 (1번, 2번, 3번)
}