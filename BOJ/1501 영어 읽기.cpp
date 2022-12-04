// 2022-11-30
// 1501 영어 읽기
// https://www.acmicpc.net/problem/1501
/*
    맵, 문자열 (2,616KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 뒤섞인 두 문자 s1, s2는 각각 정렬 후에 비교하게 된다면, 서로 같은 문자인지 확인할 수 있음.
    - 입력된 단어의 첫 문자와 끝 문자를 제외한 나머지 문자열인 중간 문자열을 정렬 후, 맵을 이용하여 단어의 개수를 저장.
    이때, 문자의 길이가 2 이하인 경우 중간 문자열은 존재하지 않음에 주의해야 한다.
    - 입력된 m개의 단어가 맵에 존재하는지 확인.
    만약 맵에 존재할 경우, ans에 값을 저장한다.
    경우의 수를 구해야 하므로, 맵에 존재하는 단어의 개수를 서로 곱해야 한다. (= ans *= m[s])
    참고)
    - 반례: https://www.acmicpc.net/board/view/104145
 */

#include <iostream>
#include <map>
#include <algorithm> // sort
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

map<string, int> M; // 중간 문자열이 정렬된 단어를 저장 (M[s] = k일 경우, 중간 문자열이 정렬된 단어 s는 k개)

int main()
{
    FAST_IO;

    int n; // 사전 속 단어의 개수 (0 ≤ n ≤ 10,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;

        if (word.length() >= 3)
            sort(word.begin() + 1, word.end() - 1); // 중간 문자열 정렬

        M[word]++;
    }
    int m; // 해석할 문장의 개수 (0 ≤ m ≤ 10,000)
    cin >> m;
    cin.ignore();
    for (int i = 0; i < m; i++)
    {

        string sentence;
        getline(cin, sentence);
        stringstream ss(sentence);

        int ans = 1;
        string word;
        while (ss >> word)
        {
            if (word.length() >= 3)
                sort(word.begin() + 1, word.end() - 1); // 중간 문자열 정렬

            ans *= M[word];
        }

        cout << ans << endl;
    }
}