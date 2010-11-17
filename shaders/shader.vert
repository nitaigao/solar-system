varying float LightIntensity;

void main()
{
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

   vec3 LightPosition = vec3(0.0, 0.0, 10.0);
 
   vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
   vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);
   vec3 lightVec = (LightPosition - ecPosition);
  
   float diffuse = max(dot(lightVec, tnorm), 0.0);
   LightIntensity = diffuse;
}
