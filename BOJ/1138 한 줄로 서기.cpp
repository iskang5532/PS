// 2022-05-10
// 1138 한 줄로 서기
// https://www.acmicpc.net/problem/1138
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - vector STL의 insert()를 이용하여 기존 벡터 사이에 값을 추가. (추가되는 자리 뒤의 값들은 뒤로 밀림)
    - 입력된 값을 v에 저장한 후, 뒤에서부터 탐색.
    - 현재 탐색중인 값 v[i]는 왼쪽에 i+1보다 큰 값의 개수이다.
    즉, v[i]만큼 왼쪽에서 떨어진 위치에 i+1를 추가한다.
    이떄, insert를 이용하므로 i+1위치보다 뒤에 존재하는 값들은 뒤로 한칸씩 밀린다.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 13

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &i : v)
        cin >> i;

    vector<int> ans;
    for (int i = n - 1; i >= 0; i--)
        ans.insert(ans.begin() + v[i], i + 1); // insert(pos, val)

    for (const auto &i : ans)
        cout << i << ' ';
}