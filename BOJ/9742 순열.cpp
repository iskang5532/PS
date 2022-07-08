// 9742 순열
// https://www.acmicpc.net/problem/9742
/*
    완전 탐색 (2,012KB, 12ms)
    시간 복잡도: O(n)
    풀이)
    - next_permutation을 이용하여 입력된 문자열의 다음 순열을 구해준다.
    추가로, 수행할 때마다 횟수를 세어주어 현재 순열이 몇 번째 순열인지를 구해준다.
    이를 이용해 입력된 문자열의 n번째 순열을 구해준다.
    또한, 현재 순열의 순서가 n보다 커질 수 있으므로 n에서 멈출 수 있도록 해준다.
    - 출력
     - 기존 문자열과 cnt를 출력해줘야 한다. 그러므로, next_permutation을 수행하기 전에 출력해주거나 기존 문자열을 복사한 값을 이용해준다.
     - cnt == n일 경우, 구한 순열을 출력해준다.
     - cnt != n일 경우, "No permutation"을 출력해준다. (cnt < n으로, 주어진 문자열의 남은 순열이 부족해 n번째 순열을 구할 수 없는 경우이다.)
 */

#include <iostream>
#include <algorithm> // next_permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    string str; // str.len ≤ 10
    int n;      // 1 ≤ n ≤ 3,628,800
    while (cin >> str >> n)
    {
        cout << str << ' ' << n << ' ' << '=' << ' ';

        int cnt = 1;
        while (next_permutation(str.begin(), str.end()) && ++cnt < n)
            ;

        n == cnt ? cout << str
                 : cout << "No permutation";
        cout << endl;
    }
}