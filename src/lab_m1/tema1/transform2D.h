#pragma once

#include "utils/glm_utils.h"
#include <math.h>


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::transpose(
            glm::mat3(
                1, 0, translateX,
                0, 1, translateY,
                0, 0, 1
            )
        );
    }

    // Scale matrix
    inline glm::mat3 Scale(float scale)
    {
        return glm::transpose(
            glm::mat3(
                scale, 0, 0,
                0, scale, 0,
                0, 0, 1
            )
        );
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        return glm::transpose(
            glm::mat3(
                cos(radians), -1.0 * sin(radians), 0,
                sin(radians), cos(radians), 0,
                0, 0, 1
            )
        );
    }
}   // namespace transform2D