#include "firebeam.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Firebeam::Firebeam(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[] = {
        -0.8f, 0.05f,  0.0f, -0.8f, -0.05f, 0.0f, 0.8f,  -0.05f, 0.0f,
        0.8f,  -0.05f, 0.0f, 0.8f,  0.05f,  0.0f, -0.8f, 0.05f,  0.0f,
        -0.8f, 0.15f,  0.0f, -0.9f, 0.0f,   0.0f, -0.8,  -0.15,  0.0f,
        0.8f,  0.15f,  0.0f, 0.9f,  0.0f,   0.0f, 0.8,   -0.15,  0.0f};

    static GLfloat color_buffer_data[36];
    for (int i = 0; i < 18; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 215.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }
    for (int i = 18; i < 36; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 105.0 / 256.0;
        color_buffer_data[i + 2] = 32.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(5, 5, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(0, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6,
    // 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::tick() {
    this->rotation += this->speed;
    this->timer += 1.0 / 60.0;
    if (this->timer - 5.0 > -0.000005) off = 1;
    if (this->position.y + 2.0 > 0.05 && direction == -1.0) {
        this->position.y += this->direction * 0.1;
    } else {
        this->direction = 1.0;
    }
    if (this->position.y - 3.0 < -0.05 && direction == 1.0) {
        this->position.y += this->direction * 0.1;
    } else {
        this->direction = -1.0;
    }
}
