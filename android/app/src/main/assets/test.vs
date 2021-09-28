attribute vec4 position;
attribute vec4 color;
uniform mat4 U_ModelMatrix;
uniform mat4 U_ViewMatrix;
uniform mat4 U_ProjectionMatrix;
varying vec4 V_Color;
void main(){
    V_Color=color; 
    //点
    gl_Position=U_ProjectionMatrix*U_ViewMatrix*U_ModelMatrix*position;
}