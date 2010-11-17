varying float LightIntensity;

void main()
{
  vec3 color = vec3(1.0, 0.0, 0.0) * LightIntensity;
  gl_FragColor = vec4(color.x, color.y, color.z, 1.0);
}
