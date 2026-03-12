#include "my_list.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void WriteInput(const std::string& content) {
    std::ofstream out("test_in.txt");
    out << content;
}

void TestEmptyFile() {
    WriteInput("");

    std::ifstream in("test_in.txt");
    my_list::List list;
    list.FormingListFromFile(in);

    assert(list.GetHeadPtr() == nullptr);
}

void TestSingleNullRand() {
    WriteInput("apple;-1\n");

    std::ifstream in("test_in.txt");
    my_list::List list;
    list.FormingListFromFile(in);

    auto* head = list.GetHeadPtr();
    assert(head != nullptr);
    assert(head->data == "apple");
    assert(head->prev == nullptr);
    assert(head->next == nullptr);
    assert(head->rand == nullptr);
}

void TestSingleSelfRand() {
    WriteInput("apple;0\n");

    std::ifstream in("test_in.txt");
    my_list::List list;
    list.FormingListFromFile(in);

    auto* head = list.GetHeadPtr();
    assert(head != nullptr);
    assert(head->rand == head);
}

void TestTaskExample() {
    WriteInput("apple;2\nbanana;-1\ncarrot;1\n");

    std::ifstream in("test_in.txt");
    my_list::List list;
    list.FormingListFromFile(in);

    auto* first = list.GetHeadPtr();
    assert(first != nullptr);

    auto* second = first->next;
    auto* third = second->next;

    assert(second != nullptr);
    assert(third != nullptr);
    assert(third->next == nullptr);

    assert(first->data == "apple");
    assert(second->data == "banana");
    assert(third->data == "carrot");

    assert(first->prev == nullptr);
    assert(second->prev == first);
    assert(third->prev == second);

    assert(first->rand == third);
    assert(second->rand == nullptr);
    assert(third->rand == second);
}

void TestInvalidInput() {
    WriteInput("apple;abc\n");

    std::ifstream in("test_in.txt");
    my_list::List list;

    bool thrown = false;
    try {
        list.FormingListFromFile(in);
    } catch (const std::invalid_argument&) {
        thrown = true;
    }

    assert(thrown);
}

int main() {
    TestEmptyFile();
    TestSingleNullRand();
    TestSingleSelfRand();
    TestTaskExample();
    TestInvalidInput();

    std::cout << "All tests passed\n";
    return 0;
}