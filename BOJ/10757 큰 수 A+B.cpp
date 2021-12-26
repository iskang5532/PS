// 10757 큰 수 A+B
// https://www.acmicpc.net/problem/10757
/*
    sol.1) 구현 (2,168KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 각 문자열의 뒷자리를 빼내어 더한 후, 더한 값을 ans에 저장.
    두 문자열이 빌 때까지 혹은 sum 값이 없어질 때까지 반복.
    etc.) 시간이 오래 걸릴듯 싶은 풀이
 */

#include <iostream>
#include <algorithm>

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

    string a, b;
    cin >> a >> b;

    string ans = "";
    int sum = 0;
    // 문자열이 남아 있거나 sum 값이 남아 있거나 (= 수가 남았으며, ans에 넣어줘야 함)
    while (a.size() || b.size() || sum)
    {
        if (a.size())
            sum += a.back() - '0', a.pop_back();
        if (b.size())
            sum += b.back() - '0', b.pop_back();

        ans.push_back((sum % 10) + '0');
        sum /= 10;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
}