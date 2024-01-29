#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{

    // Create square with given center, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill = true);

    // Create rectangle with given center, height, width and color
    Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float height, float width, glm::vec3 color);

    // Create star with given center, radius and color
    Mesh* CreateStar(const std::string& name, glm::vec3 center, float radius, glm::vec3 color);

    // Create hexagon with given center, outer radius, inner radius, outer color and inner color
    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float outerRadius, float innerRadius, glm::vec3 outerColor, glm::vec3 innerColor);

    // Create turret with given center, height and color
    Mesh* CreateTurret(const std::string& name, glm::vec3 center, float height, glm::vec3 color);

    // Create heart with given center and color
    Mesh* CreateHeart(const std::string& name, glm::vec3 center, glm::vec3 color);
}
