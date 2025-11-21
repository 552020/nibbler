#include <SFML/System.hpp>
#include <iostream>

int main()
{
    std::cout << "Testing non-OpenGL SFML modules..." << std::endl;
    
    try {
        std::cout << "Creating Clock..." << std::endl;
        sf::Clock clock;
        std::cout << "Clock created successfully" << std::endl;
        
        std::cout << "Getting elapsed time..." << std::endl;
        sf::Time elapsed = clock.getElapsedTime();
        std::cout << "Elapsed time: " << elapsed.asSeconds() << " seconds" << std::endl;
        
        std::cout << "Restarting clock..." << std::endl;
        elapsed = clock.restart();
        std::cout << "Clock restarted. Previous elapsed: " << elapsed.asSeconds() << " seconds" << std::endl;
        
        std::cout << "Sleeping for 100ms..." << std::endl;
        sf::sleep(sf::milliseconds(100));
        
        elapsed = clock.getElapsedTime();
        std::cout << "After sleep, elapsed: " << elapsed.asMilliseconds() << " ms" << std::endl;
        
        std::cout << "✅ All non-OpenGL SFML tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }
}

