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

// Функція для створення нового елементу списку
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// Функція для додавання нового елементу в кінець списку
void append(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;
        head->next = head; // робимо список кільцевим
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

// Функція для друку списку за годинниковою стрілкою
void printClockwise(Node* head) {
    if (head == nullptr) return;
    Node* current = head;
    cout << "За годинниковою стрілкою: ";
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

// Функція для друку списку проти годинникової стрілки
void printCounterClockwise(Node* head) {
    if (head == nullptr) return;
    Node* current = head->prev;
    cout << "Проти годинникової стрілки: ";
    do {
        cout << current->data << " ";
        current = current->prev;
    } while (current != head->prev);
    cout << endl;
}

// Функція для вставки нового елементу на задану позицію
void insertAtPosition(Node*& head, int position, int data) {
    if (head == nullptr || position <= 0) return;

    Node* newNode = createNode(data);
    Node* current = head;

    // Шукаємо позицію для вставки
    for (int i = 1; i < position && current->next != head; ++i) {
        current = current->next;
    }

    // Вставляємо новий елемент
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

// Функція для видалення заголовного елементу
void deleteHead(Node*& head) {
    if (head == nullptr) return;
    if (head->next == head) { // Якщо лише один елемент у списку
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

// Функція для друку списку
void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній" << endl;
        return;
    }
    Node* current = head;
    cout << "Список: ";
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

int main() {

    SetConsoleOutputCP(1251);

    Node* head = nullptr;

    // Зчитуємо дані з текстового файлу
    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    int value;
    while (inputFile >> value) {
        append(head, value);
    }
    inputFile.close();

    // Виводимо елементи списку за та проти годинникової стрілки
    printClockwise(head);
    printCounterClockwise(head);

    // Вставляємо новий елемент на задану позицію
    int position, newValue;
    cout << "Введіть позицію для вставки нового елементу: ";
    cin >> position;
    cout << "Введіть значення нового елементу: ";
    cin >> newValue;
    insertAtPosition(head, position, newValue);
    printList(head);

    // Видаляємо заголовний елемент
    deleteHead(head);
    printList(head);

    // Звільняємо пам'ять, вивільнення пам'яті необхідне, щоб уникнути витоку пам'яті
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
