#include "special.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Special::Special(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[100000];
    vertex_buffer_data[0] = 0.0;
    vertex_buffer_data[1] = 0.2;
    vertex_buffer_data[2] = 0.0;
    vertex_buffer_data[3] = 0.2;
    vertex_buffer_data[4] = 0.0;
    vertex_buffer_data[5] = 0.0;
    vertex_buffer_data[6] = -0.2;
    vertex_buffer_data[7] = 0.0;
    vertex_buffer_data[8] = 0.0;

    vertex_buffer_data[9] = -0.2;
    vertex_buffer_data[10] = 0.0;
    vertex_buffer_data[11] = 0.0;
    vertex_buffer_data[12] = 0.2;
    vertex_buffer_data[13] = 0.0;
    vertex_buffer_data[14] = 0.0;
    vertex_buffer_data[15] = 0.0;
    vertex_buffer_data[16] = -0.2;
    vertex_buffer_data[17] = 0.0;

    this->object =
        create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, color, GL_FILL);
}

void Special::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(0, 1, 0));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6,
    // 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Special::tick() {
    this->position.x -= 0.05f;
    this->position.y = sin(this->position.x);
}
