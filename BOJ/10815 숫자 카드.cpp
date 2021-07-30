/* 
 * 10815 ���� ī��
 * ���� Ž�� (binary search)
 * �ð� ���⵵: ?
 * ����: https://www.acmicpc.net/problem/10815
 * ETC) �⺻���� ���� Ž�� STL�� �̿��� �����ε�
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &num : arr)
        cin >> num;
    sort(arr.begin(), arr.end()); // ���� Ž���� ���ؼ��� ��� �迭�� ���ؼ� ������ �ʿ���
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        cout << binary_search(arr.begin(), arr.end(), num) << endl; // ���� �迭���� ���� Ž������ ã�� ��, ������ true, ������ false�� ��ȯ
    }
}
