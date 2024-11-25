$input v_color0, v_texcoord0

uniform sampler2D s_tex;

void main() {
    gl_FragColor = texture2D(s_tex, v_texcoord0);
}
