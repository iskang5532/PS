// 1076 저항
// https://www.acmicpc.net/problem/1076
/*
    맵 (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 맵에 저항의 색과 값, 곱을 저장함.
    - 입력된 세 개의 색을 맵에 저장된 값을 사용하여 결과를 생성.
    - 주의할 점은, 예제 입력 3처럼 int형 범위를 벗어날 수 있으므로 long long을 취해줌.
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define val first
#define mul second
using pii = pair<int, int>;

unordered_map<string, pii> um = {
    {"black", {0, 1}},
    {"brown", {1, 10}},
    {"red", {2, 100}},
    {"orange", {3, 1'000}},
    {"yellow", {4, 10'000}},
    {"green", {5, 100'000}},
    {"blue", {6, 1'000'000}},
    {"violet", {7, 10'000'000}},
    {"grey", {8, 100'000'000}},
    {"white", {9, 1'000'000'000}},
}; // color, val, mul

int main()
{
    FAST_IO;

    string a, b, c;
    cin >> a >> b >> c;

    cout << (10LL * um[a].val + um[b].val) * um[c].mul;
}