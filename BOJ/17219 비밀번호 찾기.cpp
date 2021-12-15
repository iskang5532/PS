// 17219 비밀번호 찾기
// https://www.acmicpc.net/problem/17219
/*
    map (16,448KB, 160ms)
    시간 복잡도: ?
    풀이)
    - n개의 주소 및 비밀번호를 입력받은 후, 맵에 id = pw꼴로 저장시켜줌.
    이후 m개의 주소를 입력받은 후, 아이디(= key)에 맞는 비밀번호(= value)를 출력.
    etc.) 맵을 이용한 기본적인 문제인듯
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 저장된 주소의 수 n, 찾으려는 주소의 수 m (1 ≤ n, m ≤ 100,000)
    cin >> n >> m;

    unordered_map<string, string> um;
    for (int i = 0; i < n; i++)
    {
        string id, pw; // 1 ≤ len() ≤ 20
        cin >> id >> pw;
        um[id] = pw;
    }
    for (int i = 0; i < m; i++)
    {
        string id;
        cin >> id;
        cout << um[id] << endl;
    }
}