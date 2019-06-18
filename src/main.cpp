#include "main.h"
#include "ball.h"
#include "balloon.h"
#include "bits/stdc++.h"
#include "boomerang.h"
#include "coin.h"
#include "dragon.h"
#include "dragonfire.h"
#include "firebeam.h"
#include "fireline.h"
#include "floor.h"
#include "health.h"
#include "lightsaber.h"
#include "lives.h"
#include "magnet.h"
#include "ring.h"
#include "score.h"
#include "special.h"
#include "specialcoin.h"
#include "timer.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
 * Customizable functions *
 **************************/

#define PI 3.14159265

Ball ball1;
Floor floor1;
Coin coins[1005];
Fireline firelines[105];
Firebeam firebeam[15];
Lightsaber lightsaber;
Boomerang boomerang[15];
Magnet magnets[105];
Special special[105];
Specialcoin specialcoins[105];
int cflag[1005];
int scflag[105];
int sflag[105];
Dragon dragon;
static GLfloat a[100000];
float cx;
double tim = 0.0;
int bflag;
int booflag[15];
Ring ring;
int rflag;
int score;
double ang = 180.0;
Score scores[4];
Lives lives[2];
Health health[3];
vector<Balloon> balloons;
vector<Dragonfire> dragonfire;
int bidx;
int didx;
double dtime = 0.0;

