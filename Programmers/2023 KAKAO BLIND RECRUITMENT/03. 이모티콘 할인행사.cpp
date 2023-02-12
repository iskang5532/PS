// 2023-01-28
// 이모티콘 할인행사 (코딩테스트 연습 > 2023 KAKAO BLIND RECRUITMENT > 이모티콘 할인행사)
// https://school.programmers.co.kr/learn/courses/30/lessons/150368
/*
    DFS
    시간 복잡도: ?
    풀이)
    - 유저의 수와 이모티콘의 개수, 그리고 할인율의 개수가 크지 않다.
    그러므로 DFS를 이용하여 할인율에 따른 유저의 구매 목록을 구하여 정답을 구한다.
    - 각 이모티콘마다 10%에서 40%까지 네 가지의 할인율를 각각 적용한다. (rate[]에 저장)
    모든 이모티콘에 할인율이 적용되었다면, 각 유저마다 구매한 이모티콘의 가격을 구한다.
    만약 구매한 가격이 유저가 원하는 가격을 넘었을 경우, 해당 유저는 서비스에 가입한다.
    - 할인율에 따른 모든 유저의 상태 cnt, tot을 구한 후, 기존에 구한 가입자의 수 a와 매출액 b와 비교한다.
    만약 cnt > a, 즉 현재 할인율로 인해 가입자가 더 많은 경우, 가입자의 수 및 매출액을 a와 b에 저장한다.
    만약 cnt == a, 즉 가입자가 같을 경우 기존 매출액 b와 현재 매출액 tot 중 더 큰 값을 b에 저장한다.
    - 최종적으로 구한 a와 b를 벡터에 저장하여 반환한다.
    etc.) 이모티콘의 할인율은 총 네 가지. 지문 뿐만 아니라 제한사항에도 적어줬으면 좋겠다.
    참고)
    - https://school.programmers.co.kr/questions/42013 (할인율의 개수)
 */

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
#define MAX 10 // max emoticons size

vector<vector<int>> users;
vector<int> emoticons;
int rate[MAX]; // i번 이모티콘의 할인율 (rate[i] = k일 경우, i번 이모티콘의 할인율은 k)
int a, b;

void dfs(int dep = 0)
{
    if (dep == emoticons.size())
    {
        int cnt = 0, tot = 0; // 서비스 가입자의 수, 매출액 (현재 할인율에 따른 값)
        for (const auto &user : users)
        {
            int r = user[0], k = user[1]; // 유저가 원하는 비율 및 가격

            int sum = 0; // 구매한 이모티콘 가격의 합
            for (int i = 0; i < emoticons.size(); i++)
                if (rate[i] >= r) // 구매 가능한 비율일 경우
                    sum += emoticons[i] - (emoticons[i] / 100 * rate[i]);
            sum >= k ? cnt++ // 원하는 가격을 넘었을 경우, 서비스에 가입
                     : tot += sum;
        }

        if (cnt > a)
            a = cnt, b = tot;
        else if (a == cnt)
            b = max(b, tot);

        return;
    }

    for (const int _rate : {10, 20, 30, 40}) // 할인율
    {
        rate[dep] = _rate;

        dfs(dep + 1);
    }
}

vector<int> solution(vector<vector<int>> _users, vector<int> _emoticons)
{
    users = _users, emoticons = _emoticons;

    vector<int> ans;

    dfs();

    return vector{a, b};
}

template <typename T>
void print_ans(const vector<T> &arr)
{
    for (const auto &elem : arr)
        cout << elem << " ";
    cout << '\n';
}
int main()
{
    print_ans(solution({{40, 10000}, {25, 10000}}, {7000, 9000})); // 1 5400
    print_ans(solution({{40, 2900}, {23, 10000}, {11, 5200}, {5, 5900}, {40, 3100}, {27, 9200}, {32, 6900}},
                       {1300, 1500, 1600, 4900})); // 4 13860
}