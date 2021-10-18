#version 330 core

mat4 brightnessMatrix(float b) {
    if (b > 1.0) b = 1.0;
    if (b < 0.0) b = 0.0;
    return mat4(b, 0.0f, 0.0f, 0.0f,
                0.0f, b, 0.0f, 0.0f,
                0.0f, 0.0f, b, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

out vec4 FragColor;

struct Material {
    vec3 color;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform float brightness;

void main()
{
    // ambient
    vec3 ambient = material.color * light.ambient * texture(material.diffuse, TexCoords).rgb;


    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    // vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    // vec3 specular = light.specular * (spec * material.specular);

    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = brightnessMatrix(brightness) * vec4(result, 1.0);
}
