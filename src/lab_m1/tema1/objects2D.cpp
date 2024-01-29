#include "objects2D.h"

#include <vector>
#include <math.h>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* objects2D::CreateSquare(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    float side = length / 2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-side, -side, 0), color),
        VertexFormat(center + glm::vec3(side, -side, 0), color),
        VertexFormat(center + glm::vec3(side, side, 0), color),
        VertexFormat(center + glm::vec3(-side, side, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objects2D::CreateRectangle(
    const std::string& name,
    glm::vec3 center,
    float height,
    float width,
    glm::vec3 color)
{
    float heightSide = height / 2;
    float widthSide = width / 2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-widthSide, -heightSide, 0), color),
        VertexFormat(center + glm::vec3(widthSide, -heightSide, 0), color),
        VertexFormat(center + glm::vec3(widthSide, heightSide, 0), color),
        VertexFormat(center + glm::vec3(-widthSide, heightSide, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    indices.push_back(0);
    indices.push_back(2);

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* objects2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color)
{
    const float PI = 3.1415926535898;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(radius * sin(0), radius * cos(0), 1), color),                       // 0
        VertexFormat(center + glm::vec3(radius * sin(2 * PI / 5), radius * cos(2 * PI / 5), 1), color),     // 1
        VertexFormat(center + glm::vec3(radius * sin(4 * PI / 5), radius * cos(4 * PI / 5), 1), color),     // 2
        VertexFormat(center + glm::vec3(radius * sin(6 * PI / 5), radius * cos(6 * PI / 5), 1), color),     // 3
        VertexFormat(center + glm::vec3(radius * sin(8 * PI / 5), radius * cos(8 * PI / 5), 1), color),     // 4
        VertexFormat(center + glm::vec3(10.8981379200804, -3.5410196624968, 1), color),                     // 5
        VertexFormat(center + glm::vec3(-10.8981379200804, -3.5410196624969, 1), color),                    // 6
        VertexFormat(center + glm::vec3(0, -11.4589803375032, 1), color)                                    // 7
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        2, 0, 6, 
        3, 5, 0, 
        7, 1, 4 
    };

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* objects2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float outerRadius,
    float innerRadius,
    glm::vec3 outerColor,
    glm::vec3 innerColor)
{
    const float PI = 3.1415926535898;

    std::vector<VertexFormat> vertices =
    {
        // Outer hexagon
        VertexFormat(center + glm::vec3(0, 0, 2), outerColor),                                                              // 0
        VertexFormat(center + glm::vec3(outerRadius * sin(0), outerRadius * cos(0), 2), outerColor),                        // 1
        VertexFormat(center + glm::vec3(outerRadius * sin(PI / 3), outerRadius * cos(PI / 3), 2), outerColor),              // 2
        VertexFormat(center + glm::vec3(outerRadius * sin(2 * PI / 3), outerRadius * cos(2 * PI / 3), 2), outerColor),      // 3
        VertexFormat(center + glm::vec3(outerRadius * sin(PI), outerRadius * cos(PI), 2), outerColor),                      // 4
        VertexFormat(center + glm::vec3(outerRadius * sin(4 * PI / 3), outerRadius * cos(4 * PI / 3), 2), outerColor),      // 5
        VertexFormat(center + glm::vec3(outerRadius * sin(5 * PI / 3), outerRadius * cos(5 * PI / 3), 2), outerColor),      // 6
        // Inner hexagon
        VertexFormat(center + glm::vec3(0, 0, 3), innerColor),                                                              // 7
        VertexFormat(center + glm::vec3(innerRadius * sin(0), innerRadius * cos(0), 3), innerColor),                        // 8
        VertexFormat(center + glm::vec3(innerRadius * sin(PI / 3), innerRadius * cos(PI / 3), 3), innerColor),              // 9
        VertexFormat(center + glm::vec3(innerRadius * sin(2 * PI / 3), innerRadius * cos(2 * PI / 3), 3), innerColor),      // 10
        VertexFormat(center + glm::vec3(innerRadius * sin(PI), innerRadius * cos(PI), 3), innerColor),                      // 11
        VertexFormat(center + glm::vec3(innerRadius * sin(4 * PI / 3), innerRadius * cos(4 * PI / 3), 3), innerColor),      // 12
        VertexFormat(center + glm::vec3(innerRadius * sin(5 * PI / 3), innerRadius * cos(5 * PI / 3), 3), innerColor)       // 13
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        // Outer hexagon
        0, 1, 6,
        0, 6, 5,
        0, 5, 4,
        0, 4, 3,
        0, 3, 2,
        0, 2, 1,
        // Inner hexagon
        7, 8, 13,
        7, 13, 12,
        7, 12, 11,
        7, 11, 10,
        7, 10, 9,
        7, 9, 8
    };

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* objects2D::CreateTurret(
    const std::string& name,
    glm::vec3 center,
    float height, 
    glm::vec3 color)
{
    float h = height / 2;
    float l = height / 4;
    float g = height / 16; 
    float r = height / 2 + g;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, h, 2), color),   // 0
        VertexFormat(center + glm::vec3(-l, 0, 2), color),  // 1
        VertexFormat(center + glm::vec3(0, -h, 2), color),  // 2
        VertexFormat(center + glm::vec3(l, g, 2), color),   // 3
        VertexFormat(center + glm::vec3(l, -g, 2), color),  // 4
        VertexFormat(center + glm::vec3(r, g, 2), color),   // 5
        VertexFormat(center + glm::vec3(r, -g, 2), color)   // 6
    };

    Mesh* turret = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        2, 4, 3,
        4, 5, 3,
        4, 6, 5
    };

    turret->InitFromData(vertices, indices);
    return turret;
}

Mesh* objects2D::CreateHeart(
    const std::string& name,
    glm::vec3 center,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, -50, 0), color),     // 0
        VertexFormat(center + glm::vec3(-50, 10, 0), color),    // 1
        VertexFormat(center + glm::vec3(50, 10, 0), color),     // 2
        VertexFormat(center + glm::vec3(-50, 35, 0), color),    // 3
        VertexFormat(center + glm::vec3(50, 35, 0), color),     // 4
        VertexFormat(center + glm::vec3(-35, 50, 0), color),    // 5
        VertexFormat(center + glm::vec3(35, 50, 0), color),     // 6
        VertexFormat(center + glm::vec3(-10, 50, 0), color),    // 7
        VertexFormat(center + glm::vec3(10, 50, 0), color),     // 8
        VertexFormat(center + glm::vec3(0, 30, 0), color)       // 9
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 9, 7,
        0, 7, 5,
        0, 5, 3,
        0, 3, 1,
        0, 2, 4,
        0, 4, 6,
        0, 6, 8,
        0, 8, 9
    };

    heart->InitFromData(vertices, indices);
    return heart;
}