// 단체사진 찍기 (코딩테스트 연습 > 2017 카카오코드 본선 > 단체사진 찍기)
// https://programmers.co.kr/learn/courses/30/lessons/1835?language=cpp
/*
    sol.1) 완전 탐색 (next_permutation)
 */

#include <bits/stdc++.h>
using namespace std;
#define MAX 8 // 글자의 개수

bool isValid(const string &s, const string &q, int dist)
{
    char oper = q[3];
    int k = q.back() - '0';

    if (oper == '>' && dist > k)       return true;
    else if (oper == '=' && dist == k) return true;
    else if (oper == '<' && dist < k)  return true;

    return false;
}

int solution(int n, vector<string> data)
{
    string s = "ACFJMNRT";

    int ans = 0;
    do
    {
        bool flag = true; // 조건을 만족하는가?
        for (int i = 0; i < MAX && flag; i++)
            for (int j = 0; j < MAX && flag; j++)
            {
                char c1 = s[i], c2 = s[j];

                for (const auto &q : data)
                    if (c1 == q[0] && c2 == q[2] && !isValid(s, q, abs(i - j) - 1))
                        flag = false;
            }

        if (flag)
            ans++;
    } while (next_permutation(s.begin(), s.end()));

    return ans;
}

// int main()
// {
//     cout << solution(2, {"N~F=0", "R~T>2"}) << '\n'; // 3648
//     cout << solution(2, {"M~C<2", "C~M>1"}) << '\n'; // 0
// }

/*
    sol.2) 완전 탐색 (DFS)
 */

#include <bits/stdc++.h>
using namespace std;
#define MAX 8

constexpr char c[MAX] = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};

int visited[100];

bool isValid(const vector<string> &data)
{
    for (const string &s : data)
    {
        char c1 = s[0], c2 = s[2], oper = s[3];
        int k = s[4] - '0';

        int dist = abs(visited[c1] - visited[c2]) - 1;

        if (oper == '>' && !(dist > k))       return false;
        else if (oper == '<' && !(dist < k))  return false;
        else if (oper == '=' && !(dist == k)) return false;
    }

    return true;
}

void dfs(const vector<string> &data, int dep, int &ans)
{
    if (dep == MAX)
    {
        if (isValid(data)) // 조건에 충족하는가?
            ans++;
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        char cur = c[i];
        if (visited[cur])
            continue;

        visited[cur] = dep + 1;
        dfs(data, dep + 1, ans);
        visited[cur] = 0;
    }
}

int solution(int n, vector<string> data)
{
    fill(visited, visited + 100, 0);

    int ans = 0;
    dfs(data, 0, ans);

    return ans;
}

// int main()
// {
//     cout << solution(2, {"N~F=0", "R~T>2"}) << '\n'; // 3648
//     cout << solution(2, {"M~C<2", "C~M>1"}) << '\n'; // 0
// }
