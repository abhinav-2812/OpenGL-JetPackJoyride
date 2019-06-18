#include "boomerang.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 2.0;
    this->temp = 0.0;
    this->direction = -1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2 triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[100000];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = 0.0f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.0f;
    vertex_buffer_data[4] = -0.5f;
    vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6] = -0.3f;
    vertex_buffer_data[7] = 0.6f;
    vertex_buffer_data[8] = 0.0f;
    vertex_buffer_data[9] = 0.3f;
    vertex_buffer_data[10] = 0.6f;
    vertex_buffer_data[11] = 0.0f;
    vertex_buffer_data[12] = 0.0f;
    vertex_buffer_data[13] = 0.0f;
    vertex_buffer_data[14] = 0.0f;
    vertex_buffer_data[15] = 0.0f;
    vertex_buffer_data[16] = -0.5f;
    vertex_buffer_data[17] = 0.0f;

    this->object =
        create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(0.5, 0.5, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::tick() {
    this->rotation += this->speed;
    // if (this->position.x - (this->cx - 20.0) > 0.05 && direction == -1.0) {
    //     this->position.x += this->direction * 0.1;
    //     this->position.y =
    //         1.0 * 3.0 *
    //         sqrt(1.0 - (this->position.x * this->position.x) / 100.0);
    // } else {
    //     this->direction = 1.0;
    // }
    // // if (this->position.x == -10.0f) {
    // //     this->position.x += this->direction * 0.1;
    // //     this->position.y =
    // //         5.0 * sqrt(1 - (this->position.x * this->position.x) / 100.0);
    // // }
    // if (this->position.x - this->cx < -0.05 && direction == 1.0) {
    //     this->position.x += this->direction * 0.1;
    //     this->position.y =
    //         -1.0 * 3.0 *
    //         sqrt(1.0 - (this->position.x * this->position.x) / 100.0);
    // } else {
    //     this->direction = -1.0;
    // }
    this->position.x = 5.0 * cos(this->ang) + this->cx;
    this->position.y = 3.0 * sin(this->ang) + this->cy;
    ang += 0.01;

    // if (this->position.x == 10.0f) {
    //     this->position.x += this->direction * 0.1;
    //     this->position.y =
    //         5.0 * sqrt(1 - (this->position.x * this->position.x) / 100.0);
    // }
}
