#include <coroutine>
#include <iostream>

auto dbg = [](const char* s) {
        std::cerr << "Function " << s << " called.\n";
};

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;
        promise_type() {
            dbg(__PRETTY_FUNCTION__);
        }
        ~promise_type() {
            dbg(__PRETTY_FUNCTION__);
        }
        Task get_return_object() {
            dbg(__PRETTY_FUNCTION__);
            return Task{Handle::from_promise(*this)};
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
    explicit Task(promise_type::Handle coro) : coro_(coro) {
        dbg(__PRETTY_FUNCTION__);
    }
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& t) noexcept : coro_(t.coro_) {
        dbg(__PRETTY_FUNCTION__);
        t.coro_ = {};
    }
    Task& operator=(Task&& t) noexcept {
        dbg(__PRETTY_FUNCTION__);
        if (this == &t) return *this;
        if (coro_) coro_.destroy();
        coro_ = t.coro_;
        t.coro_ = {};
        return *this;
    }
    ~Task() {
        dbg(__PRETTY_FUNCTION__);
        if (coro_ && !coro_.done())
            coro_.destroy();
    }

    void destroy() { coro_.destroy(); }
    void resume() { coro_.resume(); }
private:
    promise_type::Handle coro_;
};

Task myCoroutine() {
    std::cerr << "Inside coroutine.\n";
    co_return; // make it a coroutine
}

int main() {
    std::cerr << "Before coroutine call.\n";
    auto c = myCoroutine();
    std::cerr << "After call, before resume.\n";
    c.resume();
    std::cerr << "After resume.\n";
}
