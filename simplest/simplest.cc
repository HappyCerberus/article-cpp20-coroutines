#include <coroutine>

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() { }
        void unhandled_exception() { }
    };
};

Task myCoroutine() {
    co_return; // make it a coroutine
}

int main() {
    auto c = myCoroutine();
}
