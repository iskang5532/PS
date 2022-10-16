// 2022-10-10
// 2992 크면서 작은 수
// https://www.acmicpc.net/problem/2992
/*
    문자열, 정렬 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - "정수 X가 주어졌을 때, X와 구성이 같으면서 X보다 큰 수 중 가장 작은 수를 출력한다."
    이는 next_permutation을 이용하면 쉽게 구할 수 있다.
     - 조건을 만족하는 x보다 큰 수가 없을 수도 있다. 이는 x가 이미 최댓값일 때이다.
    이 값에 next_permutation을 적용하게 된다면, 조건을 만족하는 최솟값이 된다.
    - x를 저장한 s를 정렬한 후, next_permutation한 x값과 비교.
    만약 같을 경우, 조건을 만족하는 값은 존재하지 않음.
    만약 다를 경우, x는 조건을 만족하는 기존 x보다 큰 값이므로 출력한다.
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string x; // 1 ≤ X ≤ 999,999, X != 0
    cin >> x;

    next_permutation(x.begin(), x.end());

    string s = x;
    sort(s.begin(), s.end());
    cout << (s == x ? "0" : x);
}
