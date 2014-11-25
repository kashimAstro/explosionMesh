#version 150

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 modelview;
uniform float time;

in vec3 gnormal[];

out vec3 fcolor;
out vec3 position_eye;
out vec3 n;

void main() {
  vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
  vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);

  vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
  vec3 normal = normalize(cross(b, a));
  vec3 new_center = normal * time + center;
  
  vec3 diff = new_center - center;

  for (int i = 0; i < 3; ++i) {
	    fcolor = vec3(i/2,0.,0.);
	    position_eye = (modelview * (gl_in[i].gl_Position + vec4(diff, 0.0))).xyz;
	    n = gnormal[i];
	    gl_Position = projection * vec4(position_eye, 1.0);
	    EmitVertex();
  }

  EndPrimitive();
}
