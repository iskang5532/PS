// 2022-06-24
// 9536 여우는 어떻게 울지?
// https://www.acmicpc.net/problem/9536
/*
    맵, 파싱 (2,084KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 동물의 울음소리 중 소리를 맵에 저장.
    - 울음소리의 입력이 끝났을 경우, 녹음된 소리의 문자열마다 확인.
    만약 확인중인 문자열 s가 맵에 존재할 경우, 다음 문자열을 확인.
    만약 확인중인 문자열 s가 맵에 존재하지 않을 경우, 여우의 울음소리를 저장할 ans에 공백과 함께 저장.
 */

#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

unordered_map<string, bool> get_cry()
{
    unordered_map<string, bool> m;

    string s;
    while (getline(cin, s) && s != "what does the fox say?")
    {
        stringstream ss(s);
        string cry;
        ss >> cry >> cry >> cry;
        m[cry] = true;
    }

    return m;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    cin.ignore();
    while (tc--)
    {
        string record;
        getline(cin, record);

        unordered_map<string, bool> m = get_cry(); // 다른 동물의 울음소리를 저장

        string ans;
        stringstream ss(record);
        while (!ss.eof())
        {
            string s;
            ss >> s;

            if (!m[s]) // 다른 동물의 울음소리가 아닌가? (= 여우의 울음소리인가?)
                ans += s + ' ';
        }

        cout << ans << endl;
    }
}