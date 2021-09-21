/* 
 * 1759 암호 만들기
 * brute-force, nextg_permutation
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1759
 * etc.) next_permutation을 이용한 풀이가 더 간단해서 좋은듯.
 * 참고: https://blog.naver.com/jinhan814/222131161691 (state 초기화에 대한 참고)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define endl "\n"

bool isValid(const string &ans)
{
    int a = 0, b = 0; // 자음 및 모음의 개수
    for (const auto &c : ans) // 암호의 문자를 하나씩 검사
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') // 모음일 경우
            b++;
        else // 자음일 경우
            a++;

    if (a >= 2 && b >= 1) // 조건에 만족하는 경우 (자음이 둘 이상, 모음이 하나 이상)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 암호의 길이 및 암호 후보 개수 (3 <= n, m <= 15)
    cin >> n >> m;

    vector<char> str(m);
    for (auto &c : str)
        cin >> c;
    sort(str.begin(), str.end()); // 출력이 오름차순을 요하기 때문에 입력값을 정렬시켜 줌

    vector<bool> state(m, true);                   // 선택(= 0)할 문자. 000011일 경우, 0, 1, 2, 3을 이용하여 암호를 만듬
    fill(state.begin(), state.begin() + n, false); // 전체를 1로 한 후, n만큼 0으로 초기화 (최솟값으로)
    do
    {
        string ans = "";
        for (int i = 0; i < m; i++)    // 선택된 문자들을 확인
            if (!state[i])             // false인 경우 (= 선택)
                ans.push_back(str[i]); // 문자를 넣음

        if (isValid(ans)) // 현재 완성된 암호가 조건에 부합하는 경우
            cout << ans << endl;
    } while (next_permutation(state.begin(), state.end())); // 순열을 이용하여 선택될 문자를 만듬
}