/* 
 * 1406 에디터
 * Linked List
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1406
 * ETC) Linked List를 이용한 풀이. 구현 자체가 어렵고 헷갈림. 주석들을 참고해가며 이해할 것.
 * 참고: https://zoomkoding.github.io/algorithm/2019/06/29/Linked-list-1.html
 */

#include <iostream>

using namespace std;

#define endl "\n"

struct Node
{
    Node *prev, *next; // 해당 노드의 [이전 노드], [다음 노드]
    char data;

    Node() // 처음 입력된 값으로 노드를 생성할 때 (= 중간에 삽입하는 노드가 아닌)
    {
        // 생성된 노드의 기본 값 설정 (= 아무 것도 없음)
        prev = next = nullptr;
        data = ' '; // = NULL
    };
    Node(Node *node, char c) // 중간에 삽입하는 노드를 생성함
    {
        // this: 새로 만들 노드. 새 노드를 기존 노드들 사이에 넣어 줘야 함
        // 새 노드와 다음 노드를 이어주며, 새 노드와 이전 노드를 이어줌
        this->next = node->next, next->prev = this;
        node->next = this, this->prev = node;

        data = c;
    }

    void deleted() // 여기서 this는 List에서의 위치 pos의 앞 노드 (= pos 앞의 노드를 제거)
    {
        // 이전 노드와 다음 노드끼리 연결시킴 (= 현재 노드와의 연관성이 없어짐)
        prev->next = this->next, next->prev = this->prev;
        delete this; // 현재 노드는 필요가 없으므로 해제시킴
    };
};

class Linked_List
{
    Node *head, *pos; // 가장 처음 노드 head와 리스트를 옮겨 다닐 pos

public:
    Linked_List() // 리스트 선언
    {
        // 생성된 리스트에 head와 pos 두 노드를 생성하며, 서로 연결시켜 줌 (head - pos이며, pos 자리에는 값 자체가 없는 느낌으로)
        head = new Node();
        pos = new Node();
        head->next = pos, pos->prev = head;
    };

    void moved_left()
    {
        if (pos->prev != head) // 이전 노드가 마지막이 아닌 경우만
            pos = pos->prev;
    };
    void moved_right()
    {
        if (pos->data != ' ') // 현재 노드가 마지막이 아닌 경우만
            pos = pos->next;
    };
    void inserted(const char &c) { new Node(pos->prev, c); }; // 현재 위치의 앞에 노드를 생성
    void deleted()
    {
        if (pos->prev != head)    // 이전 위치가 마지막이 아닌 경우
            pos->prev->deleted(); // 현재 노드의 이전 노드를 제거 시킴
    };
    void print()
    {
        Node *tour = head->next; // 리스트 전체를 훑어줄 노드 생성

        while (tour->data != ' ')
        {
            // 현재 위치의 노드에 대한 값을 출력 후, 다음 위치로 이동
            cout << tour->data;
            tour = tour->next;
        }

        delete tour; // 사용을 마쳤으니 제거 (print를 빠져 나갈 때 제거가 되는가?? 제거 되면 필요 없는 라인)
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    // Linked List 생성. 이 안에 Node들이 존재함.
    Linked_List *list = new Linked_List();

    string str;
    cin >> str;
    for (const auto &c : str)
        list->inserted(c);

    int i;
    cin >> i;
    while (i--)
    {
        char cmd;
        cin >> cmd;
        switch (cmd)
        {
        case 'L':
            list->moved_left();
            break;
        case 'D':
            list->moved_right();
            break;
        case 'B':
            list->deleted();
            break;
        case 'P':
            cin >> cmd;
            list->inserted(cmd);
            break;
        }
    }

    list->print();
}