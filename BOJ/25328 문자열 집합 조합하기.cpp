// 2022-12-30
// 25328 문자열 집합 조합하기
// https://www.acmicpc.net/problem/25328
/*
    맵, 백트래킹 (4,936KB, 32ms)
    시간 복잡도: ?
    풀이)
    - 문자열의 최대 길이는 17이므로, 부분 문자열을 구할 때는 3만번의 연산으로 구할 수 있다. (17C8 (k = 8일 경우))
    - 구한 부분 문자열을 횟수와 함께 맵에 저장하여 관리한다.
    - 부분 문자열을 구하는 과정에서, 해당 부분 문자열이 두 번 이상 나타난 경우 valid의 값을 true로 바꾼다.
    - valid에 맞춰 출력을 나눈다.
    만약 valid == false인 경우, -1을 출력한다. (두 번 이상 나온 부분 문자열이 없으므로)
    만약 valid == true인 경우, 맵을 이용하여 값을 출력한다.
    맵에서 꺼낸 문자열이 두 번 이상 나타난 경우, 문자열을 출력한다.
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // prev_permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

map<string, int> m; // {부분 문자열, 만든 횟수}
bool valid;         // 두 번 이상 나타나는 부분 문자열이 존재하는가?

void get_subs(const string &s, int k)
{
    vector<int> bits(s.length(), false);
    fill(bits.begin(), bits.begin() + k, true);

    do
    {
        string subs;
        for (int i = 0; i < bits.size(); i++)
            if (bits[i])
                subs += s[i];
        m[subs]++;
        if (m[subs] >= 2) // 두 번 이상인 경우
            valid = true;
    } while (prev_permutation(bits.begin(), bits.end()));
}

int main()
{
    FAST_IO;

    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    int k;
    cin >> k;

    get_subs(s1, k), get_subs(s2, k), get_subs(s3, k);

    if (!valid)
        cout << -1;
    else
        for (const auto &[s, cnt] : m)
            if (cnt >= 2)
                cout << s << endl;
}