#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform Light light2;
uniform sampler2D texture_diffuse;

void main()
{
    // Ambient
    vec3 ambient1 = light.ambient *material.diffuse;
    
    // Diffuse
    vec3 norm1 = normalize(Normal);
    vec3 lightDir1 = normalize(light.position - FragPos);
    float diff1 = max(dot(norm1, lightDir1), 0.0);
    vec3 diffuse1 = light.diffuse * diff1 * material.diffuse;
    
    // Specular
    vec3 viewDir1 = normalize(viewPos - FragPos);
    vec3 reflectDir1 = reflect(-lightDir1, norm1);
    float spec1 = pow(max(dot(viewDir1, reflectDir1), 0.0), material.shininess);
    vec3 specular1 = light.specular * (spec1 * material.specular);
    
    vec3 result1 = ambient1 + diffuse1 + specular1;


    // Ambient
    vec3 ambient2 = light2.ambient *material.diffuse;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light2.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse2 = light2.diffuse * diff * material.diffuse;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular2 = light2.specular * (spec * material.specular);
    
    vec3 result2 = ambient2 + diffuse2 + specular2;


    color = vec4(result1 + result2, 1.0f)*texture(texture_diffuse, TexCoords);


}