#include <coroutine>
#include <iostream>
#include <chrono>
#include <thread>

struct Sleeper {
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> h) const {
        auto t = std::jthread([h,l = length] {
            std::this_thread::sleep_for(l);
            h.resume();
        });
    }
    constexpr void await_resume() const noexcept {}
    const std::chrono::duration<int, std::milli> length;
};

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
    using namespace std::chrono_literals;
    auto before = std::chrono::steady_clock::now();
    std::cout << "Going to sleep on thread " <<
	    std::this_thread::get_id() << "\n";
    co_await Sleeper{200ms};
    auto after = std::chrono::steady_clock::now();
    std::cout << "Slept for " << (after-before) / 1ms << " ms\n";
    std::cout << "Now on thread " << std::this_thread::get_id() << "\n";
}

int main() {
    myCoroutine();
}
