#define STB_IMAGE_IMPLEMENTATION
#include<windows.h>
#include "stb_image.h"
#include <GL/glut.h>
#include <GL/glext.h> // Include GL/glext.h for GL_CLAMP_TO_EDGE

// Image data
int imageWidth, imageHeight, imageChannels;
unsigned char* imageData;

// Texture ID
GLuint textureID;

void loadImage(const char* fileName) {
    // Load image file
    imageData = stbi_load(fileName, &imageWidth, &imageHeight, &imageChannels, 0);
}

void init() {
    // Load image
    loadImage("SpaceBack.png");

    // Enable texture
    glEnable(GL_TEXTURE_2D);

    // Generate texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Use GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Use GL_CLAMP_TO_EDGE

    // Load image data into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    // Free image data
    stbi_image_free(imageData);
}

void display() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Draw textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Swap buffers
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("OpenGL Background");

    // Initialize OpenGL
    init();

    // Set display callback
    glutDisplayFunc(display);

    // Enter main loop
    glutMainLoop();

    return 0;
}
