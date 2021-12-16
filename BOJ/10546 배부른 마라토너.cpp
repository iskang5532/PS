// 10546 배부른 마라토너
// https://www.acmicpc.net/problem/10546
/*
    map (10,192KB, 76ms)
    시간 복잡도: ?
    풀이)
    - map[str] = k인 경우, 이름이 str인 사람이 k명.
    1) n명의 인원을 받아 맵에 저장. (+1)
    2) n-1명의 인원을 받아 맵에서 제거. (-1)
    만약 0명이 된 경우, 맵에서 제거.
    3) 맵에 남은 인원(= 마지막 인원)은 완주하지 못한 인원이 되며, 출력.
    etc.) 간단한 문제인데 이것저것 해보려다가 오래 걸림. (셋, 벡터 등..)
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 참가자 수 N이 주어진다. (1 ≤ N ≤ 100k)
    cin >> n;

    unordered_map<string, int> um;
    for (int i = 0; i < n; i++) // 맵에 저장
    {
        string str;
        cin >> str;
        um[str]++;
    }
    for (int i = 0; i < n - 1; i++) // 맵에서 제거
    {
        string str;
        cin >> str;
        um[str]--;
        if (!um[str])
            um.erase(str);
    }
    cout << um.begin()->first; // 맵에 남아 있는 값은 마라톤을 완주하지 못한 참가자.
}