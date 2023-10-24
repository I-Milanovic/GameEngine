#version 330 core

const int MAX_POINT_LIGHTS = 1;
const int MAX_SPOT_LIGHTS = 1;
const float SPECULAR_POWER = 10;


in vec3 outPosition;
in vec3 outVertexNormal;
in vec2 outTexCoord;

out vec4 fragColor;

struct Attenuation {
	float constant;
	float linear;
	float exponent;
};

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float reflectance;
};

struct AmbientLight {
	float factor;
	vec3 color;
};

struct PointLight {
	vec3 position;
	vec3 color;
	float intensity;
	Attenuation att;
};

struct SpotLight {
	PointLight pointLight;
	vec3 coneDir;
	float cutOff;
};

struct DirLight {
	vec3 color;
	vec3 direction;
	float intensity;
};

uniform sampler2D texSampler;
uniform Material material;
uniform AmbientLight ambientLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform DirLight dirLight;

vec4 calcAmbient(AmbientLight ambientLight, vec4 ambient) {
	return vec4(ambientLight.factor * ambientLight.color, 1) * ambient;
}

vec4 calcLightColor(vec4 diffuse, vec4 specular, vec3 lightColor, float light_intensity, vec3 position, vec3 to_light_dir, vec3 normal) {

	vec4 diffuseColor = vec4(0, 0, 0, 1);
	vec4 specColor = vec4(0, 0, 0, 1);


	// Diffuse Light
	float diffuseFactor = max(dot(normal, to_light_dir), 0.0);
	diffuseColor = diffuse * vec4(lightColor, 1.0) * light_intensity * diffuseColor;

	// Speclar Light
	vec3 camera_direction = normalize(-position);
	vec3 from_light_dir = -to_light_dir;
	vec3 reflected_light = normalize(reflect(from_light_dir, normal));
	float specularFactor = max(dot(camera_direction, reflected_light), 0.0);
	specularFactor = pow(specularFactor, SPECULAR_POWER);
	specColor = specular * light_intensity * specularFactor * material.reflectance * vec4(lightColor, 1.0);

	return (diffuseColor + specColor);
}

vec4 calcPointLight(vec4 diffuse, vec4 specular, PointLight light, vec3 position, vec3 normal) {
	vec3 light_direction = light.position - position;
	vec3 to_light_dir = normalize(light_direction);
	vec4 light_color = calcLightColor(diffuse, specular, light.color, light.intensity, position, to_light_dir, normal);

	// Apply Attenuation
	float distance = length(light_direction);
	float attenuationInv = light.att.constant + light.att.linear * distance + light.att.exponent * distance * distance;

	return light_color / attenuationInv;
}

vec4 calcSpotLight(vec4 diffuse, vec4 specular, SpotLight light, vec3 position, vec3 normal) {
	vec3 light_direction = light.pointLight.position - position;
	vec3 to_light_dir = normalize(light_direction);
	vec3 from_light_dir = -to_light_dir;
	float spot_alfa = dot(from_light_dir, normalize(light.coneDir));
	
	vec4 color = vec4(0, 0, 0, 0);

	if(spot_alfa > light.cutOff) {
		color = calcPointLight(diffuse, specular, light.pointLight, position, normal);
		color *= (1.0 -(1.0 - spot_alfa) / (1.0 - light.cutOff));
	}

	return color;
}

vec4 calcDirLight(vec4 diffuse, vec4 specular, DirLight light, vec3 position, vec3 normal) {
	return calcLightColor(diffuse, specular ,light.color, light.intensity, position, normalize(light.direction), normal);
}

void main() {
	 vec4 tex_color = texture(texSampler, outTexCoord);
	 vec4 ambient = calcAmbient(ambientLight, tex_color + material.ambient);
	 vec4 diffuse = tex_color + material.diffuse;
	 vec4 specular = tex_color + material.specular;

	 vec4 diffuseSpecularComp = calcDirLight(diffuse, specular, dirLight, outPosition, outVertexNormal);
	 
	for(int i=0 ; i < MAX_POINT_LIGHTS; i++) {
		if(pointLights[i].intensity > 0) {
			diffuseSpecularComp += calcPointLight(diffuse, specular, pointLights[i], outPosition, outVertexNormal);		
		}	
	}
	
	for(int i = 0; i < MAX_SPOT_LIGHTS; i++) {
		if(spotLights[i].pointLight.intensity > 0){
			diffuseSpecularComp += calcSpotLight(diffuse, specular, spotLights[i], outPosition, outVertexNormal);
		}
	
	}

	fragColor = ambient + diffuseSpecularComp;
}