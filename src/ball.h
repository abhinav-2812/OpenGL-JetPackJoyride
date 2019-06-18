#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
#ifndef BALL_H
#define BALL_H

class Ball {
   public:
    Ball() {}
    Ball(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1();
    double speed;
    bool jump = false;
    double jump_time = 0.0;
    double vert_speed = 0.0;
    int health = 100;
    int lives = 3;

   private:
    VAO *object;
};

#endif  // BALL_H
