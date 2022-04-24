// 2022-04-21
// 1244 스위치 켜고 끄기
// https://www.acmicpc.net/problem/1244
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 스위치를 저장할 v. ([1]부터 저장)
    - 학생 m명에 대해 성별 s와 수 k를 입력받음.
     - k번 스위치의 상태를 바꿔줌. (남학생과 여학생 모두 k번 스위치의 상태는 바꿈)
     - 현재 학생이 남학생일 경우, 임의의 수 i에 k를 부여한 후, i += k를 해주며 스위치의 상태를 바꿈.
     - 현재 학생이 여학생일 경우, k를 중심으로 좌측의 번호를 저장할 l, 우측의 번호를 저장할 r을 선언한 후, 범위 안에 있는 스위치의 상태를 탐색.
     만약 두 스위치의 상태가 같은 경우(= v[l] == v[r]), l번 스위치와 r번 스위치의 상태를 바꿈.
     만약 두 스위치의 상태가 다른 경우(= v[l] != v[r]), 다음 학생을 탐색.
    - 주의할 점은, 출력이 굉장히 깐깐하므로 공백 문자와 줄바꿈 문자 모두 올바르게 출력할 수 있도록 조건을 추가해야 한다.
    참고)
    - 출력 형식: https://help.acmicpc.net/judge/info (10개씩 끊어도 AC던데, 별로 상관없는듯)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 103

int main()
{
    FAST_IO;

    int n; // 스위치 개수 (1 ≤ n ≤ 100)
    cin >> n;
    int v[MAX];
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int m; // 학생의 수 (1 ≤ m ≤ 100)
    cin >> m;
    while (m--)
    {
        int s, k;
        cin >> s >> k;

        v[k] = !v[k];
        if (s == 1) // male
            for (int i = k + k; i <= n; i += k)
                v[i] = !v[i];
        else if (s == 2) // female
            for (int l = k - 1, r = k + 1; 1 <= l && r <= n; l--, r++)
            {
                if (v[l] != v[r])
                    break;
                v[l] = !v[l], v[r] = !v[r];
            }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << v[i];
        if (i % 20)
            cout << ' ';
        else
            cout << endl;
    }
}