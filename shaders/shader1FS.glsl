#version 420 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  

out vec4 color;

uniform sampler2D ourTexture;
//uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 viewPos; 

void main()
{
	//vec3 ambient = ambientStrength * lightColor;
   // vec3 lightColor2=vec3(0.5f,0.5f,0.5f);
	//color =  );	//vec4(1.0f, 0.5f, 0.2f, 1.0f);
	
	//diffuse
	vec3 lightPos= vec3(0,3,0);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * spec * lightColor;  


	color = vec4((lightColor + diffuse+specular),1) *  texture(ourTexture, TexCoord);
	//color = vec4(result, 1.0);
}
