#include <iostream>

using namespace std;

template <typename T>
class List {
    struct Node {
        Node* next;
        T value;
        int index;

        Node(T value, int index) {
            this->value = value;
            next = nullptr;
            this->index = index;
        }
    };

    Node* current;
    int size = 0;

    T findElement(Node* next, T value) {
        if (next->value == value) {
            return next->index;
        }
        else if (next->next != nullptr) {
            return findElement(next->next, value);
        }
        return -1; // If not found!!!
    }

    Node* findElementPtr(Node* prev, Node* next, T value) {
        if (next->value == value) {
            prev->next = next->next;

            Node* temp = next->next;
            delete next;
            while (temp != nullptr) {
                temp->index--;
                temp = temp->next;
            }
            size--;
            return prev;
        }
        else if (next->next != nullptr) {
            return findElementPtr(next, next->next, value);
        }
        return nullptr;
    }

    Node* findIndexElementPtr(Node* prev, Node* next, int value) {
        if (next->index == value) {
            prev->next = next->next;

            Node* temp = next->next;
            delete next;
            while (temp != nullptr) {
                temp->index--;
                temp = temp->next;
            }
            size--;
            return prev;
        }
        else if (next->next != nullptr) {
            return findIndexElementPtr(next, next->next, value);
        }
        return nullptr;
    }

    Node* findElementPtrValue(Node* next, T value) {
        if (next->value == value) {
            return next;
        }
        else if (next->next != nullptr) {
            return findElementPtrValue(next->next, value);
        }
        return nullptr;
    }

public:
    List() {
        this->current = nullptr;
    }

    void append(T value) {
        if (size == 0) {
            this->current = new Node(value, 0);
            size++;
            return;
        }
        Node* newElement = new Node(value, size);
        Node* temp = current;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newElement;
        size++;
    }

    T getByValue(T value) {
        if (current->value == value) {
            return current->index;
        }
        else {
            return findElement(current->next, value);
        }
    }

    Node* remove(T value) {
        if (current->value == value) {
            Node* temp = current;
            current = current->next;
            delete temp;
            Node* temp2 = current;
            while (temp2 != nullptr) {
                temp2->index--;
                temp2 = temp2->next;
            }
            size--;
            return current;
        }
        else {
            return findElementPtr(current, current->next, value);
        }
    }

    Node* removeByIndex(int value) {
        if (current->index == value) {
            Node* temp = current;
            current = current->next;
            delete temp;
            Node* temp2 = current;
            while (temp2 != nullptr) {
                temp2->index--;
                temp2 = temp2->next;
            }
            size--;
            return current;
        }
        else {
            return findIndexElementPtr(current, current->next, value);
        }
    }

    Node* getNext(Node* element) {
        if (element->next != nullptr) {
            return element->next;
        }
        else {
            return element;
        }
    }

    Node* getElement(T value) {
        if (current->value == value) {
            return current;
        }
        else {
            return findElementPtrValue(current->next, value);
        }
    }

    Node* pushBack(T value) {
        Node* newElement = new Node(value, 0);
        Node* temp = current;
        while (temp != nullptr) {
            temp->index++;
            temp = temp->next;
        }
        newElement->next = current;
        current = newElement;
        size++;
        return current;
    }

    void insertByIndex(int index, T value) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (index == 0) {
            pushBack(value);
            return;
        }
        Node* temp = current;
        while (temp->next != nullptr && temp->next->index < index) {
            temp = temp->next;
        }
        Node* newElement = new Node(value, index);
        newElement->next = temp->next;
        temp->next = newElement;

        Node* temp2 = newElement->next;
        while (temp2 != nullptr) {
            temp2->index++;
            temp2 = temp2->next;
        }
        size++;
    }

    void popBack() {
        if (size == 0) return;
        if (size == 1) {
            delete current;
            current = nullptr;
            size--;
            return;
        }
        Node* temp = current;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = current;
        Node* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        current = prev;

        Node* temp = current;
        int idx = 0;
        while (temp != nullptr) {
            temp->index = idx++;
            temp = temp->next;
        }
    }
};

int main() {
    List<int> obj;
    obj.append(12);
    obj.append(14);
    obj.append(125);

    obj.insertByIndex(1, 100);
    obj.popBack();
    obj.reverse();

    auto element = obj.getElement(14);
    if (element) {
        cout << "Found: " << element->value << " at index " << element->index << endl;
    }
    else {
        cout << "Not found" << endl;
    }
}
