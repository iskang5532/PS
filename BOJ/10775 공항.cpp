/*
    10775 공항
    유니온 파인드 (2,812KB, 12ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/10775
    풀이)
    - g값과 가장 가까운 게이트에 비행기를 도킹.
    - g번 게이트에 도킹이 완료된 상황에서 같은 g값이 한번 더 들어올 경우, g-1에 도킹을 시켜줘야 함.
    이를 위해 parent 배열을 선언하여 g값에 의한 최적의 도킹 위치를 저장. (범위는 1~g까지이며, g = 5에 {5, 5, 5}가 들어올 경우 5번, 4번, 3번에 도킹.)
    1) parent 배열을 선언 및 초기화. (처음엔 전부 빈 공간이므로 g값이 들어오는 즉시 g번 게이트에 도킹)
    이후 비행기의 수만큼 입력을 받음. (입력될 g값을 {1, 1}로 가정)
    2) 1이 들어오며, 비행기가 도킹할 수 있는 최적의 위치(= p)를 찾음.
    parent[1] == 1이므로 p == 1이며, g를 [1]에 도킹시키며 ans++.
    이후 똑같은 값이 들어올 경우 p가 아닌 p - 1로 도킹시키기 위해 parent[1] = p-1.
    3) 다시 1에 대한 p값을 찾으며, 값은 0이 된다.
    그러나 0번 게이트는 존재하지 않는다. 즉, 이 비행기가 도킹할 게이트는 존재하지 않는다.
    그러므로, 현재까지 도킹시킨 비행기의 수인 ans를 출력시키고 종료한다.
    etc.) 유니온 파인드 문제는 자주 헷갈리는듯
    - 첫 시도로 visited를 이용해 그리디하게 탐색시킴. 그러나 TLE. (그리디가 아닌 완전탐색인가?)
    - 이전에 카카오의 방 배정 문제를 떠올리며 유니온 파인드로 풀이. (호텔 방 배정: https://programmers.co.kr/learn/courses/30/lessons/64063)
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100'000 + 1

int parent[MAX]; // parent[5] = 3일 경우, g == 5인 비행기가 도킹할 최적의 장소는 3번 (4, 5는 이미 참)
int find(const int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = find(parent[x]); // 부모의 부모 찾기
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int g, _p; // 게이트의 수 g, 비행기의 수 _p (1 ≤ g, _p ≤ 100k)
    cin >> g >> _p;

    int ans = 0;
    for (int i = 0; i <= g; i++) // fill
        parent[i] = i;

    for (int i = 0; i < _p; i++)
    {
        int x;
        cin >> x;

        int p = find(x); // x가 도킹할 수 있는 게이트

        if (p == 0) // 도킹할 게이트가 없을 경우
            break;

        parent[p] = p - 1; // p번째에 도킹을 완료했으므로 그 이전의 위치에 도킹할 수 있도록 도킹할 게이트를 왼쪽값으로 바꿔줌

        ans++;
    }

    cout << ans;
}