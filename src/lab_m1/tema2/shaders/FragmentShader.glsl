#version 330

// Input
// Get values from vertex shader

in vec3 frag_color;
in vec3 frag_normal;
in float frag_HP;


// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // Write pixel out color
    vec3 new_color = frag_color - ((5 - frag_HP) / 5) * vec3(0.2, 0.2, 0.2);
    out_color = vec4(new_color, 1);
}