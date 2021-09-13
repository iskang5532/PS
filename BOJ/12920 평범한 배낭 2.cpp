/* 
 * 12920 평범한 배낭 2
 * DP, knapsack
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/12920
 * etc.) 12865 평범한 배낭과 다른 점은, 같은 물건이 여러 개 존재한다는 점.
 * 입력에서 같은 물건이 여러개여서 w, v에 하나씩 집어넣으면 TLE/MLE를 받음.
 * 때문에, 입력 속도 및 공간 활용을 위해 거듭제곱을 이용함.
 * 2가 13개일 경우, 1, 2, 4를 넣은 후 나머지 6을 넣음. (6을 원하는 경우 1개와 2개를, 10을 원하는 경우 1개와 3개를 가지고 만들 수 있음)
 * 참고: https://blog.naver.com/jinhan814/222232364601 (이론)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 1 <= n <= 100, 1 <= m <= 10k
    cin >> n >> m;

    vector<int> w, v;
    for (int i = 0; i < n; i++)
    {
        int a, b, c; // 무게, 만족도, 개수 (1 <= a <= m(10k), 1 <= b,c <= 10k, 1 <= a*c <= 10k)
        cin >> a >> b >> c;

        for (int r = 1; r <= c; r <<= 1) // 제곱된 값이며, 공간(벡터)에 넣을 개수 (제곱씩 증가)
        {
            w.push_back(a * r);
            v.push_back(b * r);

            c -= r; // r개를 가방에 넣었기 때문에 개수에서 r개를 뺌
        }
        if (c) // 개수가 남아있는 경우
            w.push_back(a * c), v.push_back(b * c); // 남은 개수를 공간(벡터)에 넣어줌
    }

    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int i = 0; i < w.size(); i++) // i번째 물건
    {
        for (int pos = w[i]; pos <= m; pos++) // i번째 물건의 무게부터 측정하여 제한된 무게 m까지 확인
            curr[pos] = max(prev[pos], v[i] + prev[pos - w[i]]); // 이전 값의 가치 or 현재 물건의 가치 + 이전 값 (현재 물건을 포함시킨 경우이기 때문에 무게는 0에서부터)
        prev = curr;
    }

    cout << curr.back();
}