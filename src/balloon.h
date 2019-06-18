#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef BALLOON_H
#define BALLOON_H

class Balloon {
   public:
    Balloon() {}
    Balloon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed;
    double timer = 0.0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    bool air = false;
    VAO *object;
};

#endif  // BALL_H
