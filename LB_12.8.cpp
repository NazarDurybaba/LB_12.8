#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

// ������� ��� ��������� ������ �������� ������
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// ������� ��� ��������� ������ �������� � ����� ������
void append(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;
        head->next = head; // ������ ������ ��������
        head->prev = head;
    }
    else {
        Node* last = head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;
    }
}

// ������� ��� ����� ������ �� ������������ �������
void printClockwise(Node* head) {
    if (head == nullptr) return;
    Node* current = head;
    cout << "�� ������������ �������: ";
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

// ������� ��� ����� ������ ����� ����������� ������
void printCounterClockwise(Node* head) {
    if (head == nullptr) return;
    Node* current = head->prev;
    cout << "����� ����������� ������: ";
    do {
        cout << current->data << " ";
        current = current->prev;
    } while (current != head->prev);
    cout << endl;
}

// ������� ��� ������� ������ �������� �� ������ �������
void insertAtPosition(Node*& head, int position, int data) {
    if (head == nullptr || position <= 0) return;

    Node* newNode = createNode(data);
    Node* current = head;

    // ������ ������� ��� �������
    for (int i = 1; i < position && current->next != head; ++i) {
        current = current->next;
    }

    // ���������� ����� �������
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

// ������� ��� ��������� ����������� ��������
void deleteHead(Node*& head) {
    if (head == nullptr) return;
    if (head->next == head) { // ���� ���� ���� ������� � ������
        delete head;
        head = nullptr;
    }
    else {
        Node* temp = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
        delete temp;
    }
}

// ������� ��� ����� ������
void printList(Node* head) {
    if (head == nullptr) {
        cout << "������ �������" << endl;
        return;
    }
    Node* current = head;
    cout << "������: ";
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

int main() {

    SetConsoleOutputCP(1251);

    Node* head = nullptr;

    // ������� ��� � ���������� �����
    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "������� �������� �����!" << endl;
        return 1;
    }

    int value;
    while (inputFile >> value) {
        append(head, value);
    }
    inputFile.close();

    // �������� �������� ������ �� �� ����� ����������� ������
    printClockwise(head);
    printCounterClockwise(head);

    // ���������� ����� ������� �� ������ �������
    int position, newValue;
    cout << "������ ������� ��� ������� ������ ��������: ";
    cin >> position;
    cout << "������ �������� ������ ��������: ";
    cin >> newValue;
    insertAtPosition(head, position, newValue);
    printList(head);

    // ��������� ���������� �������
    deleteHead(head);
    printList(head);

    // ��������� ���'���, ���������� ���'�� ���������, ��� �������� ������ ���'��
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
