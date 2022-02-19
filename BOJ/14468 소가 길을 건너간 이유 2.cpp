// 14468 소가 길을 건너간 이유 2
// https://www.acmicpc.net/problem/14468
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열에서 두 쌍의 문자의 출발점 및 도착점을 찾아 v에 저장.
    v[i] = {st, ed}일 때, i번째 소('A' + i)의 시작점은 st, 도착점은 ed.
    - 가장 낮은 시작점부터 탐색할 수 있도록 정렬.
    - 하나의 경로 a를 선택한 후, 다른 경로 b와 비교.
    만약 a 사이에 b의 시작점이 존재하며, b의 도착점이 a 사이에 없을 경우, ans++.
    etc.) LIS로 생각했지만, 결국 못품.
    참고)
    - 이론: https://justicehui.github.io/usaco/2019/06/21/BOJ14468/
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 26
#define st first
#define ed second
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    pii v[MAX]; // v[i] = {st, ed}일 때, i번째 소('A' + i)의 시작점은 st, 도착점은 ed
    fill(v, v + MAX, pii{-1, -1});

    for (int i = 0; i < MAX * 2; i++)
    {
        int pos = s[i] - 'A';
        if (v[pos].st == -1) // 첫 번째일 경우 st에, 두 번째일 경우 ed에 저장
            v[pos].st = i;
        else
            v[pos].ed = i;
    }
    sort(v, v + MAX);

    int ans = 0;
    for (int i = 0; i < MAX - 1; i++)
        for (int j = i + 1; j < MAX; j++)
        {
            int s1 = v[i].st, e1 = v[i].ed; // 기준 경로의 시작점 s1, 도착점 e1
            int s2 = v[j].st, e2 = v[j].ed; // 비교 경로의 시작점 s2, 도착점 e2
            if ((s1 < s2 && s2 < e1) && (e1 < e2))
                ans++;
        }

    cout << ans;
}