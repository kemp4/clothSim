#version 420 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
     // gl_Position = vec4(position, 1.0f);
    //TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = texCoord;
	Normal = mat3(transpose(inverse(model))) * aNormal;  
	FragPos = vec3(model * vec4(position, 1.0));
}
