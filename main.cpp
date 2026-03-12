#include <iostream>
#include <fstream>

#include "my_list.h"

int main() {
    std::ifstream input("../inlet.in");
    if (!input.is_open()) {
        throw std::invalid_argument("input file not found!");
    }

    my_list::List list;
    my_list::ListNode* head = list.GetHeadPtr();

    list.FormingListFromFile(input);

    std::ofstream output("../outlet.out", std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("output file is not opened!");
    }

    list.FormingOutFile(output);

    auto l_ptr = head;
    while (true) {
        if (l_ptr == nullptr) {
            break;
        }


        std::cout << l_ptr->data << "    " << l_ptr->rand << std::endl;
        l_ptr = l_ptr->next;
    }

    return 0;
}