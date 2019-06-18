#include "coin.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Coin::Coin(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 10;
    double ang = 360.0 / (double)(n);
    static GLfloat vertex_buffer_data[100000];
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
    this->object = create3DObject(GL_TRIANGLES, 100 * 3, vertex_buffer_data,
                                  color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(1, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::tick() { this->rotation += this->speed; }