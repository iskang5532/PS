// 2023-01-30
// 11507 카드셋트
// https://www.acmicpc.net/problem/11507
/*
    파싱 (2,076KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열은 문자+숫자가 반복되는 형식이다.
    stringstream을 이용하여 문자와 숫자를 추출한다.
    - used에 가지고 있는 카드를 저장하며, 동일한 카드가 나왔을 경우 상태를 flag에 저장하여 출력을 바꿈.
    - 잃어버린 카드의 개수를 저장할 loss. (모양의 개수를 저장)
    - 출력 시, 각 모양의 최대 개수 13개에서 잃어버린 카드의 개수 loss를 뺀 값을 출력.
 */

#include <iostream>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

bool used['z'][17]; // used['P'][13] = true일 경우, P13은 가지고 있음

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int flag = true, loss['z']{}; // 똑같은 카드의 여부 flag, loss['P'] = k일 경우, 잃어버린 P의 개수는 k

    char ch; // 카드의 모양
    int num; // 카드의 숫자
    stringstream ss(s);
    while (ss >> ch >> num)
    {
        if (used[ch][num]) // 앞서 나온 카드인 경우 (= 중복)
            flag = false;
        loss[ch]++, used[ch][num] = true;
    }

    if (!flag)
        cout << "GRESKA";
    else
        for (const char &c : {'P', 'K', 'H', 'T'})
            cout << 13 - loss[c] << ' ';
}