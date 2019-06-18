#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef LIGHTSABER_H
#define LIGHTSABER_H

class Lightsaber {
   public:
    Lightsaber() {}
    Lightsaber(float x, float y);
    glm::vec3 position;
    float rotation;
    double speed;
    double direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool done = false;
    VAO *object;
};

#endif  // BALL_H
