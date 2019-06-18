#include "ring.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[100000];
    int j = 0;
    for (int i = 1; i < 90; i += 2, j += 9) {
        vertex_buffer_data[j] = 1.0 * cos(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 1] = 1.0 * sin(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 2] = 0.0f;
        vertex_buffer_data[j + 3] = 2.0 * cos(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 4] = 2.0 * sin(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 5] = 0.0f;
        vertex_buffer_data[j + 6] =
            2.0 * cos(2.0 * (double)(i + 1) * PI / 180.0);
        vertex_buffer_data[j + 7] =
            2.0 * sin(2.0 * (double)(i + 1) * PI / 180.0);
        vertex_buffer_data[j + 8] = 0.0f;
    }
    for (int i = 0; i < 90; i += 2, j += 9) {
        vertex_buffer_data[j] = 2.0 * cos(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 1] = 2.0 * sin(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 2] = 0.0f;
        vertex_buffer_data[j + 3] =
            1.0 * cos(2.0 * (double)(i + 1) * PI / 180.0);
        vertex_buffer_data[j + 4] =
            1.0 * sin(2.0 * (double)(i + 1) * PI / 180.0);
        vertex_buffer_data[j + 5] = 0.0f;
        vertex_buffer_data[j + 6] = 1.0 * cos(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 7] = 1.0 * sin(2.0 * (double)(i)*PI / 180.0);
        vertex_buffer_data[j + 8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 10000 * 3, vertex_buffer_data,
                                  color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(2, 2, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6,
    // 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::tick() {}
