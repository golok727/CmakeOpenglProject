@type vertex
#version 460 core
layout (location = 0) in vec3 a_Position; 
layout (location = 1) in vec2 a_TexCoord; 
uniform mat4 u_Projection;
uniform mat4 u_Transform;

out vec2 TexCoord; 
void main()
{
  TexCoord = a_TexCoord; 
  vec4 position = vec4(a_Position, 1.0); 
  gl_Position = u_Projection * u_Transform * position; 
}

@type fragment
#version 460 core

out vec4 color; 
in vec2 TexCoord; 
uniform sampler2D u_ImageTexture;

void main()
{
  color = texture(u_ImageTexture, TexCoord); 
}