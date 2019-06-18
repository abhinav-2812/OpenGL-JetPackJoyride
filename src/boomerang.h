#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef BOOMERANG_H
#define BOOMERANG_H

class Boomerang {
   public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed;
    double temp;
    double direction;
    double cx;
    double cy;
    double ang = 0.0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H
