/* 
 * 3078 좋은 친구
 * Sliding Window
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/3078
 * ETC.) 입력된 문자열의 길이를 len에 저장하며, 슬라이딩 윈도우 방식으로 체크.
 * k개 만큼의 len을 cnt에 저장 후, 0에서부터 k까지의 상자 형태가 우측으로 한 칸 씩 우측으로 이동하며 체크.
 * 맨 앞의 값과 길이가 같은 문자열의 개수(= cnt)를 ans에 더해줌
 * 참고: 
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define LEN_MAX 20 + 1

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> len(n); // len[n]일 때, n번 째 문자열의 길이
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        len[i] = str.length(); // 문자열의 길이로 저장
    }

    int cnt[LEN_MAX] = {0};
    for (int i = 0; i <= k; i++) // i번째 문자열의 길이에 대해 cnt++ 해줌 (첫 번째부터 k번째까지)
        cnt[len[i]]++;

    long long answer = 0;                // 300k^2이기 때문에 ll을 사용한다고 하는데, 정확히는 모르겠음..
    for (int left = 0; left < n; left++) // 슬라이딩 윈도우에서의 좌측
    {
        answer += cnt[len[left]] - 1; // 좌측 값과 같은 길이의 개수를 더해주되, 본인은 제외 (= -1)
        cnt[len[left]]--;             // 좌측 값 길이의 개수 -1

        int right = left + k;      // 슬라이딩 윈도우에서의 우측
        if (right + 1 < n)         // 만약 우측으로 이동해도 범위(= n)의 안쪽인 경우
            cnt[len[right + 1]]++; // [우측 + 1]번째 값의 길이에 대한 카운트 +1
    }

    cout << answer;
}