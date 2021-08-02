/* ���� ���� ���̱ⱸ�� �αⰡ �ſ� ���� ���� ������ �ʽ��ϴ�.
 * �� ���̱ⱸ�� ���� �̿��� price�� �ε�, ���̱ⱸ�� N �� ° �̿��Ѵٸ� ���� �̿���� N�踦 �ޱ�� �Ͽ����ϴ�.
 * ��, ó�� �̿�ᰡ 100�̾��ٸ� 2��°���� 200, 3��°���� 300���� ����� �λ�˴ϴ�.
 * ���̱ⱸ�� count�� Ÿ�� �Ǹ� ���� �ڽ��� ������ �ִ� �ݾ׿��� �󸶰� ���ڶ������ return �ϵ��� solution �Լ��� �ϼ��ϼ���.
 * ��, �ݾ��� �������� ������ 0�� return �ϼ���. 

 * ���ѻ���
 * ���̱ⱸ�� �̿�� price : 1 �� price �� 2,500, price�� �ڿ���
 * ó�� ������ �ִ� �ݾ� money : 1 �� money �� 1,000,000,000, money�� �ڿ���
 * ���̱ⱸ�� �̿� Ƚ�� count : 1 �� count �� 2,500, count�� �ڿ���

 * ����� ��) price = 3, money = 20, count = 4 => result is 10*/

/* 
 * �ڵ��׽�Ʈ ���� - ��Ŭ�� ç���� - 1����
 * �ð� ���⵵: ?
 * ����: https://programmers.co.kr/learn/courses/30/lessons/82612?language=cpp
 */

using namespace std;

long long solution(int price, int money, int count)
{
    long long used = 0; // �� ��� �ݾ�
    for (int cnt = 1; cnt <= count; cnt++)
        used += price * cnt; // �̿� Ƚ���� ����ϸ� �ݾ� �߰�

    long long rem = money - used; // �̿�Ḧ ������ ���� �ݾ�
    if (rem < 0)
        return -rem;
    else
        return 0;
}