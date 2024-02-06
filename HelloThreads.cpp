#include <iostream>
#include <thread>  // std::jthread is also defined in the <thread> header

void hello_threads() {
    std::cout << "Hello Concurrent World\n";
}

int main() {
    // Print in a different thread
    std::jthread t(hello_threads);
    // No need to call t.join() as std::jthread automatically joins upon destruction
}

