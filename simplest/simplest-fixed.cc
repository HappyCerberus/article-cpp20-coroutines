#include <coroutine>

// The caller-level type
struct Task {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;

        Task get_return_object() {
            return Task{Handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() { }
        void unhandled_exception() { }
    };

    explicit Task(promise_type::Handle coro) : coro_(coro) {}
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& t) noexcept : coro_(t.coro_) { t.coro_ = {}; }
    Task& operator=(Task&& t) noexcept {
        if (this == &t) return *this;
        if (coro_) coro_.destroy();
        coro_ = t.coro_;
        t.coro_ = {};
        return *this;
    }
    ~Task() {
        if (coro_ && !coro_.done())
            coro_.destroy();
    }

    void destroy() { coro_.destroy(); }
    void resume() { coro_.resume(); }

private:
    promise_type::Handle coro_;
};

Task myCoroutine() {
    co_return; // make it a coroutine
}

int main() {
    auto c = myCoroutine();
    c.resume();
    // c.destroy();
}
