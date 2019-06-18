#include "dragon.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[100000];
    vertex_buffer_data[0] = -0.1;
    vertex_buffer_data[1] = 0.2;
    vertex_buffer_data[2] = 0.0;
    vertex_buffer_data[3] = -0.35;
    vertex_buffer_data[4] = -0.05;
    vertex_buffer_data[5] = 0.0;
    vertex_buffer_data[6] = 0.0;
    vertex_buffer_data[7] = 0.0;
    vertex_buffer_data[8] = 0.0;

    vertex_buffer_data[9] = 0.0;
    vertex_buffer_data[10] = 0.0;
    vertex_buffer_data[11] = 0.0;
    vertex_buffer_data[12] = -0.3;
    vertex_buffer_data[13] = -0.8;
    vertex_buffer_data[14] = 0.0;
    vertex_buffer_data[15] = 0.2;
    vertex_buffer_data[16] = -1.5;
    vertex_buffer_data[17] = 0.0;

    vertex_buffer_data[18] = 0.04;
    vertex_buffer_data[19] = -0.3;
    vertex_buffer_data[20] = 0.0;
    vertex_buffer_data[21] = 0.4;
    vertex_buffer_data[22] = -1.2;
    vertex_buffer_data[23] = 0.0;
    vertex_buffer_data[24] = 0.5;
    vertex_buffer_data[25] = 0.15;
    vertex_buffer_data[26] = 0.0;

    static GLfloat color_buffer_data[100000];
    for (int i = 0; i < 18; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 69.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }
    for (int i = 18; i < 27; i += 3) {
        color_buffer_data[i] = 255.0 / 256.0;
        color_buffer_data[i + 1] = 215.0 / 256.0;
        color_buffer_data[i + 2] = 0.0 / 256.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 3 * 3, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(1.5, 1.5, 0));
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

void Dragon::tick() {
    this->position.x -= 0.05f;
    this->position.y = 1.5 * sin(this->position.x);
}

void Dragon::tick1() {
    if (this->position.y + 2.7 > 0.05 && direction == -1.0) {
        this->position.y += this->direction * 0.05;
    } else {
        this->direction = 1.0;
    }
    if (this->position.y - 4.0 < -0.05 && direction == 1.0) {
        this->position.y += this->direction * 0.05;
    } else {
        this->direction = -1.0;
    }
}
