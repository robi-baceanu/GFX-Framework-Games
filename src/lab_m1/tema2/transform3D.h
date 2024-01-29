#pragma once

#include "utils/glm_utils.h"
#include <math.h>


namespace transform3D
{
    // Translate matrix
    inline glm::mat4 Translate(glm::vec3 translate)
    {
        // Implement the translation matrix
        return glm::transpose(
            glm::mat4(1, 0, 0, translate.x,
                0, 1, 0, translate.y,
                0, 0, 1, translate.z,
                0, 0, 0, 1)
        );

    }

    // Scale matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        // Implement the scaling matrix
        return glm::transpose(
            glm::mat4(scaleX, 0, 0, 0,
                0, scaleY, 0, 0,
                0, 0, scaleZ, 0,
                0, 0, 0, 1)
        );

    }

    // Rotate matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {
        // Implement the rotation matrix
        return glm::transpose(
            glm::mat4(cos(radians), -1.0 * sin(radians), 0, 0,
                sin(radians), cos(radians), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1)
        );

    }

    // Rotate matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {
        // Implement the rotation matrix
        return glm::transpose(
            glm::mat4(cos(radians), 0, sin(radians), 0,
                0, 1, 0, 0,
                -1.0 * sin(radians), 0, cos(radians), 0,
                0, 0, 0, 1)
        );

    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {
        // Implement the rotation matrix
        return glm::transpose(
            glm::mat4(1, 0, 0, 0,
                0, cos(radians), -1.0 * sin(radians), 0,
                0, sin(radians), cos(radians), 0,
                0, 0, 0, 1)
        );

    }
}   // namespace transform3D