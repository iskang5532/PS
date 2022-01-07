// 1427 소트인사이드
// https://www.acmicpc.net/problem/1427
/*
    정렬 (2,024KB, 0ms)
    시간 복잡도: O(nlogn)
    풀이) 입력을 문자열로 받은 후, 문자열을 내림차순 정렬.
    - 내림차순 정렬을 위해, sort의 세번째 인자에 greater<char>(). (char인 이유는, char끼리 정렬되므로)
    etc.) 문자열 전용 정렬 알고리즘은?
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    string str;
    cin >> str;

    sort(str.begin(), str.end(), greater<char>());
    cout << str;
}