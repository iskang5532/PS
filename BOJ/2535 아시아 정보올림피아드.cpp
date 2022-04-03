// 2535 아시아 정보올림피아드
// https://www.acmicpc.net/problem/2535
/*
    구현, 정렬 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 동일한 성적을 가진 학생이 존재하지 않으므로, 단순히 성적을 기준으로 정렬해주면 된다.
    - 해당 국가의 메달 획득 개수를 저장할 배열 cnt. (cnt[i] = k일 때, i번 국가의 메달 획득 개수는 k개)
    - 첫 번째 학생(= 성적이 가장 높은 학생)부터 메달을 수여할 지 확인.
    만약 해당 학생이 속한 국가의 메달의 개수가 2개 미만인 경우 메달을 수여.
    만약 해당 학생이 속한 국가의 메달의 개수가 2개 이상일 경우, 다음 학생을 탐색.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'003

struct P
{
    int a, b, c; // 국가 번호 a, 학생 번호 b, 성적 c(0 ≤ c ≤ 1, 000)

    friend bool operator<(const P &p1, const P &p2) { return p1.c > p2.c; } // 점수 기준으로 오름차순 정렬
};

int main()
{
    FAST_IO;

    int n; // 학생 수 (3 ≤ N ≤ 100)
    cin >> n;
    vector<P> v(n);
    for (auto &[a, b, c] : v)
        cin >> a >> b >> c;

    sort(v.begin(), v.end()); // 점수 기준으로 오름차순 정렬

    int cnt[MAX]{}; // cnt[i] = k일 때, i번 국가의 메달 획득 개수는 k개
    for (int i = 0, t = 3; i < n && t; i++)
    {
        auto [a, b, c] = v[i];
        if (cnt[a] < 2)
        {
            cout << a << ' ' << b << endl;
            cnt[a]++, t--;
        }
    }
}