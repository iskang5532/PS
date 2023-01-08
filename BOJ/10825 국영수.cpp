// 2023-01-07
// 10825 국영수
// https://www.acmicpc.net/problem/10825
/*
    정렬 (6,720KB, 56ms)
    시간 복잡도: ?
    풀이)
    - 구조체 P를 만들어 이름과 세 과목의 점수를 만듦.
    - 입력받은 값을 P로 이루어진 벡터에 받은 후, 문제에서 주어진 조건에 맞춰 정렬.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

struct P
{
    string name; // 이름
    int a, b, c; // 국어, 영어, 수학

    friend bool operator<(const P &p1, const P &p2)
    {
        return p1.a != p2.a   ? p1.a > p2.a        // 1. 국어 점수가 감소하는 순서로
               : p1.b != p2.b ? p1.b < p2.b        // 2. 영어 점수가 증가하는 순서로 (1번을 거쳤으므로 국어 점수는 같음)
               : p1.c != p2.c ? p1.c > p2.c        // 3. 수학 점수가 감소하는 순서로 (2번을 거쳤으므로 국어 점수와 영어 점수가 같음)
                              : p1.name < p2.name; // 4. 이름이 사전 순으로 증가하는 순서로 (3번을 거쳤으므로 모든 점수가 같음)
    }
};

int main()
{
    FAST_IO;

    int n; // 학생의 수 (1 ≤ N ≤ 100,000)
    cin >> n;
    vector<P> v(n);
    for (auto &[name, a, b, c] : v)
        cin >> name >> a >> b >> c;

    sort(v.begin(), v.end());

    for (const auto &[name, a, b, c] : v)
        cout << name << endl;
}