// 2022-10-02
// 9177 단어 섞기
// https://www.acmicpc.net/problem/9177
/*
    sol.1) DP (2,064KB, 24ms)
    시간 복잡도: O(n*m)
    풀이)
    - dp[][]를 이용하여 현재 사용된 문자들로 만들 수 있는 s3의 길이를 저장.
    dp[i][j] = k일 때, s1에서 i개의 문자와 s2에서 j개의 문자로 만들 수 있는 s3의 길이는 k개 (앞에서부터 해당함)
    이전 dp의 값이 필요함. 편의를 위해 (0, 0)에서부터 한 칸 띄워서 사용.
    현재 구하는 값이 dp[i][j]일 경우, s1의 이전까지의 문자를 이용했을 때의 값 l과 s2의 이전까지의 문자를 이용했을 때의 값 t를 비교.
    만약 t > l일 경우, s2의 문자열을 모두 이용 후 s3의 i+j번 문자에 s1의 문자를 추가할 수 있는지 확인.
     만약 추가할 수 있으면, dp에 t+1의 값을 저장.
    만약 l > r일 경우, s1의 문자열을 모두 이용 후 s3의 i+j번 문자에 s2의 문자를 추가할 수 있는지 확인.
     만약 추가할 수 있으면, dp에 l+1의 값을 저장.
    만약 l == r일 경우, s1 혹은 s2의 문자가 s3를 추가할 수 있는지 확인.
     만약 추가할 수 있으면, dp에 l+1의 값을 저장.
    - dp에 저장된 값이 s3의 길이와 같은지 확인. 만약 같을면 true, 다르면 false를 리턴.
    주의할 점은, s1과 s2에 공백을 추가하였으므로 s.length()에 -1을 연산해줘야 한다. (dp 탐색 범위는 s1.length()-1까지이므로)
    etc.) 어려움. 이론을 봐도 구현하려고 하니 헷갈림.
    참고)
    이론: https://leesh111112.tistory.com/395
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 203 // max str length

bool isValid(const string &s1, const string &s2, const string &s3)
{
    int dp[MAX][MAX]{}; // dp[i][j] = k일 때, s1에서 i개의 문자와 s2에서 j개의 문자로 만들 수 있는 s3의 길이는 k개 (앞에서부터 해당됨)

    for (int i = 0; i < s1.length(); i++)
        for (int j = 0; j < s2.length(); j++)
        {
            int t = i == 0 ? 0 : dp[i - 1][j], // top (현재 dp의 윗쪽 값)
                l = j == 0 ? 0 : dp[i][j - 1]; // left (현재 dp의 왼쪽 값)
            dp[i][j] = max(t, l);
            if ((i == 0 && j == 0) || dp[i][j] < i + j - 1) // 더 이상 볼 필요 없는 경우 (i + j - 1보다 작은 경우, i+j번 문자와 같아도 채울 수 없음 (순서대로이므로))
                continue;

            char c = s3[i + j - 1];
            if (t > l) // 윗쪽 값이 더 큰 경우 (= 왼쪽 s1의 문자를 사용)
            {
                if (s1[i] == c)
                    dp[i][j]++;
            }
            else if (l > t) // 왼쪽 값이 더 큰 경우 (= 윗쪽 s2의 문자를 사용)
            {
                if (s2[j] == c)
                    dp[i][j]++;
            }
            else // t == l (아무 문자나 사용)
                if (s1[i] == c || s2[j] == c)
                    dp[i][j]++;
        }

    return dp[s1.length() - 1][s2.length() - 1] == s3.length() ? true : false; // 문자열에 공백을 추하했으므로 -1을 해줘야 함
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;

        cout << "Data set " << t << ": " << (isValid(" " + s1, " " + s2, s3) ? "yes" : "no") << endl;
    }
}

/*
    sol.2) DP(1차원 배열) (2,024KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 2차원 dp를 1차원 배열 2개로 나눠 사용.
    가능한 이유는, 현재 상태 dp를 구하기 위해서는 이전 상태 dp만을 사용하기 때문.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 203 // max str length

bool isValid(const string &s1, const string &s2, const string &s3)
{
    int prev[MAX]{}, cur[MAX]{};

    for (int y = 0; y < s1.length(); y++)
    {
        for (int x = 0; x < s2.length(); x++)
        {
            int t = y == 0 ? 0 : prev[x],
                l = x == 0 ? 0 : cur[x - 1];
            cur[x] = max(t, l);
            if ((y == 0 && x == 0) || cur[x] < y + x - 1)
                continue;

            char c = s3[y + x - 1];
            if (t > l)
            {
                if (s1[y] == c)
                    cur[x]++;
            }
            else if (l > t)
            {
                if (s2[x] == c)
                    cur[x]++;
            }
            else // t == l
                if (s1[y] == c || s2[x] == c)
                    cur[x]++;
        }
        copy(cur, cur + MAX, prev);
        fill(cur, cur + MAX, 0);
    }

    return prev[s2.length() - 1] == s3.length() ? true
                                                : false;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;

        cout << "Data set " << t << ": " << (isValid(" " + s1, " " + s2, s3) ? "yes" : "no") << endl;
    }
}