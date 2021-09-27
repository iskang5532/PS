/* 
 * 2621 카드게임
 * 구현
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2621
 * etc.) 첫 번째 풀이로 먼저 풀었는데 너무 어려웠음..
 */

// sol.1) 벡터에 숫자을 넣은 후에 정렬하여 인접한 숫자을 비교하여 구현
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define endl "\n"
#define MAX 5

int FLUSH; // default: false
int STRAIGHT = true;
int FOUR;
int THREE;
int TWO;
int ONE;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    vector<char> color(MAX);
    vector<int> num(MAX);
    for (int i = 0; i < MAX; i++)
        cin >> color[i] >> num[i];

    sort(color.begin(), color.end());
    if (color.front() == color.back()) // 정렬한 색이 앞과 뒤가 같은 경우 (= 모두 같음)
        FLUSH = true;

    sort(num.begin(), num.end());
    int cnt = 1; // 숫자이 같은 카드의 개수 (자신 포함)
    for (int i = 0; i <= MAX - 2; i++)
    {
        int curr = num[i], next = num[i + 1];
        if (curr + 1 != next)
            STRAIGHT = false;

        if (curr == next) // 현재 카드와 다음 카드가 같은 숫자인 경우
            cnt++;

        if (curr != next || i == MAX - 2) // 다음 카드와 숫자가 다르거나 확인할 카드가 마지막인 경우
            if (cnt == 2)
                if (!ONE)
                    ONE = curr, cnt = 1;
                else // (ONE)
                    TWO = curr, cnt = 1; // 앞서 원페어가 존재했을 경우, 투페어 true
            else if (cnt == 3)
                THREE = curr, cnt = 1;
            else if (cnt == 4)
                FOUR = curr, cnt = 1;
    }

    if (STRAIGHT && FLUSH)
        cout << 900 + num.back();
    else if (FOUR)
        cout << 800 + FOUR;
    else if (THREE && ONE)
        cout << 700 + (THREE * 10) + ONE;
    else if (FLUSH)
        cout << 600 + num.back();
    else if (STRAIGHT)
        cout << 500 + num.back();
    else if (THREE)
        cout << 400 + THREE;
    else if (TWO)
        cout << 300 + (TWO * 10) + ONE;
    else if (ONE)
        cout << 200 + ONE;
    else
        cout << 100 + num.back();
}


// sol.2) 벡터에 [숫자]++를 해주어 해당 숫자의 개수를 파악하여 구현하였으며, 스트레이트는 별도로 구함.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define endl "\n"
#define MAX 5
#define MAX_NUM 9 + 1

int FLUSH; // default: false
int STRAIGHT;
int FOUR;
int THREE;
int TWO;
int ONE;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    vector<char> color(MAX);
    vector<int> num(MAX_NUM, 0);
    int mx = 0; // 입력된 숫자들 중 최댓값
    for (int i = 0; i < MAX; i++)
    {
        int k;
        cin >> color[i] >> k;
        mx = max(mx, k), num[k]++; // 최댓값 갱신 및 숫자의 개수 +1
    }

    sort(color.begin(), color.end());
    if (color.front() == color.back()) // 정렬한 색이 앞과 뒤가 같은 경우 (= 모두 같음)
        FLUSH = true;

    for (int i = 1; i <= 5; i++)
        if (num[i] && num[i + 1] && num[i + 2] && num[i + 3] && num[i + 4]) // 구간 [i, i+4]의 값이 모두 같은 경우 (= 스트레이트)
            STRAIGHT = true;
    for (int i = 1; i <= 9; i++) // 숫자 1부터 9까지 확인
    {
        if (num[i] == 2)
            if (!ONE)
                ONE = i;
            else // (ONE)
                TWO = i; // 앞서 원페어가 존재했을 경우, 투페어 true
        else if (num[i] == 3)
            THREE = i;
        else if (num[i] == 4)
            FOUR = i;
    }

    if (STRAIGHT && FLUSH)
        cout << 900 + mx;
    else if (FOUR)
        cout << 800 + FOUR;
    else if (THREE && ONE)
        cout << 700 + (THREE * 10) + ONE;
    else if (FLUSH)
        cout << 600 + mx;
    else if (STRAIGHT)
        cout << 500 + mx;
    else if (THREE)
        cout << 400 + THREE;
    else if (TWO)
        cout << 300 + (TWO * 10) + ONE;
    else if (ONE)
        cout << 200 + ONE;
    else
        cout << 100 + mx;
}

// ans: 749
// R4B4B4B9B9  (44499)

// ans: 794
// R4B4B9B9B9 (44999)