#include "src/App.h"
#include <iostream>
int main() {
    App app; // Create the App object on the stack
    app.run(); // Start the game loop
    return 0;
}