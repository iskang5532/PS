/* 
 * 13711 LCS 4
 * LIS
 * 시간 복잡도: O(NlogN)
 * 문제: https://www.acmicpc.net/problem/13711
 * etc.) 각 수열에서의 값은 중복되지 않으며, n까지의 값이 입력됨.
 * LIS 풀이를 이용한 LCS 풀이
 * 참고: https://travelbeeee.tistory.com/490 (이론 참고)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    // 수열의 값을 위치에 대하여 저장
    vector<int> a(n + 1); // 정의: a[k]일 경우, a[k]는 수열 A에서 k값의 위치
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        a[k] = i; // k값의 위치는 i
    }

    // 정의된 a를 이용하여 수열 B에 대한 b를 생성. (b는 수열 A와 수열 B를 합친 느낌)
    vector<int> b(n + 1); // 정의: b[i]일 경우, b는 a에서 k값의 위치이며, i개의 k가 입력됨
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        b[i] = a[k]; // a[k]: 수열 a에서 값 k의 위치
    }
    // 수열 A:  [6 1 5 3 2 4]
    // pos_A:   1 2 3 4 5 6
    // 수열 B:  [3 1 4 5 6 2]
    // b:       4 2 6 3 1 5 수열 A에서 B[i]값과 동일한 값의 위치를 찾아 i번째에 저장

    vector<int> lis;
    for (int i = 1; i <= n; i++)
    {
        int k = b[i];
        auto pos = lower_bound(lis.begin(), lis.end(), k);

        if (pos == lis.end())
            lis.push_back(k);
        else
            *pos = k;
    }

    cout << lis.size();
}

// 6 1 5 3 2 4
// 3 1 4 5 6 2
// ans 3

/* ____extended____ */
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// #define endl "\n"

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL), cout.tie(NULL);

//     int n;
//     cin >> n;

//     vector<int> a(n);
//     for (auto &elem : a)
//         cin >> elem;
//     vector<int> b(n);
//     for (auto &elem : b)
//         cin >> elem;

//     vector<int> _b(n); // b의 값을 순서(= 번호)로 저장
//     for (int pos = 0; pos < n; pos++)
//     {
//         int k = b[pos] - 1;
//         _b[k] = pos; // b의 k번째 값은 pos번째
//     }

//     vector<int> c(n); // i번째 값에 a[i]값을 이용해 _b값(= b값의 번호)을 찾아 저장
//     for (int i = 0; i < n; i++)
//     {
//         int pos = a[i] - 1;
//         c[i] = _b[pos];
//     }

//     vector<int> lis;
//     for (int i = 0; i < n; i++)
//     {
//         int k = c[i];
//         auto pos = lower_bound(lis.begin(), lis.end(), k);

//         if (pos == lis.end())
//             lis.push_back(k);
//         else
//             *pos = k;
//     }
//     cout << lis.size();
// }