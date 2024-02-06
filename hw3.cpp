#include <iostream>
#include <mutex>
#include <stack>
#include <stdexcept>
#include <initializer_list>

namespace mpcs51044 {
    template <typename T>
    class stack {
    private:
        std::stack<T> st;
        mutable std::mutex mtx;

    public:
        // Default constructor
        stack() = default;

        // Initializer list constructor
        stack(std::initializer_list<T> init) : st(init) {}

        // Push an element onto the stack
        void push(const T& value) {
            std::lock_guard<std::mutex> lock(mtx);
            st.push(value);
        }

        // Pop an element from the stack
        T pop() {
            std::lock_guard<std::mutex> lock(mtx);
            if (st.empty()) {
                throw std::out_of_range("Stack is empty");
            }
            T value = st.top();
            st.pop();
            return value;
        }

        // Check if the stack is empty
        bool empty() const {
            std::lock_guard<std::mutex> lock(mtx);
            return st.empty();
        }
    };
}

int main() {
    // Usage example
    mpcs51044::stack<int> s{3, 1, 4};
    s.push(7);
    s.push(5);
    try {
        while (!s.empty()) {
            std::cout << s.pop() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
