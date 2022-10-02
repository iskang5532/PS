// 2022-09-26
// 5635 생일
// https://www.acmicpc.net/problem/5635
/*
    맵 (2,028KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 연도 yy, 월 mm, 일 dd 중 yy와 mm을 일로 바꾼 후 dd와 합쳐 저장.
    이후, dd를 기준으로 정렬.
    - 해당 dd에 맞는 이름을 저장해야 하므로, 맵을 사용함.
    - 맵에 저장된 값은 key를 기준으로 오름차순 정렬이 됨.
    그러므로, 나이가 적은 사람은 뒷 값을, 나이가 많은 사람은 앞 값을 출력한다.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

map<int, string> m; // m[k] = name일 때, name은 0년 0월 0일로부터 k일이 지남

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name;
        int dd, mm, yy;
        cin >> name >> dd >> mm >> yy;

        m[yy * 365 + mm * 31 + dd] = name;
    }

    cout << m.rbegin()->second << endl;
    cout << m.begin()->second << endl;
}
