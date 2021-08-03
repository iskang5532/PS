/* 
 * 3020 개똥벌레
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/3020
 * ETC.) 입력된 k값마다 덧셈을 해주면 시간 초과가 나버림.
 * 때문에, 값 k의 길이가 있을 때, 앞과 뒤에 체크를 해주어 k값의 모든 입력이 끝난 후에 전체적으로 덧셈을 시작함
 * 참고: https://blog.naver.com/jinhan814/222252619895 (이론 및 최적화 참고)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, h; // 2 <= n <= 200k, 2 <= h <= 500k;
    cin >> n >> h;

    vector<int> pSum(h, 0);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        if (i & 1) // 홀 (= 종유석)
            pSum[h - k]++;
        else // 0 or 짝(= 석순)
            pSum[0]++, pSum[k]--;
    }

    for (int i = 1; i < h; i++) // [0]은 값 그대로의 횟수
        pSum[i] += pSum[i - 1];

    int _min = *min_element(pSum.begin(), pSum.end()); // 최솟값 탐색
    int cnt = count(pSum.begin(), pSum.end(), _min);   // 값의 개수 탐색

    cout << _min << " " << cnt << endl;
}