#include "ball.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Ball::Ball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices

    int n = 10;
    double ang = 360.0 / (double)(n);
    static GLfloat vertex_buffer_data[120000];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = 0.0f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.1f;
    vertex_buffer_data[4] = 0.0f;
    vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6] = 0.1f * cos(ang * PI / 180.0);
    vertex_buffer_data[7] = 0.1f * sin(ang * PI / 180.0);
    vertex_buffer_data[8] = 0.0f;
    for (int i = 9; i < 9 * n; i += 9) {
        double prevx = vertex_buffer_data[i - 3];
        double prevy = vertex_buffer_data[i - 2];
        vertex_buffer_data[i] = prevx;
        vertex_buffer_data[i + 1] = prevy;
        vertex_buffer_data[i + 2] = 0.0f;
        vertex_buffer_data[i + 3] = 0.0f;
        vertex_buffer_data[i + 4] = 0.0f;
        vertex_buffer_data[i + 5] = 0.0f;
        vertex_buffer_data[i + 6] =
            prevx * cos(ang * PI / 180.0) - prevy * sin(ang * PI / 180.0);
        vertex_buffer_data[i + 7] =
            prevx * sin(ang * PI / 180.0) + prevy * cos(ang * PI / 180.0);
        vertex_buffer_data[i + 8] = 0.0f;
    }
    vertex_buffer_data[9 * n] = -0.2f;
    vertex_buffer_data[9 * n + 1] = -0.15f;
    vertex_buffer_data[9 * n + 2] = 0.0f;
    vertex_buffer_data[9 * n + 3] = -0.2f;
    vertex_buffer_data[9 * n + 4] = -0.75f;
    vertex_buffer_data[9 * n + 5] = 0.0f;
    vertex_buffer_data[9 * n + 6] = 0.2f;
    vertex_buffer_data[9 * n + 7] = -0.75f;
    vertex_buffer_data[9 * n + 8] = 0.0f;
    vertex_buffer_data[9 * n + 45] = 0.2f;
    vertex_buffer_data[9 * n + 46] = -0.75f;
    vertex_buffer_data[9 * n + 47] = 0.0f;
    vertex_buffer_data[9 * n + 48] = 0.2f;
    vertex_buffer_data[9 * n + 49] = -0.15f;
    vertex_buffer_data[9 * n + 50] = 0.0f;
    vertex_buffer_data[9 * n + 51] = -0.2f;
    vertex_buffer_data[9 * n + 52] = -0.15f;
    vertex_buffer_data[9 * n + 53] = 0.0f;

    vertex_buffer_data[9 * n + 54] = -0.42f;
    vertex_buffer_data[9 * n + 55] = -0.25f;
    vertex_buffer_data[9 * n + 56] = 0.0f;
    vertex_buffer_data[9 * n + 57] = -0.42f;
    vertex_buffer_data[9 * n + 58] = -0.65f;
    vertex_buffer_data[9 * n + 59] = 0.0f;
    vertex_buffer_data[9 * n + 60] = -0.22f;
    vertex_buffer_data[9 * n + 61] = -0.65f;
    vertex_buffer_data[9 * n + 62] = 0.0f;
    vertex_buffer_data[9 * n + 63] = -0.22f;
    vertex_buffer_data[9 * n + 64] = -0.65f;
    vertex_buffer_data[9 * n + 65] = 0.0f;
    vertex_buffer_data[9 * n + 66] = -0.22f;
    vertex_buffer_data[9 * n + 67] = -0.25f;
    vertex_buffer_data[9 * n + 68] = 0.0f;
    vertex_buffer_data[9 * n + 69] = -0.42f;
    vertex_buffer_data[9 * n + 70] = -0.25f;
    vertex_buffer_data[9 * n + 71] = 0.0f;

    vertex_buffer_data[9 * n + 72] = -0.35f;
    vertex_buffer_data[9 * n + 73] = -0.23f;
    vertex_buffer_data[9 * n + 74] = 0.0f;
    vertex_buffer_data[9 * n + 75] = -0.35f;
    vertex_buffer_data[9 * n + 76] = -0.18f;
    vertex_buffer_data[9 * n + 77] = 0.0f;
    vertex_buffer_data[9 * n + 78] = -0.29f;
    vertex_buffer_data[9 * n + 79] = -0.23f;
    vertex_buffer_data[9 * n + 80] = 0.0f;
    vertex_buffer_data[9 * n + 81] = -0.29f;
    vertex_buffer_data[9 * n + 82] = -0.23f;
    vertex_buffer_data[9 * n + 83] = 0.0f;
    vertex_buffer_data[9 * n + 84] = -0.29f;
    vertex_buffer_data[9 * n + 85] = -0.18f;
    vertex_buffer_data[9 * n + 86] = 0.0f;
    vertex_buffer_data[9 * n + 87] = -0.35f;
    vertex_buffer_data[9 * n + 88] = -0.18f;
    vertex_buffer_data[9 * n + 89] = 0.0f;

    vertex_buffer_data[9 * n + 9] = -0.15f;
    vertex_buffer_data[9 * n + 10] = -0.8f;
    vertex_buffer_data[9 * n + 11] = 0.0f;
    vertex_buffer_data[9 * n + 12] = -0.15f;
    vertex_buffer_data[9 * n + 13] = -1.0f;
    vertex_buffer_data[9 * n + 14] = 0.0f;
    vertex_buffer_data[9 * n + 15] = -0.05f;
    vertex_buffer_data[9 * n + 16] = -1.0f;
    vertex_buffer_data[9 * n + 17] = 0.0f;
    vertex_buffer_data[9 * n + 18] = -0.05f;
    vertex_buffer_data[9 * n + 19] = -1.0f;
    vertex_buffer_data[9 * n + 20] = 0.0f;
    vertex_buffer_data[9 * n + 21] = -0.05f;
    vertex_buffer_data[9 * n + 22] = -0.8f;
    vertex_buffer_data[9 * n + 23] = 0.0f;
    vertex_buffer_data[9 * n + 24] = -0.15f;
    vertex_buffer_data[9 * n + 25] = -0.8f;
    vertex_buffer_data[9 * n + 26] = 0.0f;

    vertex_buffer_data[9 * n + 27] = 0.15f;
    vertex_buffer_data[9 * n + 28] = -0.8f;
    vertex_buffer_data[9 * n + 29] = 0.0f;
    vertex_buffer_data[9 * n + 30] = 0.15f;
    vertex_buffer_data[9 * n + 31] = -1.0f;
    vertex_buffer_data[9 * n + 32] = 0.0f;
    vertex_buffer_data[9 * n + 33] = 0.05f;
    vertex_buffer_data[9 * n + 34] = -1.0f;
    vertex_buffer_data[9 * n + 35] = 0.0f;
    vertex_buffer_data[9 * n + 36] = 0.05f;
    vertex_buffer_data[9 * n + 37] = -1.0f;
    vertex_buffer_data[9 * n + 38] = 0.0f;
    vertex_buffer_data[9 * n + 39] = 0.05f;
    vertex_buffer_data[9 * n + 40] = -0.8f;
    vertex_buffer_data[9 * n + 41] = 0.0f;
    vertex_buffer_data[9 * n + 42] = 0.15f;
    vertex_buffer_data[9 * n + 43] = -0.8f;
    vertex_buffer_data[9 * n + 44] = 0.0f;
    static GLfloat color_buffer_data[120000];

    for (int i = 0; i < 9 * n + 53; i += 3) {
        color_buffer_data[i] = 236.0 / 256.0;
        color_buffer_data[i + 1] = 100.0 / 256.0;
        color_buffer_data[i + 1] = 75.0 / 256.0;
    }
    for (int i = 9 * n + 54; i < 9 * n + 90; i += 3) {
        color_buffer_data[i] = 0.0 / 256.0;
        color_buffer_data[i + 1] = 204.0 / 256.0;
        color_buffer_data[i + 1] = 0.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 10010 * 3, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(1.0, 1.0, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f),
                                   glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (scale * translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->rotation += speed;
    // this->position.x += speed;
    // this->position.y += speed;
}
