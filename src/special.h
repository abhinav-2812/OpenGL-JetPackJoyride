#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef SPECIAL_H
#define SPECIAL_H

class Special {
   public:
    Special() {}
    Special(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed;
    double direction = -1.0;
    double timer = 0.0;
    int off = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H
