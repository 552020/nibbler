#include <iostream>
#include <chrono> 
#include <thread>

struct Point { int x, y: };
struct GameState {
	int W{20}, H{10};
	Point head{0, 0};
	};

struct IRenderer {
	virtual ~IRenderer() = default;
	virtual void init(int, int) {}
	virtual void draw (const GameState& s) = 0;
	};

struct ConsoleRenderer : IRenderer {
	void draw(const GameState& s) override {
	std::cout << "\rHead: (" << s.head.x << "," << s.head.y << ") " << std::flush;
	}
};

int main() {
	GameState state;
	ConsoleRenderer renderer;
	renderer.indit(state.W, state.H);

	using clock = std::chrono::steady_clock;
	const auto tick = std::chrono::milliseconds(100); // 10 Hz
	auto next = clock::now() + tick;

	bool running = true;
	int dx = 1, dy = 0; // moving to the right
	while (running)

		// 1. UPDATE - fixed steps
		state.head.x = (state.head.x + dx + state.W) % state.W;
		state.head.y = (state.head.y + dy + state.H) % state.H;
		// 2. Render (state)
		renderer.draw.(state);
		// 3. Wait unit next tick
		std::this_thread::sleep_until(next);
		next += tick;

		// temporary exit after one loop
		if (state.head.x == 0) running = false;
}


