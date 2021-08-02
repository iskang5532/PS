#include <bits/stdc++.h>
using namespace std;
int n, m, psum[1025][1025];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int col = 0; col < n; col++)
    {
        for (int row = 0; row < n; row++)
        {
            int a;
            cin >> a;
            psum[col + 1][row + 1] = psum[col + 1][row] + psum[col][row + 1] - psum[col][row] + a;
        }
    }
    for (int col = 0; col < m; col++)
    {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        cout << psum[p][q] - psum[x - 1][q] - psum[p][y - 1] + psum[x - 1][y - 1] << "\n";
    }
}
