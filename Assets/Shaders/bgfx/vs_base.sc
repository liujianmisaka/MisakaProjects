$input a_position, a_color0, a_texcoord0
$output v_color0, v_texcoord0

uniform mat4 u_mvp;

void main() {
    v_texcoord0 = a_texcoord0;
    v_color0 = vec4(a_position, 1.0);
    gl_Position = u_mvp * vec4(a_position, 1.0);
}
