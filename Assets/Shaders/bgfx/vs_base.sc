$input a_position, a_color0
$output v_color0

void main() {
    v_color0 = a_color0;
    gl_Position = vec4(a_position, 1.0);
}