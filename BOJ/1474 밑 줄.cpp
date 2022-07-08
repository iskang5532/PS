// 2022-07-04
// 1474 밑 줄
// https://www.acmicpc.net/problem/1474
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어의 길이의 합 l을 구함. l은 새로운 단어를 만들었을 때의 길이에 포함.
    부족한 길이, 즉 m - l을 구한 후, 각 단어 사이에 추가할 언더바의 평균 개수 avg를 구함.
    n-1개에 각각 avg개만큼 추가하고도 m개를 채우지 못할 수 있음. 이 남은 개수를 rem에 저장.
    남은 rem개를 이용하여 문자 사이에 언더바를 골고루 배치해야 한다.
    최대 n-1개의 칸을 확인해야 하므로, permutation을 이용하여 풀 수 있음.
    - 단어 사이에 언더바를 추가할 지의 여부를 저장할 bit를 이용하여 permutation을 수행.
    만약 bit[i] == true일 경우, i번째 단어 다음에 언더바를 추가.
    만들어진 새로운 단어 s와 ans를 비교한 후, 사전순으로 가장 앞선 문자열을 ans에 저장.
    etc.) 그리디하게 풀어보려 하다가 실패
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 12 // max n

int main()
{
    FAST_IO;

    int n, m;
    cin >> n >> m;
    string v[MAX];
    int l = 0; // 입력된 단어들의 길이의 합
    for (int i = 0; i < n; i++)
        cin >> v[i], l += v[i].length();

    int avg = (m - l) / (n - 1); // 언더바의 평균 개수
    int rem = (m - l) % (n - 1); // 추가로 필요한 언더바의 개수
    string bar;
    for (int i = 0; i < avg; i++)
        bar += '_';

    vector<int> bit(n - 1, false);
    fill(bit.begin(), bit.begin() + rem, true);

    string ans = "";
    do
    {
        string s;
        for (int i = 0; i < n - 1; i++)
        {
            s += v[i] + bar;
            if (bit[i])
                s.push_back('_');
        }
        s += v[n - 1];

        ans = (ans.empty() ? s : min(ans, s));
    } while (prev_permutation(bit.begin(), bit.end()));

    cout << ans;
}