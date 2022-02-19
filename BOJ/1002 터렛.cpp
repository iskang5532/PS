// 1002 터렛
// https://www.acmicpc.net/problem/1002
/*
    수학, 기하학 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 두 점 사이의 거리 l을 구해준 후, 두 원에 의한 교점의 개수를 구해준다.
    1. 만약 두 점이 겹쳐있는 경우 (l == 0)
     1-1. 두 원의 반지름이 같을 경우, 교점의 개수는 무한개이다. (완전히 일치)
     1-2. 두 원의 반지름이 다를 경우, 교점의 개수는 0개이다.
    2. 만약 l이 적당한 거리일 경우, 교점의 개수는 2개이다. (반례 참고)
    적당한 거리란, 두 반지름의 합보다 작으며 차보다 클 때이다.
    3. 만약 l이 두 반지름의 합 혹은 차와 같을 경우, 교점의 개수는 1개이다. (외접 혹은 내접)
    4. 그 외의 경우, 교점의 개수는 0개이다.
    etc.)
    - 두 점 간의 거리가 맨해튼 거리인 줄 알고 헤맨 문제.
    - p1과 p2를 뭐라고 불러야 하는가?
    참고)
    - 두 점 사이의 거리: https://ko.wikipedia.org/wiki/%EB%91%90_%EC%A0%90_%EC%82%AC%EC%9D%B4%EC%9D%98_%EA%B1%B0%EB%A6%AC
    - 그림 설명: https://gaeunhan.tistory.com/57
                https://mjeong9316.tistory.com/157
 */

#include <iostream>
#include <cmath>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int x1, y1, r1, x2, y2, r2; // |(x1, y1, x2, y2)| ≤ 10,000, 1 ≤ r1, r2 ≤ 10,000
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        int l = pow((x1 - x2), 2) + pow((y1 - y2), 2); // 두 점 사이의 거리
        int p1 = pow(r1 - r2, 2), p2 = pow(r1 + r2, 2);

        if (l == 0) // 두 점이 겹쳐있는 경우
            if (r1 == r2)
                cout << "-1" << endl;
            else
                cout << '0' << endl;
        else if (p1 < l && l < p2)
            cout << '2' << endl;
        else if (l == p1 || l == p2) // 외접 혹은 내접
            cout << '1' << endl;
        else
            cout << '0' << endl;
    }
}

// 3
// 1 1 3 2 2 1
// 0 0 7 6 0 2
// 0 0 1 10 10 1
// ans: 0 2 0