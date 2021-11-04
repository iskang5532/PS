/*
    기지국 건설 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 기지국 설치)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12979
    etc.) 첫 풀이로는 TLE를 받은 문제. (혹시나 될까 싶은 마음에 시도해봤지만 결과는 역시..)
    - 위치 i에 전파가 닿는지 판단하는 것조차 시간이 아깝다고 생각하여 따로 공간을 사용하지 않음.
    - 변수를 이용하여 해당 변수 이하의 위치에는 이미 전파가 닿고 있다고 가정함.
    - 현재 위치(= pos)에서부터 w 만큼의 거리 안에 기지국(stations)이 존재하는 경우, 기지국 + w 위치의 다음 위치(+1)로 이동하여 탐색.
    - pos에서부터 w 만큼의 거리 안에 기지국이 존재하지 않는 경우, w 만큼 떨어진 거리에 기지국을 설치했다고 가정한 후 pos + w + w + 1의 위치로 이동.
    또한 이 경우는 기지국을 설치해야 하므로 카운팅을 해줌.
 */

#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int solution(int n, vector<int> stations, int w)
{
    int ans = 0;
    auto itr = stations.begin();
    for (int pos = 1; pos <= n; pos++)
    {
        while (itr != stations.end() && *itr - w <= pos && pos <= *itr + w)
            pos = *itr + w + 1, itr++;
        if (pos > n)
            continue;
        pos += w << 1, ans++;
    }

    return ans;
}

#include <iostream>
#define endl "\n"
int main()
{
    cout << solution(11, {4, 11}, 1) << endl; // 3
    cout << solution(16, {9}, 2) << endl;     // 3
    cout << solution(10, {3}, 10) << endl;    // 0
}

// TLE
// int solution(int n, vector<int> stations, int w)
// {
//     vector<bool> visited(n + 1, false);
//     for (const auto &elem : stations)
//     {
//         for (int i = elem - w; i <= elem + w && i <= n; i++)
//         {
//             if (i < 1)
//                 i = 1;
//             visited[i] = true;
//         }
//     }
//     int ans = 0;
//     for (int pos = 1; pos <= n; pos++)
//     {
//         if (visited[pos])
//             continue;

//         pos += w << 1;
//         ans++;
//     }

//     return ans;
// }