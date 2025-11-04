$input a_position,  a_color0   
$output v_color0

#include "../lib/bgfx.cmake/bgfx/src/bgfx_shader.sh"

void main()
{
    gl_Position = vec4(a_position,0.f, 1.0f);
    v_color0 = vec4(1.f,0.f,1.f,1.f);
}