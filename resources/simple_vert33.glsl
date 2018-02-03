#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertexColor;
uniform mat4 P;
uniform mat4 MV;
uniform float time;
out vec3 fragmentColor;

void main()
{
    vec3 nePos = vertPos;
    if (gl_VertexID % 3 == 1 || gl_VertexID % 3 == 0){
        if(gl_VertexID % 2 == 1){
            nePos = nePos * (.5 * abs(sin(time)) + .4);
        }
        else{
            nePos = nePos * (.5 * abs(cos(time)) + .24;
        }
    }
    fragmentColor = vertexColor;
    gl_Position = P * MV * vec4(nePos, 1.0);
}
