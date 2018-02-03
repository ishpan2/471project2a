#version 330 core
out vec3 color;
in vec3 fragmentColor;
uniform int WINDOWHEIGHT;
uniform int WINDOWWIDTH;
uniform float time;
void main()
{
    float cx = WINDOWWIDTH/2;
    float rad = 100;
    float cy = WINDOWHEIGHT/2;
    if (distance(gl_FragCoord.xy, vec2(WINDOWWIDTH/2, WINDOWHEIGHT/2))<rad){
        float factor = distance(gl_FragCoord.xy, vec2(WINDOWWIDTH/2, WINDOWHEIGHT/2)) / 40;
        color = vec3(1.0f, 1.0f, 0.0f);
        
    }
    else{
        float fac = distance(gl_FragCoord.xy, vec2(WINDOWWIDTH/2, WINDOWHEIGHT/2)) / distance(vec2(WINDOWWIDTH/2, WINDOWHEIGHT/2), vec2(WINDOWWIDTH, WINDOWHEIGHT));
        color = vec3(1.0f, 0.8f, 0.4f);
    }
}
