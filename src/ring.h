#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef RING_H
#define RING_H

class Ring {
   public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H
