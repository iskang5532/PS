// 2022-10-11
// 12933 오리
// https://www.acmicpc.net/problem/12933
/*
    sol.1) 그리디, 구현 (2,028KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 입력된 문자열 s에서 문자를 하나씩 확인.
    인접한 문자(현재 문자가 'u'라면 이전 문자는 'q', 다음 문자는 'a')를 쉽게 확인할 수 있도록 맵에 {문자, 수} 형식으로 저장하여 사용.
    - 만들 수 있는 울음 소리를 cnt[] 저장.
    만약 s[0]이 'q'일 경우, cnt[0]++.
    만약 s[1]이 'u'이면서 'u'의 이전 소리인 'q'의 cnt[0]가 존재할 경우, cnt[0]--하면서 cnt[1]++.
    s[1]까지는 cnt[1]이 1이다. 즉, s[1]까지는 u까지 한 마리의 오리가 낼 수 있다.
    - 울음 소리가 완성됐을 경우, 이후에 나오는 울음 소리는 동일한 오리의 소리이다.
    즉, s[i]가 q일 경우 cnt[0]++이지만 cnt[4]의 값이 존재할 경우, cnt[4]-- 해준다.
    이는 'k'까지 도달한 오리는 새로운 울음 소리를 낼 수 있기 때문이다.
    - 'k'까지 도달한 경우, 오리의 수를 갱신해준다. (cnt[4]에 저장된 수는 'k'까지 우는 오리의 수이다.)
    - 이전 울음 소리, 즉 cnt[i - 1]이 0일 경우, 울음 소리를 완성할 수 없다.
    즉, 올바르지 않은 녹음이다.
    etc.) 왜맞틀 엄청 했었는데, 맞고 나서도 왜틀맞 한 풀이.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

const map<char, int> ch = {
    {'q', 0},
    {'u', 1},
    {'a', 2},
    {'c', 3},
    {'k', 4},
};

int cnt[5]{}; // cnt[3] = k일 경우, ch[3](= 'c')까지 낼 수 있는 오리는 k마리 (최대 혹은 최소가 아님)

bool isValid(const string &s)
{
    return (cnt[0] || cnt[1] || cnt[2] || cnt[3]) ? false
                                                  : true;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int ans = 0;
    bool valid = true;
    for (int i = 0; i < s.length() && valid; i++)
    {
        int cur = ch.at(s[i]);
        if (cur == 0)
        {
            cnt[cur]++;
            if (cnt[4]) // 완벽한 울음 소리를 낸 오리가 존재할 경우 (= 그 오리가 다시 욺)
                cnt[4]--;
        }
        else if (cur >= 1)
        {
            if (!cnt[cur - 1])
                valid = false;

            cnt[cur]++, cnt[cur - 1]--;
        }

        if (cur == 4)
            ans = max(ans, cnt[4]);
    }

    cout << (valid && isValid(s) ? ans : -1);
}

/*
    sol.2) 그리디, 구현 (2,028KB, 16ms)
    시간 복잡도: O(n^2)
    풀이)
    - 울음 소리가 완성됐을 경우, 이후에 나오는 울음 소리는 동일한 오리의 소리이다.
    - 첫 번째 문자열을 읽어가며 울음 소리가 완성되는지 확인.
    울음 소리가 한 번 이상 완성됐을 경우, ans++.
    완성된 울음 소리는 다른 문자(여기서는 null)로 변환해줌.
    - 2중 for문을 이용하여 모든 문자에 대해서 확인. (2500^2이므로 시간 내에 가능)
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 2'503 // max s.length()

const map<char, int> ch = {
    {'q', 0},
    {'u', 1},
    {'a', 2},
    {'c', 3},
    {'k', 4},
    {'\0', -1},
};

bool isValid(const string &s)
{
    for (const auto &c : s)
        if (c != '\0')
            return false;

    return true;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int ans = 0;
    bool valid = true;
    for (int st = 0; st < s.length() && valid; st++)
    {
        bool flag = false; // 한 번 이상 울음 소리가 완성됐는가
        for (int pos = st, c = 0; pos < s.length() && valid; pos++)
        {
            if (ch.at(s[pos]) == c)
                s[pos] = '\0', c++;

            if (c == 5)
                flag = true, c = 0;

            if (pos == s.length() - 1 && c != 0) // 마지막 문자에서 울음 소리가 완성되지 않았을 경우
                valid = false;
        }

        ans += flag;
    }

    cout << (valid && isValid(s) ? ans : -1);
}