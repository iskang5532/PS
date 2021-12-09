/*
    1943 동전 분배.cpp
    DP, Knapsack (2,152KB, 112ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1943
    풀이)
    - dp[i] = true일 때, 동전들로 i원을 만들 수 있음.
    - 합계 / 2 == 1일 경우, 반으로 나누는 것이 가능하다. (합계의 절반을 만들 수 있다면, 나머지 값 또한 절반의 값이므로)
    그러므로 dp[total/2]를 구해줌. (= total >>= 1)
    - 동전의 개수가 여러 개일 수도 있음. 만약 1원짜리 10만 개일 경우, 10만의 경우에 대해 10만 원을 만들 수 있는 경우를 모두 탐색해야 하며, 이는 TLE. (and MLE?)
    그러므로 제곱 수를 이용하여 저장. ex) 100원 8개일 경우, 100원, 200원, 400원, 100원(나머지)
    dp를 구하는 과정에서 합계(= total)부터 확인한다. 만약 arr의 값에서부터 시작할 경우, 탐색 중에 저장된 dp의 값을 이용하여 뒤에 올 dp값이 부정확하게 된다.
    그러므로 구하려는 값에 지장이 없도록 뒤에서부터 확인하며 값을 구해준다.
    - k원을 이용해 i원을 만들 수 있는지 확인하는 방법은, i - k가 true인지를 확인한다. (= i원에 동전의 값을 더해줌)
    etc.) 어려웠음.
    - dp를 curr와 prev를 선언하여 2차원 배열같이 풀었을 경우, 시간 초과가 나버림. (prev = curr에서 나는 걸지도)
 */

#include <iostream>
#include <vector>

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

    int n; // 동전의 종류 N(1 ≤ N ≤ 100)
    while (cin >> n)
    {
        int total = 0; // 동전의 합계
        vector<int> arr;
        while (n--)
        {
            int v, cnt;
            cin >> v >> cnt, total += (v * cnt);

            for (int i = 0; 1 << i <= cnt; i++) // 제곱 수를 이용한 저장
                arr.push_back(v * (1 << i)), cnt -= (1 << i);
            if (cnt) // 제곱 수를 구하고 남은 개수
                arr.push_back(v * cnt);
        }

        if (total & 1) // 합이 홀수일 경우, 반으로 나눌 수 없음
        {
            cout << '0' << endl;
            continue;
        }
        total >>= 1;

        vector<bool> dp(total + 1, false); // dp[i] = true일 때, 동전들로 i원을 만들 수 있음
        dp[0] = true;

        for (int pos = 0; pos < arr.size(); pos++)
            for (int i = total; i >= arr[pos]; i--) // total부터 arr[pos]까지 (= top-down?)
                if (dp[i - arr[pos]])               // i원을 만들 수 있을 경우
                    dp[i] = true;

        cout << dp[total] << endl;
    }
}