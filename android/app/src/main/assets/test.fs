#ifdef GL_ES
precision mediump float;
#endif
varying vec4 V_Color; //shader 数据传递
void main(){
    gl_FragColor=V_Color;
}