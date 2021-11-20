/*
    피로도 (코딩테스트 연습 > 위클리 챌린지 > 피로도)
    조합
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/87946
    풀이)
    - 탐험하는 던전의 순서에 따라 정답이 달라짐. 또한 던전의 최대 개수 또한 8임.
    따라서 던전을 탐험 모든 경우의 수를 구하여 사용.
    1) 던전을 탐험하는 모든 경우의 수를 구하여 사용.
    2) 던전의 필요 조건에 맞는지를 확인.
     - 첫 번째 던전을 탐험하기 위한 필요 피로도를 가지고 있는가?
     - 던전을 탐험한 후에 소모될 소모 피로도가 현재 피로도에서 삭제되었을 경우 음수가 되지 않는가?
     조건을 만족할 경우, 현재 피로도에서 소모 피로도의 값만큼 제거한 후 탐험 횟수 +1
    3) 현재 던전의 탐험 순서를 모두 끝마친 경우, 현재까지 구한 탐험 횟수와 이전까지 구한 탐험 횟수를 비교하여 최대 탐험 횟수를 갱신시킴.
    4) 이후 남아 있는 경우의 수를 이용.
 */

#include <string>
#include <vector>
#include <algorithm> // next_permutation

using namespace std;

int solution(int _k, vector<vector<int>> dungeons)
{
    string bits;
    for (int i = 0; i < dungeons.size(); i++)
        bits += i + '0';

    int ans = 0;
    do
    {
        int k = _k;
        int cnt = 0;
        for (const char &bit : bits)
        {
            int need = dungeons[bit - '0'][0];
            int del = dungeons[bit - '0'][1];
            if (k >= need && k - del >= 0)
                k -= del, cnt++;
        }
        ans = max(ans, cnt);
    } while (next_permutation(bits.begin(), bits.end()));
    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(80, {{80, 20}, {50, 40}, {30, 10}}) << endl;  // 3
//     cout << solution(100, {{100, 50}, {50, 0}, {90, 40}}) << endl; // 2
// }