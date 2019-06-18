#include "lightsaber.h"
#include "main.h"
#include "math.h"

#define PI 3.14159265

#define GLM_ENABLE_EXPERIMENTAL
Lightsaber::Lightsaber(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    // this->direction = -1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle. A cube has 6 faces with 2
    // triangles
    // each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[100000];
    vertex_buffer_data[0] = -0.2;
    vertex_buffer_data[1] = 0.05;
    vertex_buffer_data[2] = 0.0;
    vertex_buffer_data[3] = -0.2;
    vertex_buffer_data[4] = -0.05;
    vertex_buffer_data[5] = 0.0;
    vertex_buffer_data[6] = 0.03;
    vertex_buffer_data[7] = -0.05;
    vertex_buffer_data[8] = 0.0;
    vertex_buffer_data[9] = 0.03;
    vertex_buffer_data[10] = -0.05;
    vertex_buffer_data[11] = 0.0;
    vertex_buffer_data[12] = 0.03;
    vertex_buffer_data[13] = 0.05;
    vertex_buffer_data[14] = 0.0;
    vertex_buffer_data[15] = -0.2;
    vertex_buffer_data[16] = 0.05;
    vertex_buffer_data[17] = 0.0;

    vertex_buffer_data[18] = -0.03;
    vertex_buffer_data[19] = 0.05;
    vertex_buffer_data[20] = 0.0;
    vertex_buffer_data[21] = 0.03;
    vertex_buffer_data[22] = 0.05;
    vertex_buffer_data[23] = 0.0;
    vertex_buffer_data[24] = 0.0;
    vertex_buffer_data[25] = 0.1;
    vertex_buffer_data[26] = 0.0;

    vertex_buffer_data[27] = -0.03;
    vertex_buffer_data[28] = -0.05;
    vertex_buffer_data[29] = 0.0;
    vertex_buffer_data[30] = 0.03;
    vertex_buffer_data[31] = -0.05;
    vertex_buffer_data[32] = 0.0;
    vertex_buffer_data[33] = 0.0;
    vertex_buffer_data[34] = -0.1;
    vertex_buffer_data[35] = 0.0;

    vertex_buffer_data[36] = 0.05;
    vertex_buffer_data[37] = 0.05;
    vertex_buffer_data[38] = 0.0;
    vertex_buffer_data[39] = 0.62;
    vertex_buffer_data[40] = 0.05;
    vertex_buffer_data[41] = 0.0;
    vertex_buffer_data[42] = 0.62;
    vertex_buffer_data[43] = -0.05;
    vertex_buffer_data[44] = 0.0;
    vertex_buffer_data[45] = 0.62;
    vertex_buffer_data[46] = -0.05;
    vertex_buffer_data[47] = 0.0;
    vertex_buffer_data[48] = 0.05;
    vertex_buffer_data[49] = -0.05;
    vertex_buffer_data[50] = 0.0;
    vertex_buffer_data[51] = 0.05;
    vertex_buffer_data[52] = 0.05;
    vertex_buffer_data[53] = 0.0;

    static GLfloat color_buffer_data[100000];
    for (int i = 0; i < 36; i += 3) {
        color_buffer_data[i] = 105.0 / 256.0;
        color_buffer_data[i + 1] = 105.0 / 256.0;
        color_buffer_data[i + 2] = 105.0 / 256.0;
    }
    for (int i = 36; i < 54; i += 3) {
        color_buffer_data[i] = 135.0 / 256.0;
        color_buffer_data[i + 1] = 206.0 / 256.0;
        color_buffer_data[i + 2] = 250.0 / 256.0;
    }
    this->object = create3DObject(GL_TRIANGLES, 6 * 3, vertex_buffer_data,
                                  color_buffer_data, GL_FILL);
}

void Lightsaber::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(1, 1, 0));
    glm::mat4 translate = glm::translate(this->position);  // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 18 - 2.0f),
                                   glm::vec3(1, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant
    // to
    // rotate rotate          = rotate * glm::translate(glm::vec3(0, -0.6,
    // 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Lightsaber::tick() { this->rotation += 0.5; }
