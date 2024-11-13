#if BGFX_SHADER_LANGUAGE_GLSL
    #define varying out
#else
    #define varying varying
#endif

varying vec4 v_color0;
