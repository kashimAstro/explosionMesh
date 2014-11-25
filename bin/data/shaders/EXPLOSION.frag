#version 150

in vec3 fcolor;
out vec4 frag_color;

void main() {
  frag_color = vec4(fcolor, 1.0);
}
