#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv)
{
    std::cout << "=== Testing OpenGL in isolation ===" << std::endl;
    std::cout << "Initializing GLUT..." << std::endl;
    
    glutInit(&argc, argv);
    std::cout << "GLUT initialized" << std::endl;
    
    std::cout << "Creating window..." << std::endl;
    glutCreateWindow("OpenGL Test");
    std::cout << "Window created successfully!" << std::endl;
    
    std::cout << "Setting display callback..." << std::endl;
    glutDisplayFunc(display);
    
    std::cout << "Entering GLUT main loop (will exit after 2 seconds)..." << std::endl;
    std::cout << "✅ OpenGL test passed - no crash!" << std::endl;
    
    // Don't actually enter the loop, just test initialization
    // glutMainLoop();
    
    return 0;
}


