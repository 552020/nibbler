#include "Game.hpp"

int main() {
    // Program entry point.
    Game game; // Creating our game object.
    
    while (game.GetWindow()->IsOpen()) {
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
    }
}

