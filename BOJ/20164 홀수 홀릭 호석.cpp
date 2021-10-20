/*
    20164 홀수 홀릭 호석
    재귀, 구현 (2,028KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/20164
    etc.)
    재귀를 이용하였으며, 재귀를 이용하기 위해 메인 코드를 함수에 넣음.
    - 세 자리 이상인 경우 나올 수 있는 모든 경우의 수를 구함.
    - 두 자리인 경우 수를 합한 값을 다시 재귀로 돌림. 이 때 구한 최댓값 및 최솟값을 같이 가져감.
    - 한 자리일 경우, 이전에 구한 최댓값 및 최솟값을 조건에 맞게 저장. (이전에 구한 최댓값보다 큰가 혹은 최솟값보다 작은가)
    이후 더 이상 할 연산이 없으므로 함수를 빠져 나감.
    만약 입력된 수로 경우의 수를 두 가지 이상 만들 수 있는 네 자리 이상의 값인 경우, 다음 경우의 수로 재귀.
 */

#include <iostream>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 1234567890

int ans_mx = 0, ans_mn = INF;

int get_odd(const string &str) // 현재 숫자에서 홀수의 개수 구하기
{
    int ret = 0;
    for (const auto &c : str)
        if (c - '0' & 1)
            ret++;

    return ret;
}

void solution(string str, const int _mx = 0, const int _mn = 0)
{

    int k = get_odd(str); // 현재 수에서 홀수의 개수를 구함
    int mx = _mx + k, mn = _mn + k;

    if (str.length() == 1) // 한 자리: 값을 갱신 후 종료
    {
        ans_mx = max(ans_mx, mx);
        ans_mn = min(ans_mn, mn);
        return;
    }
    else if (str.length() == 2) // 두 자리: 수를 2개로 나눠 합을 구한 후 재귀
    {
        str = to_string((str.front() - '0') + (str.back() - '0'));
        solution(str, mx, mn);
    }
    else if (str.length() >= 3) // 세 자리 이상: 3개로 나눠 합을 구한 후 재귀 (3개로 나눌 수 있는 모든 경우를 이용)
    {
        for (int l = 1; l < str.length() - 1; l++)
            for (int r = l + 1; r < str.length(); r++)
            {
                string s1, s2, s3;
                s1 = string(str.begin(), str.begin() + l);
                s2 = string(str.begin() + l, str.begin() + r);
                s3 = string(str.begin() + r, str.end());

                string sum = to_string(stoi(s1) + stoi(s2) + stoi(s3)); // 분할한 3개의 수로 합을 구함
                solution(sum, mx, mn);
            }
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    string str; // 1 ≤ N ≤ 10^9-1, N 은 자연수
    cin >> str;

    solution(str);

    cout << ans_mn << " " << ans_mx;
}