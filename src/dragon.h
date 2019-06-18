#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
   public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    double speed;
    double direction = -1.0;
    double timer = 0.0;
    int off = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1();
    bool done = false;
    bool alive = true;
    int health = 200;
    VAO *object;
};

#endif  // BALL_H
