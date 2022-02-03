// 1009 분산처리
// https://www.acmicpc.net/problem/1009
/*
    sol.1) 구현 (2,020KB, 800ms)
    시간 복잡도: ?
    풀이)
    - a를 b번 제곱할 경우, int형은 물론이고 long long형의 범위까지 벗어날 수 있다.
    - 사용될 컴퓨터의 개수는 총 10개이다. 그러므로 10을 넘는 값은 필요가 없어지며, 10 이하로 줄여준다.
    이를 이용해 b번 제곱시킨 값은 10을 나눈 값으로 바꿔준다. (= =% 10)
    - 주의해야 할 점은, 10^1과 같을 꼴에 10의 나머지 값을 구하게 된다면 0이다. 그러나 0번째 컴퓨터는 없다.
    10^1은 10, 즉 10번째 컴퓨터이므로 값이 0이 되는 순간은 10을 출력해줘야 한다.
    etc.) 컴퓨터의 번호가 1번부터 10번까지라 헷갈렸음. (10^1과 같은 케이스)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MUL 10

int sol(int a, int b)
{
    int ret = 1;
    for (int i = 1; i <= b; i++)
        ret = ret * a % MUL;

    if (ret == 0)
        return 10;
    return ret;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    while (tc--)
    {
        int a, b;
        cin >> a >> b;

        cout << sol(a, b) << endl;
    }
}

/*
    sol.2) 거듭제곱 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - b의 거듭제곱을 이용해 시간을 단축한다.
    - b가 246이며 2진법으로 바꾼 값은 '1111 0110'이다.
    작은 값부터, 즉 우측의 0부터 하나씩 확인하여 비트가 1일 경우 a를 곱해준다.
    a는 각 비트를 확인한 이후, 제곱시킨다.
    이를 이용해 지속해서 제곱 된 a의 값을 i번째 비트의 개수만큼, 즉 a를 1 << i만큼 곱해줄 수 있게 된다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MUL 10

int Pow(int a, int x)
{
    int ret = 1;
    for (int i = 1; i <= x; i++)
        ret *= a;

    return ret;
}

int sol(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1)
            ret = ret * a % MUL;

        b >>= 1;
        a = Pow(a, 2) % MUL; // == a * a % MUL
    }

    if (ret == 0)
        return 10;
    return ret;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    while (tc--)
    {
        int a, b;
        cin >> a >> b;

        cout << sol(a, b) << endl;
    }
}