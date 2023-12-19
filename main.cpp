#include "src/App.h"
#include <iostream>
int main() {
    App* app = new App; 
    app->run(); 
    delete app;
    return 0;
}