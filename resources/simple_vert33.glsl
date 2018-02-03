#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertexColor;
uniform mat4 P;
uniform mat4 MV;
uniform float time;
out vec3 fragmentColor;

void main()
{
	
    fragmentColor = vertexColor;
    vec3 Hello = vertPos;
    if (gl_VertexID % 3 == 1){
        if(gl_VertexID % 2 == 1){
            Hello = Hello * (.7 * abs(sin(time)) + .2);
        }
        else{
            Hello = Hello * (.7 * abs(cos(time)) + .2);
        }
    }
    else if(gl_VertexID % 3 == 0){
        if(gl_VertexID % 2 == 1){
            Hello = Hello * (.7 * abs(sin(time)) + .2);
        }
        else{
            Hello = Hello * (.7 * abs(cos(time)) + .2);
        }
    }
    fragmentColor = vertexColor;
    gl_Position = P * MV * vec4(Hello, 1.0);
}
