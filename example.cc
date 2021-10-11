struct ReturnType {
	struct promise_type {
	};
};

ReturnType my_coroutine() {
	co_await something();

	co_yield value;

	co_return; // void
	co_return value;
}
