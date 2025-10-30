$input a_position,  a_color0   
$output v_color0

#include "../lib/bgfx.cmake/bgfx/src/bgfx_shader.sh"

void main()
{
    gl_Position = vec4(a_position.xyz, 1.0f);
    v_color0 = a_color0;
}