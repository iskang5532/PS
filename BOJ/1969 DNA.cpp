// 1969 DNA
// https://www.acmicpc.net/problem/1969
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - i번쨰 문자의 개수를 저장할 배열 v. (v[i]['Z'] = k일 떄, i번째 'Z'의 개수는 k)
    - i번째에서 가장 많은 문자인 c를 합이 가장 작은 DNA인 s에 저장.
    - n - c는 c를 제외한 나머지 문자의 개수, 즉 c에 대한 Hamming Distance.
    etc.) 문제를 잘못 이해해서 오래 걸리기도 했고, 문제 자체도 생각보다 어려웠음
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 53

int main()
{
    FAST_IO;

    int n, m; // DNA의 수 n(1 ≤ n ≤ 1,000), 문자열의 길이 m(1 ≤ m ≤ 50)
    cin >> n >> m;

    int v[MAX]['Z']; // v[i]['Z'] = k일 떄, i번째 'Z'의 개수는 k
    fill(&v[0][0], &v[0][0] + size(v) * size(v[0]), 0);

    for (int i = 0; i < n; i++)
        for (int pos = 0; pos < m; pos++)
        {
            char c;
            cin >> c;
            v[pos][c]++;
        }

    string s;
    int ans = 0;
    for (int pos = 0; pos < m; pos++)
    {
        char c;      // pos번째에서 가장 많은 dna
        int cnt = 0; // pos번째에서 가장 많은 dna의 개수
        for (const auto &dna : {'A', 'C', 'G', 'T'})
            if (cnt < v[pos][dna])
                cnt = v[pos][dna], c = dna;

        s += c, ans += n - v[pos][c];
    }

    cout << s << endl;
    cout << ans;
}