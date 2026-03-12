#pragma once

#include <fstream>
#include <charconv>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <deque>

namespace my_list {

struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;

    std::string data;
};

class List {
public:
    List() = default;

    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) = delete;
    List& operator=(List&&) = delete;

    ~List() {
        Clear();
    }

    void FormingListFromFile(std::ifstream& input) {
        Clear();
        std::deque<ListNode*> buf_ptr; // pointers for fast accses to element
        std::deque<int> buf_indices; // index to rand elements
        ListNode* tail = nullptr;

        // first cicle - forming the list without rand pointer
        // time - O(N)        
        for (std::string line; std::getline(input, line); ) {
            auto [data, rand_index] = ParseInputLine(line);

            ListNode* node = new ListNode{};
            node->data = std::string(data);

            if (head_ == nullptr) {
                head_ = node;
            } else {
                tail->next = node;
                node->prev = tail;
            }

            tail = node;
            buf_ptr.push_back(node);
            buf_indices.push_back(rand_index);
            ++size_;
        }

        // second cicle - filling a rand pointers in list
        // time - O(N)
        for (size_t i = 0; i < size_; ++i) {
            int rand_index = buf_indices[i];

            if (rand_index == -1) {
                continue;
            }

            if (rand_index < 0 || static_cast<size_t>(rand_index) >= size_) {
                throw std::invalid_argument("rand index is out of range");
            }

            buf_ptr[i]->rand = buf_ptr[rand_index];
        }
    }

    void FormingOutFile(std::ofstream& out) {
        std::unordered_map<ListNode*, std::uint32_t> position_by_ptr;

        std::uint32_t index = 0;
        for (ListNode* ptr = head_; ptr != nullptr; ptr = ptr->next) {
            position_by_ptr[ptr] = index++;
        }

        const std::uint32_t node_count = index;
        out.write(reinterpret_cast<const char*>(&node_count), sizeof(node_count));

        for (ListNode* ptr = head_; ptr != nullptr; ptr = ptr->next) {
            const std::uint32_t data_size =
                static_cast<std::uint32_t>(ptr->data.size());

            out.write(reinterpret_cast<const char*>(&data_size), sizeof(data_size));
            out.write(ptr->data.data(), static_cast<std::streamsize>(data_size));

            std::int32_t rand_index = -1;
            if (ptr->rand != nullptr) {
                rand_index = static_cast<std::int32_t>(position_by_ptr.at(ptr->rand));
            }

            out.write(reinterpret_cast<const char*>(&rand_index), sizeof(rand_index));
        }
    }

    ListNode* GetHeadPtr() const {
        return head_;
    }

private:
    std::pair<std::string_view, int> ParseInputLine(std::string_view line) {
        size_t pos = line.find_last_of(';');
        if (pos == std::string::npos) {
            throw std::invalid_argument("The line is not content a ';'!");
        }

        if (pos + 1 == line.size()) {
            throw std::invalid_argument("Index is empty!");
        }

        std::string_view data = line.substr(0, pos);

        int index = -1;
        auto [ptr, ec] = std::from_chars((line.data() + pos + 1), line.data() + line.size(), index);
        if (ec == std::errc{} && ptr == line.data() + line.size()) {
            return {data, index};
        }
        else {
            throw std::invalid_argument("Incorrect line, parsing failed!");
        }
    }

    void Clear() {
        ListNode* cur = head_;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            delete cur;
            cur = next;
        }

        head_ = nullptr;
        size_ = 0;
    }

private:
    ListNode* head_ = nullptr;
    size_t size_ = 0;
};

} // namespace my_list