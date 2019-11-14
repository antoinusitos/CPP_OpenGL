#version 330 core
struct DirectionalLight
{
	vec3					myDirection;

	vec3					myAmbient;
	vec3					myDiffuse;
	vec3					mySpecular;
};

struct PointLight 
{    
    vec3					myPosition;
    
    float					myConstant;
    float					myLinear;
    float					myQuadratic;  

    vec3					myAmbient;
    vec3					myDiffuse;
    vec3					mySpecular;
}; 
#define NB_POINT_LIGHTS 4  

struct Material 
{
    sampler2D				myDiffuse;
    sampler2D				mySpecular;
    sampler2D				myEmissive;
    float					myShininess;
}; 

vec3 CalcDirectionalLight(DirectionalLight aLight, vec3 aNormal, vec3 aViewDir);
vec3 CalcPointLight(PointLight aLight, vec3 aNormal, vec3 aFragPos, vec3 aViewDir);  

out vec4					myFragColor;

in vec3						myFragPos;
in vec3						myNormal;
in vec2						myTexCoords;

uniform DirectionalLight	myDirectionalLight;
uniform Material			myMaterial;
uniform vec3				myViewPos;
uniform PointLight			myPointLights[NB_POINT_LIGHTS];

void main()
{
	// properties
	// --------
    vec3 norm = normalize(myNormal);
    vec3 viewDir = normalize(myViewPos - myFragPos);

    // phase 1: Directional lighting
	// --------
    vec3 result = CalcDirectionalLight(myDirectionalLight, norm, viewDir);
    // phase 2: Point lights
	// --------
    for(int i = 0; i < NB_POINT_LIGHTS; i++)
        result += CalcPointLight(myPointLights[i], norm, myFragPos, viewDir);    
    // phase 3: Spot light
	// --------
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    myFragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight aLight, vec3 aNormal, vec3 aViewDir)
{
	vec3 lightDir = normalize(-aLight.myDirection);
	// diffuse shading
	// -------
	float diff = max(dot(aNormal, lightDir), 0.0);
	// specular shading
	// -------
	vec3 reflectDir = reflect(-lightDir, aNormal);
	float spec = pow(max(dot(aViewDir, reflectDir), 0.0), myMaterial.myShininess);
	// combine results
	// -------
	vec3 ambient = aLight.myAmbient * vec3(texture(myMaterial.myDiffuse, myTexCoords));
	vec3 diffuse = aLight.myDiffuse * diff * vec3(texture(myMaterial.myDiffuse, myTexCoords));
	vec3 specular = aLight.mySpecular * spec * vec3(texture(myMaterial.mySpecular, myTexCoords));

	return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(PointLight aLight, vec3 aNormal, vec3 aFragPos, vec3 aViewDir)
{
	vec3 lightDir = normalize(aLight.myPosition - aFragPos);
    // diffuse shading
    float diff = max(dot(aNormal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, aNormal);
    float spec = pow(max(dot(aViewDir, reflectDir), 0.0), myMaterial.myShininess);
    // attenuation
    float distance    = length(aLight.myPosition - myFragPos);
    float attenuation = 1.0 / (aLight.myConstant + aLight.myLinear * distance + 
  			     aLight.myQuadratic * (distance * distance));    
    // combine results
    vec3 ambient  = aLight.myAmbient  * vec3(texture(myMaterial.myDiffuse, myTexCoords));
    vec3 diffuse  = aLight.myDiffuse  * diff * vec3(texture(myMaterial.myDiffuse, myTexCoords));
    vec3 specular = aLight.mySpecular * spec * vec3(texture(myMaterial.mySpecular, myTexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}