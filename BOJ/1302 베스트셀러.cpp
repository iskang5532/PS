/* 
 * 1302 베스트셀러
 * map
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1302
 * ETC.) 맵을 이용한 기본적인 문제인듯 싶음.
 */

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    map<string, int> m;
    for (int i = 0; i < n; i++)
    {
        string book;
        cin >> book;

        m[book]++; // 책의 개수 +1
    }

    int _max = 0;                     // 가장 많이 팔린 책의 개수
    string answer = "";               // 가장 많이 팔린 책의 이름
    for (const auto &[book, cnt] : m) // 맵에 저장된 책을 하나 씩 살펴봄
        if (_max < cnt)               // 만약 현재까지 살펴본 최대 개수보다 더 많은 경우 (= 가장 많이 팔린 책 갱신 가능)
        {
            _max = cnt;    // 개수 갱신
            answer = book; // 이름 갱신
        }
    cout << answer;
}
