// 6580 쿼드 트리
// https://www.acmicpc.net/problem/6580
/*
    분할 정복 (2,824KB, 8ms)
    시간 복잡도: ?
    풀이)
    - n x n의 크기로 이루어진 board. board에는 'W' 혹은 'B'가 저장되어 있음.
    - 입력된 헥사값을 10진수로 바꿔주기 위한 d.
    d에는 문자의 아스키코드에 16진수 값을 저장한다. (d['0'] = d[30] = 0, d['a'] = d[97] = 10)
    - getline으로 입력을 받은 후, stringstream으로 int형, 즉 n값을 빼온 후 저장.
    - n개의 라인에 헥사값들이 입력되는데, 열마다 1개가 아닌 n/8개의 헥사값이 들어오므로 각각 처리를 해줘야 한다.
    - 입력받은 헥사값을 10진수로 바꾼 값인 k를 이용해 board를 완성시켜준다.
    board에 값을 넣는 방법은, k에 존재하는 비트를 이용한다. 첫 번째 비트부터 board의 왼쪽 값이 되므로, 각 비트의 여부에 따라 board에 값을 할당해준다.
    이후 구해진 board로 분할 정복을 수행.
    - 기준점에서부터 len만큼 떨어진 곳까지 탐색.
    만약 기준점과 값이 다를 경우, 분할이 필요하므로 len / 2만큼의 범위를 잡은 후 네 부분으로 잘라 탐색해준다.
    만약 기준점과 값이 같을 경우, 분할이 필요 없으므로 정점의 값을 ans에 저장한다.
    etc.) 입력을 처리하는게 까다로웠던 문제.
    참고)
    - 16진수를 10진수로 바꾸는 방법: https://blog.naver.com/jinhan814/222474799089
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 512 + 1

int n; // 크기 (8 ≤ n ≤ 512, 2의 제곱꼴)
bool board[MAX][MAX];
int d[120]; // 문자의 아스키코드에 16진수 값을 저장 (= d['0'] = d[30] = 0, d['a'] = d[97] = 10)
string ans = "";

int get_decimal(const string &s) { return (d[s[2]] << 4) | d[s[3]]; }

bool isValid(int len, int y, int x) // 각 행렬의 값이 기준점과 같은가? (= 분할이 필요 없는가?)
{
    bool cur = board[y][x];
    for (int i = y; i < y + len; i++)
        for (int j = x; j < x + len; j++)
            if (cur != board[i][j])
                return false;

    return true;
}

void quadtree(int len, int y, int x)
{
    if (len == 1)
    {
        board[y][x] == true ? ans.push_back('B') : ans.push_back('W');
        return;
    }

    if (!isValid(len, y, x)) // 분할이 필요한 경우
    {
        ans.push_back('Q');

        int n_len = len >> 1;
        quadtree(n_len, y, x);
        quadtree(n_len, y, x + n_len);
        quadtree(n_len, y + n_len, x);
        quadtree(n_len, y + n_len, x + n_len);
    }
    else
        board[y][x] == true ? ans.push_back('B') : ans.push_back('W');
}

int main()
{
    FAST_IO;

    string idx;
    getline(cin, idx);
    stringstream ss(idx);
    ss >> idx >> idx >> n;
    getline(cin, idx);
    getline(cin, idx);

    for (int i = 0; i < 16; i++)
        d["0123456789abcdef"[i]] = i; // 아스키코드 값에 16ㅈ

    for (int y = 0; y < n; y++)
    {
        string s;
        cin >> s;

        int l = 0;
        while (l * 5 < s.length()) // l개의 헥사값 (5개씩 문자를 확인)
        {
            int k = get_decimal(string(s.begin() + l * 5, s.begin() + l * 5 + 5)); // 헥사값을 10진수로

            for (int x = 0 + (8 * l), pos = 0; x < 8 + (8 * l); x++) // y행에서 8칸씩 확인
                board[y][x] = k & 1 << pos, pos++;

            l++;
        }
    }
    cin >> idx;

    quadtree(n, 0, 0); // get ans

    cout << n << endl;
    cout << ans;
}