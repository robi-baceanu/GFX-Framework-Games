#version 330

// Input
// Get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_coordinate;
layout(location = 3) in vec3 v_color;

// Uniform properties

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Color;
uniform float HP;

// Output
// Output values to fragment shader

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_coordinate;
out vec3 frag_color;
out float frag_HP;

void main()
{
    // Send output to fragment shader
    float displacement = 0.2 * (5 - HP) * sin(v_position.x * 10) * 0.35;
    vec3 deformed_position = v_position + displacement * normalize(v_normal);

    frag_position = deformed_position;
    frag_normal = v_normal;
    frag_coordinate = v_coordinate;
    frag_color = Color;
    frag_HP = HP;

    // Compute gl_Position
    gl_Position = Projection * View * Model * vec4(deformed_position, 1.0);

}