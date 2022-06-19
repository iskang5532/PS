// 2022-06-13
// 2697 다음수 구하기
// https://www.acmicpc.net/problem/2697
/*
    순열 (2,024KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - next_permutation을 이용해 입력된 문자열 s의 다음 순열을 찾는다.
    만약 다음 순열이 존재할 경우, s의 다음 순열을 출력.
    만약 다음 순열이 존재하지 않을 경우, "BIGGEST" 출력.
 */

#include <iostream>
#include <algorithm> // next_permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

int main()
{
    FAST_IO;

    int tc; //
    cin >> tc;
    while (tc--)
    {
        string s;
        cin >> s;
        cout << (next_permutation(s.begin(), s.end()) == true ? s : "BIGGEST") << endl;
    }
}