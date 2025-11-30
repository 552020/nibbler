#include "Game.hpp"

int main() {
    // Program entry point.
    Game game; // Creating our game object.
    
    // CRITICAL: Use IsOpen() NOT IsDone() - IsDone() causes segfault because
    // when window closes, IsDone() is set to true but loop still calls Render() on closed window.
    // IsOpen() exits loop immediately when window closes, preventing render on closed window.
    while (game.GetWindow()->IsOpen()) {
        // Game loop.
        // COMMENTED OUT: HandleInput - input is now handled by states via EventManager
        // game.HandleInput();
        game.Update();
        game.Render();
        game.LateUpdate(); // Process state removal requests and restart clock
    }
    return 0;
}

