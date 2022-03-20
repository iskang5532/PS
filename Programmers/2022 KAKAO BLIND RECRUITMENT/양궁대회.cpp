// 양궁대회 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > 양궁대회)
// https://programmers.co.kr/learn/courses/30/lessons/92342
/*
    DFS (완전 탐색)
    시간 복잡도: O(20C10 = 184,756) (중복 조합)
    풀이)
    - DFS를 이용해 라이언이 어파치를 이길 경우를 탐색.
    만약 점수 차가 이전 점수 차보다 높을 경우, 각 점수의 화살 개수를 저장.
    - 점수가 같을 경우, 낮은 점수를 많이 맞춘 결과를 반환해야 한다. 이를 위해 완전 탐색을 0점에서부터 수행.
    - 입력 arr는 [0]부터 10점임에 주의.
    - 만약 점수 차가 기본값, 즉 0일 경우, 라이언이 우승할 수 있는 경우가 없으므로 -1.
    etc.) 0점부터 10점까지를 0발부터 n발까지 하나씩 증가시키면서 완탐했더니 TLE 받음.
    참고)
    - 문제해설 및 참고: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;
#define MAX 11

int N;
int a[MAX], r[MAX]; // a[i] = k일 경우, 어파치가 i점을 k개 맞힘
int mx = 0;         // 점수차의 최댓값
vector<int> ans(MAX);

int get_gap()
{
    int ryan = 0, apeach = 0;
    for (int i = 0; i <= 10; i++)
        if (a[i] > r[i] || (a[i] != 0 && a[i] == r[i])) // 어파치의 화살 개수가 많거나 같을 경우
            apeach += i;
        else if (a[i] < r[i])
            ryan += i;

    return ryan - apeach;
}

void dfs(int dep, int pos)
{
    if (dep == N)
    {
        int gap = get_gap();
        if (gap > mx)
        {
            mx = gap; // 점수차의 최댓값을 갱신
            for (int i = 0; i <= 10; i++)
                ans[i] = r[10 - i];
        }
        return;
    }

    for (int i = pos; i <= 10; i++) // 0점부터 채워 나감 (중복 조합)
    {
        r[i]++;
        dfs(dep + 1, i);
        r[i]--;
    }
}

vector<int> solution(int n, vector<int> info)
{
    N = n;

    for (int i = 0; i <= 10; i++)
        a[10 - i] = info[i];

    dfs(0, 0);

    if (mx == 0)
        return {-1};
    else
        return ans;
}

// template <typename T>
// void print_ans(const vector<T> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << '\n';
// }
// int main()
// {
//     print_ans(solution(5, {2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}));  //	0,2,2,0,1,0,0,0,0,0,0
//     print_ans(solution(1, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));  //	-1
//     print_ans(solution(9, {0, 0, 1, 2, 0, 1, 1, 1, 1, 1, 1}));  //	1,1,2,0,1,2,2,0,0,0,0
//     print_ans(solution(10, {0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3})); //	1,1,1,1,1,1,1,1,0,0,2
// }