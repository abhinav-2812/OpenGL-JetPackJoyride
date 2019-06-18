#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef FIREBEAM_H
#define FIREBEAM_H

class Firebeam {
   public:
    Firebeam() {}
    Firebeam(float x, float y);
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
