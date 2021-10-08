#include <coroutine>
#include <iostream>

auto dbg = [](const char* s) {
        std::cerr << "Function " << s << " called.\n";
};

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        promise_type() {
            dbg(__PRETTY_FUNCTION__);
        }
        ~promise_type() {
            dbg(__PRETTY_FUNCTION__);
        }
        Task get_return_object() {
            dbg(__PRETTY_FUNCTION__);
            return {};
        }
        std::suspend_always initial_suspend() {
            dbg(__PRETTY_FUNCTION__);
            return {};
        }
        std::suspend_never final_suspend() noexcept {
            dbg(__PRETTY_FUNCTION__);
            return {};
        }
        void return_void() {
            dbg(__PRETTY_FUNCTION__);
        }
        void unhandled_exception() {
            dbg(__PRETTY_FUNCTION__);
        }
    };
    Task() {
        dbg(__PRETTY_FUNCTION__);
    }
    ~Task() {
        dbg(__PRETTY_FUNCTION__);
    }
};

Task myCoroutine() {
    std::cerr << "Inside coroutine.\n";
    co_return; // make it a coroutine
}

int main() {
    std::cerr << "Before coroutine call.\n";
    auto c = myCoroutine();
    std::cerr << "After coroutine call.\n";
}
