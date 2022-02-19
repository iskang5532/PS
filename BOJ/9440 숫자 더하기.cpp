// 9440 숫자 더하기
// https://www.acmicpc.net/problem/9440
/*
    그리디 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 나눠진 두 값 l과 r이 작은 값이 되어야 한다.
    이는, 입력된 n개의 값 중 작은 값을 골라 l과 r에 골고루 넣으면 된다.
    - l과 r의 가장 큰 자릿수(= 시작값)의 수는 0이 되면 안 된다. 그러므로 값이 추가된 l과 r에 시작값이 0일 경우, 따로 처리해주거나 0이 될 수 없도록 해준다.
    이 풀이는 후자인 v를 조정하여 l과 r의 시작값이 0이 되지 않도록 만든다. (= func())
    1. 입력된 값을 v에 저장한 후, 오름차순 정렬을 해준다. (l과 r에 골고루 분포시킬 수 있도록)
    2. 함수 func에 v를 넣은 후, v의 첫 번째와 두 번째 값이 0이 되지 않도록 한다.
     - v에서 0이 아닌 값의 위치를 찾은 후 pos에 저장.
     - 만약 v[0] == 0일 경우, v[0]과 v[pos]를 바꿔 0이 되지 않도록 한다. (l의 시작값은 0이 아니게 됨.)
     - 만약 v[1] == 0일 경우, v[1]과 v[pos + 1]을 바꿔 0이 되지 않도록 한다. (r의 시작값은 0이 아니게 됨.)
     이때 주의할 점은, [pos + 1]이 존재하지 않을 수도 있다. 그러므로, pos + 1의 최솟값인 [3]이 존재할 때 스왑할 수 있도록 한다.
    3. v에 저장된 값을 l과 r에 순차적으로 넣어준다.
    4. l과 r을 더하여 출력한다.
    참고)
    - 그리디 방법: https://blog.naver.com/jinhan814/222609762108
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

void func(vector<int> &v)
{
    int pos = 0; // 0이 아닌 값의 시작 위치
    while (v[pos] == 0)
        pos++;

    swap(v[0], v[pos]);
    if (v.size() > 3)
        swap(v[1], v[pos + 1]);
}

int main()
{
    FAST_IO;

    int n;
    while (cin >> n)
    {
        if (n == 0)
            break;

        vector<int> v(n);
        for (auto &i : v)
            cin >> i;

        sort(v.begin(), v.end());

        func(v); // [0]과 [1]을 0이 아니도록 만들어줌

        string l, r;
        for (int i = 0; i < n; i++)
            if (i & 1)
                l.push_back(v[i] + '0');
            else
                r.push_back(v[i] + '0');

        cout << stoi(l) + stoi(r) << endl;
    }
}

/*
    완전 탐색 (2,024KB, 16ms)
    시간 복잡도: O(n^2)
    풀이)
    - 나눠진 두 값 l과 r이 작은 값이 되어야 한다.
    입력될 값의 개수 n이 작으므로, 완전 탐색을 이용해 l과 r의 값을 구해준다.
    - l과 r의 가장 큰 자릿수(= 시작값)의 수는 0이 되면 안 된다. 그러므로 값이 추가된 l과 r에 시작값이 0일 경우, 따로 처리해주거나 0이 될 수 없도록 해준다.
    이 풀이는 전자인 l과 r을 조정하여 시작점이 0이 되지 않도록 만든다. (= func())
    1. 입력된 값을 v에 저장한 후, 오름차순 정렬을 해준다. (l과 r에 작은 값이 먼저 입력되도록)
    2. 완전 탐색을 이용해 l과 r에 넣을 v의 원소를 선정한 후, 넣어준다.
    3. l과 r이 고른 상태인지를 확인하며, 고르지 못할 시 l과 r을 다시 만든다.
     - l 혹은 r이 비어있을 경우
     - l 혹은 r이 0으로만 이루어진 경우
    4. l과 r의 시작값이 0일 경우, 0 외의 가장 작은 값과 바꾼다.
    5. l + r값과 ans를 비교해 더 작은 값을 ans에 저장.
    이후 2번을 반복한다.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
using ll = long long;

bool isValid(const string &s1, const string &s2)
{
    if (s1.empty() || s2.empty())
        return false;

    if ((s1.front() == '0' && s1.back() == '0') || (s1.front() == '0' && s1.back() == '0')) // 0으로만 이루어진 경우
        return false;

    return true;
}

void func(string &s) // [0]을 0이 아니도록 만듦
{
    if (s.front() == '0')
    {
        int pos = 0;
        while (s[pos] == '0')
            pos++;

        swap(s[0], s[pos]);
    }
}

int main()
{
    FAST_IO;

    int n;
    while (cin >> n)
    {
        if (n == 0)
            break;

        vector<int> v(n);
        for (auto &i : v)
            cin >> i;

        sort(v.begin(), v.end());

        int ans = INF;
        for (int bit = 0; bit < 1 << n; bit++) // brute-force
        {
            string l, r;
            for (int i = 0; i < n; i++)
                if (bit & 1 << i)
                    l.push_back(v[i] + '0');
                else
                    r.push_back(v[i] + '0');

            if (!isValid(l, r))
                continue;

            func(l), func(r);

            ans = min(ans, stoi(l) + stoi(r));
        }

        cout << ans << endl;
    }
}