float screen_zoom = 0.6, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(cx, 0, 10);
    glm::vec3 target(cx, 0, 0);
    // glm::vec3 eye;
    // glm::vec3 eye(5 * cos(camera_rotation_angle * M_PI / 180.0f), 0,
    //   5 * sin(camera_rotation_angle * M_PI / 180.0f));
    // Target - Where is the camera looking at.  Don't change unless you are
    // sure!!
    // glm::vec3 target;
    // if (screen_zoom >= 1) {
    //     target = glm::vec3(cx, ball1.position.y, 0);
    //     // eye = glm::vec3(cx, ball1.position.y, 0);
    //     //     // glm::vec3 target(cx, ball1.position.y, 0);
    // } else {
    //     // eye = glm::vec3(cx, 0, 0);
    // }

    // Up - Up vector defines tilt of camera.  Don't change unless you are
    // sure!!
    glm::vec3 up(0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up);  // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(
    //     glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
    //     glm::vec3(0, 1, 0));  // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this
    // frame (basic scenario) Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP"
    // uniform For each model you render, since the MVP will be different (at
    // least the M part) Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    floor1.draw(VP);
    if (dragon.alive) dragon.draw(VP);
    ring.draw(VP);
    if (score >= 200) lightsaber.draw(VP);
    int temp = score;
    int arr[4];
    for (int i = 1; i <= 4; i++) {
        int d = temp % 10;
        temp /= 10;
        arr[4 - i] = d;
    }
    int ar[3];
    int temp1 = ball1.health;
    for (int i = 1; i <= 3; i++) {
        int d = temp1 % 10;
        temp1 /= 10;
        ar[3 - i] = d;
    }
    for (int i = 0; i < 3; i++) {
        health[i].draw(VP, ar[i]);
    }
    lives[0].draw(VP, 0);
    lives[1].draw(VP, ball1.lives);

    for (int i = 0; i < 4; i++) {
        scores[i].draw(VP, arr[i]);
    }
    for (int i = 0; i < 1005; i++) {
        if (balloons[i].done) {
            balloons[i].draw(VP);
            // balloons[i].done = false;
        }
    }
    for (int i = 0; i < 1005; i++) {
        if (dragonfire[i].done && dragon.alive) {
            dragonfire[i].draw(VP);
        }
    }
    for (int i = 0; i < 105; i++) {
        magnets[i].draw(VP);
    }
    // if (bflag && !firebeam.off) firebeam.draw(VP);
    for (int i = 0; i < 15; i++) {
        if (!booflag[i]) boomerang[i].draw(VP);
    }
    for (int i = 0; i < 1005; i++) {
        if (!cflag[i]) coins[i].draw(VP);
    }
    for (int i = 0; i < 105; i++) {
        if (!scflag[i]) specialcoins[i].draw(VP);
    }
    for (int i = 0; i < 105; i++) {
        if (!firelines[i].done) firelines[i].draw(VP);
    }
    for (int i = 0; i < 105; i++) {
        if (!sflag[i]) special[i].draw(VP);
    }
    for (int i = 0; i < 15; i++) {
        if (!firebeam[i].done) firebeam[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int b = glfwGetKey(window, GLFW_KEY_B);

    if (left) {
        ball1.position.x -= ball1.speed;
    }

    if (right) {
        ball1.position.x += ball1.speed;
    }

    if (space) {
        ball1.jump = true;
        ball1.jump_time = 0.0f;
        ball1.vert_speed = 1.0f;
    }

    if (b) {
        balloons[bidx].done = true;
        balloons[bidx].air = true;
        bidx++;
        if (bidx == balloons.size()) bidx = 0;
    }

    reset_screen();
}

void tick_elements() {
    // ball1.tick();
    double r = dragon.position.x - ball1.position.x;
    if (dragon.alive) {
        if (r > 4.0f) {
            dragon.tick();
        } else
            dragon.tick1();
    }
    if (score >= 200) lightsaber.tick();
    for (int i = 0; i < 1005; i++) {
        if (balloons[i].air) {
            balloons[i].tick();
        }
    }
    for (int i = 0; i < 1005; i++) {
        if (dragonfire[i].air && dragon.alive) {
            dragonfire[i].tick();
        }
    }
    for (int i = 0; i < 15; i++) {
        if (!booflag[i]) boomerang[i].tick();
    }
    // if (bflag && !firebeam.off) firebeam.tick();
    for (int i = 0; i < 1005; i++) {
        if (!cflag[i]) coins[i].tick();
    }
    for (int i = 0; i < 105; i++) {
        if (!scflag[i]) specialcoins[i].tick();
    }
    for (int i = 0; i < 105; i++) {
        if (!firelines[i].done) firelines[i].tick();
    }
    for (int i = 0; i < 105; i++) {
        if (!sflag[i]) special[i].tick();
    }
    for (int i = 0; i < 15; i++) {
        if (!firebeam[i].done) firebeam[i].tick();
    }
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0.0f, -2.7f);
    floor1 = Floor(0.0f, -1.7f, COLOR_GREEN);
    dragon = Dragon(700.0f, 3.0f);
    ring = Ring(rand() % 300 + 10.0, 1.0f, COLOR_DARKGREEN);
    lightsaber = Lightsaber(0.3, -3.1);
    double pos = screen_center_x;
    for (int i = 0; i < 4; i++) {
        scores[i] = Score(pos - 6.0, 6.0f, COLOR_BLACK);
        pos += 0.3f;
    }
    pos = screen_center_x;
    for (int i = 0; i < 2; i++) {
        lives[i] = Lives(pos + 6.0, 6.0f, COLOR_BLACK);
        pos += 0.3f;
    }
    pos = screen_center_x;
    for (int i = 0; i < 3; i++) {
        health[i] = Health(pos, 6.0, COLOR_BLACK);
        pos += 3.0;
    }
    pos = 0.0f;
    firebeam[0] = Firebeam(10.0, 2.0f);
    for (int i = 1; i < 15; i++) {
        double xx = rand() % 1000 + 1;
        xx += 5.0f;
        firebeam[i] = Firebeam(xx, 2.0f);
    }
    for (int i = 0; i < 15; i++) {
        double xx = rand() % 1000 + 1;
        xx += 5.0f;
        boomerang[i] = Boomerang(xx, 2.0f, COLOR_BLACK);
        boomerang[i].cx = xx;
        boomerang[i].cy = 2.0f;
    }
    for (int i = 0; i < 105; i++) {
        double xx = rand() % 2000 + 1;
        xx += 10.0;
        special[i] = Special(xx, 1.0f, COLOR_DARKGREEN);
    }
    for (int i = 0; i < 105; i++) {
        double xx = rand() % 2500 + 1;
        xx += 10.0;
        magnets[i] = Magnet(xx, 3.0f);
    }
    for (int i = 0; i < 1005; i++) {
        double xx = rand() % 2000 + 1;
        xx += 5.0f;
        double yy = 2.0f;
        coins[i] = Coin(xx, yy, COLOR_GOLDEN);
    }
    for (int i = 0; i < 105; i++) {
        double xx = rand() % 2000 + 1;
        xx += 5.0f;
        double yy = 3.0f;
        specialcoins[i] = Specialcoin(xx, yy, COLOR_ORANGE);
    }
    for (int i = 0; i < 105; i++) {
        double xx = rand() % 2000 + 1;
        xx += 10.0;
        firelines[i] = Fireline(xx, 4.0f);
    }
    for (int i = 0; i < 1005; i++) {
        balloons.push_back(
            Balloon(ball1.position.x, ball1.position.y, COLOR_DARKRED));
    }
    for (int i = 0; i < 1005; i++) {
        dragonfire.push_back(
            Dragonfire(dragon.position.x, dragon.position.y, COLOR_FLAME));
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0,
                 COLOR_BACKGROUND.b / 256.0, 0.0f);  // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width = 1600;
    int height = 900;
    cx = 0.0f;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */

    while (!glfwWindowShouldClose(window)) {
        if (ball1.lives == 0) quit(window);
        // if (tim - 10.0 > -0.00005) bflag = 1;
        // Process timers
        bounding_box_t b_player, b_coins[1005], b_boomerang[15],
            b_firebeam[105], b_ring, b_balloons[1005], b_dragonfire[1005],
            b_lightsaber, b_dragon, b_special[105], b_fireline[105],
            b_specialcoin[105];
        b_player.x = ball1.position.x;
        b_player.y = ball1.position.y;
        b_ring.x = ring.position.x - 3.0;
        b_ring.y = ring.position.y;
        b_lightsaber.x = lightsaber.position.x;
        b_lightsaber.y = lightsaber.position.y;
        b_dragon.x = dragon.position.x;
        b_dragon.y = dragon.position.y - 0.1;
        for (int i = 0; i < 15; i++) {
            b_boomerang[i].x = boomerang[i].position.x;
            b_boomerang[i].y = boomerang[i].position.y;
            b_boomerang[i].width = b_boomerang[i].height = 0.5;
        }
        for (int i = 0; i < 1005; i++) {
            b_balloons[i].x = balloons[i].position.x;
            b_balloons[i].y = balloons[i].position.y;
            b_balloons[i].width = b_balloons[i].height = 0.5;
        }
        for (int i = 0; i < 1005; i++) {
            b_dragonfire[i].x = dragonfire[i].position.x;
            b_dragonfire[i].y = dragonfire[i].position.y;
            b_dragonfire[i].width = b_dragonfire[i].height = 0.5;
        }
        for (int i = 0; i < 1005; i++) {
            b_coins[i].x = coins[i].position.x;
            b_coins[i].y = coins[i].position.y;
            b_coins[i].width = b_coins[i].height = 0.5;
        }
        for (int i = 0; i < 105; i++) {
            b_specialcoin[i].x = specialcoins[i].position.x;
            b_specialcoin[i].y = specialcoins[i].position.y;
            b_specialcoin[i].width = b_specialcoin[i].height = 0.5;
        }
        for (int i = 0; i < 105; i++) {
            b_special[i].x = special[i].position.x;
            b_special[i].y = special[i].position.y;
            b_special[i].width = b_special[i].height = 0.5;
        }

        for (int i = 0; i < 15; i++) {
            b_firebeam[i].x = firebeam[i].position.x;
            b_firebeam[i].y = firebeam[i].position.y;
            b_firebeam[i].width = 8.2;
            b_firebeam[i].height = 0.5;
        }
        for (int i = 0; i < 105; i++) {
            double dist = abs(ball1.position.x - firelines[i].position.x -
                              ball1.position.y + firelines[i].position.y);
            dist /= sqrt(2.0);
            if (!firelines[i].done && dist < 0.4 && !rflag &&
                ball1.position.x >= firelines[i].position.x - 0.2 &&
                ball1.position.x <= firelines[i].position.x + 1.7) {
                firelines[i].done = true;
                ball1.health -= 15;
                if (ball1.health == 0) {
                    ball1.lives--;
                    ball1.health = 100;
                }
            }
        }
        b_player.width = b_player.height = 0.3;
        b_ring.width = b_ring.height = 0.5;
        b_lightsaber.width = b_lightsaber.height = 0.5;
        b_dragon.width = 0.5;
        b_dragon.height = 2.0;
        for (int i = 0; i < 1005; i++) {
            for (int j = 0; j < 105; j++) {
                double dist =
                    abs(balloons[i].position.x - firelines[j].position.x -
                        balloons[i].position.y + firelines[j].position.y);
                dist /= sqrt(2.0);
                if (!firelines[j].done && balloons[i].done && dist < 0.4 &&
                    balloons[i].position.x >= firelines[j].position.x - 0.2 &&
                    balloons[i].position.x <= firelines[j].position.x + 1.7) {
                    balloons[i].done = true;
                    balloons[i].air = true;
                    firelines[j].done = true;
                }
            }
        }
        for (int i = 0; i < 1005; i++) {
            if (balloons[i].done && detect_collision(b_balloons[i], b_dragon)) {
                balloons[i].air = false;
                balloons[i].done = false;
                dragon.health -= 10;
                if (dragon.health == 0) {
                    dragon.alive = false;
                }
            }
        }
        for (int i = 0; i < 1005; i++) {
            if (dragonfire[i].done && !rflag &&
                detect_collision(b_dragonfire[i], b_player)) {
                dragonfire[i].done = false;
                dragonfire[i].air = false;
                ball1.health -= 20;
                if (ball1.health <= 0) {
                    ball1.lives--;
                    ball1.health = 100;
                }
            }
        }

        for (int i = 0; i < 1005; i++) {
            for (int j = 0; j < 105; j++) {
                if (balloons[i].done && !firebeam[j].done &&
                    detect_collision(b_balloons[i], b_firebeam[j])) {
                    balloons[i].air = false;
                    balloons[i].done = false;
                    firebeam[j].done = true;
                }
            }
        }

        for (int i = 0; i < 15; i++) {
            if (!firebeam[i].done &&
                detect_collision(b_lightsaber, b_firebeam[i])) {
                firebeam[i].done = true;
            }
        }
        for (int i = 0; i < 105; i++) {
            if (!booflag[i] && detect_collision(b_lightsaber, b_boomerang[i])) {
                booflag[i] = 1;
            }
        }

        if (score >= 300 && detect_collision(b_lightsaber, b_dragon)) {
            dragon.alive = false;
        }

        if (detect_collision(b_player, b_ring)) {
            rflag = 1;
        }
        for (int i = 0; i < 105; i++) {
            if (!sflag[i] && detect_collision(b_player, b_special[i])) {
                sflag[i] = 1;
                score += 20;
            }
        }
        for (int i = 0; i < 1005; i++) {
            if (!cflag[i] && detect_collision(b_player, b_coins[i])) {
                cflag[i] = 1;
                score++;
            }
        }
        for (int i = 0; i < 105; i++) {
            if (!scflag[i] && detect_collision(b_player, b_specialcoin[i])) {
                scflag[i] = 1;
                score += 5;
            }
        }
        for (int i = 0; i < 15; i++) {
            if (!rflag && !booflag[i] &&
                detect_collision(b_player, b_boomerang[i])) {
                booflag[i] = 1;
                ball1.health -= 10;
                if (ball1.health == 0) {
                    ball1.lives--;
                    ball1.health = 100;
                }
            }
        }
        for (int i = 0; i < 15; i++) {
            if (!rflag && (!firebeam[i].done) &&
                detect_collision(b_player, b_firebeam[i])) {
                firebeam[i].done = true;
                ball1.health -= 15;
                if (ball1.health == 0) {
                    ball1.lives--;
                    ball1.health = 100;
                }
            }
        }
        for (int i = 0; i < 105; i++) {
            double r = sqrt((magnets[i].position.x - ball1.position.x) *
                                (magnets[i].position.x - ball1.position.x) +
                            (magnets[i].position.y - ball1.position.y) *
                                (magnets[i].position.y - ball1.position.y));
            double F = 0.0;
            double Fx, Fy;
            if (r >= 0.4) {
                F = 0.1 / (r);
            }
            Fx = F * (magnets[i].position.x - ball1.position.x) / (r);
            Fy = F * (magnets[i].position.y - ball1.position.y) / (r);
            if (r < 6.0) {
                ball1.position.x += Fx;
                ball1.position.y += Fy;
            }
        }

        if (t60.processTick()) {
            if (rflag && ang > 0.0) {
                ball1.jump = false;
                ball1.position.x =
                    ring.position.x + 3.0 * cos(ang * PI / 180.0);
                ball1.position.y =
                    ring.position.y + 3.0 * sin(ang * PI / 180.0);
                ang -= 0.5;
                if (ang <= 0.0) {
                    rflag = 0;
                    ang = 180.0;
                }
            } else {
                tim += 1.0 / 60.0;
                if (ball1.jump) {
                    ball1.jump_time += 1.0 / 60.0;
                    if ((ball1.position.y + ball1.vert_speed * ball1.jump_time -
                         0.5 * 2.0 * ball1.jump_time * ball1.jump_time) >=
                            -2.7f &&
                        (ball1.position.y + ball1.vert_speed * ball1.jump_time -
                         0.5 * 2.0 * ball1.jump_time * ball1.jump_time) <=
                            7.5f) {
                        ball1.position.y +=
                            ball1.vert_speed * ball1.jump_time -
                            0.5 * 2.0 * ball1.jump_time * ball1.jump_time;
                    } else if (ball1.position.y +
                                   ball1.vert_speed * ball1.jump_time -
                                   0.5 * 2.0 * ball1.jump_time *
                                       ball1.jump_time >
                               7.5f) {
                        ball1.position.y = 7.5f;
                    } else {
                        ball1.jump = false;
                        ball1.jump_time = 0.0;
                        ball1.position.y = -2.7f;
                    }
                } else if (!ball1.jump && ball1.position.y > -2.7f) {
                    ball1.jump_time += 1.0 / 60.0;
                    if (ball1.position.y -
                            0.5 * 2.0 * ball1.jump_time * ball1.jump_time >=
                        -2.7f) {
                        ball1.position.y -=
                            0.5 * 2.0 * ball1.jump_time * ball1.jump_time;
                    } else {
                        ball1.jump_time = 0.0;
                        ball1.position.y = -2.7f;
                    }
                }
            }
            // else {
            //     if(!ball1.jump && ball1.position.y!=2.7f) {

            //     }
            // }

            double pos = 0.0;
            for (int i = 0; i < 4; i++) {
                scores[i].position.x = ball1.position.x + pos - 6.0;
                pos += 0.3;
            }
            pos = 0.0;
            for (int i = 0; i < 2; i++) {
                lives[i].position.x = ball1.position.x + pos + 6.0;
                pos += 0.3;
            }
            pos = 0.0;
            for (int i = 0; i < 3; i++) {
                health[i].position.x = ball1.position.x + pos;
                pos += 0.3;
            }
            for (int i = 0; i < 1005; i++) {
                if (!balloons[i].air) {
                    balloons[i].position.x = ball1.position.x;
                    balloons[i].position.y = ball1.position.y;
                }
            }
            if (tim - dtime > -0.00005) {
                dragonfire[didx].air = true;
                dragonfire[didx].done = true;
                dtime += 0.4;
                didx++;
                if (didx == dragonfire.size()) didx = 0;
            }
            for (int i = 0; i < 1005; i++) {
                if (!dragonfire[i].air) {
                    dragonfire[i].position.x = dragon.position.x - 0.2;
                    dragonfire[i].position.y = dragon.position.y + 0.3;
                }
            }
            lightsaber.position.x = ball1.position.x + 0.3;
            lightsaber.position.y = ball1.position.y - 0.4;
            cx = ball1.position.x;
            // 60 fps
            tick_elements();
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float yy = 1.0;
    if (screen_zoom > 0.7) {
        yy = ball1.position.y;
    }
    float top = yy + 4 / screen_zoom;
    float bottom = yy - 4 / screen_zoom;
    float left = -4 / screen_zoom;
    float right = 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
