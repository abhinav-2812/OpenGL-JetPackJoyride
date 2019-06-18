#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef SEPCIALCOIN_H
#define SEPCIALCOIN_H

class Specialcoin {
   public:
    Specialcoin() {}
    Specialcoin(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H
