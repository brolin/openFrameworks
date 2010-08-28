//find from here
//http://www.clockworkcoders.com/oglsl/tutorial10.htm


varying vec3 vNormal;
varying vec3 vVertex;
uniform vec3 hue = vec3(0.0,0.8,0.6);

#define shininess 1.0

void main (void)
{

// Material Color:
vec4 color0 = vec4(1,1,1, 1.0);

// Silhouette Color:
vec4 color1 = vec4(0.05, 0.05, 0.05, 1.0);
vec4 color2 = vec4(hue[0],hue[1],hue[2], 1.0);
// Specular Color:


// Lighting
vec3 eyePos = vec3(400.0,100.0,1000.0);
vec3 lightPos = vec3(400.0,100.0,100.0);

vec3 Normal = normalize(gl_NormalMatrix * vNormal);
vec3 EyeVert = normalize(eyePos - vVertex);
vec3 LightVert = normalize(lightPos - vVertex);
vec3 EyeLight = normalize(LightVert+EyeVert);

// Simple Silhouette
float sil = max(dot(Normal,EyeVert), 0.0);
if (sil>-0.05 && sil < 0.001) gl_FragColor = color1;
else
  {
   gl_FragColor = color0;

   // Specular part
   float spec = pow(max(dot(Normal,EyeLight),0.0), shininess);

   if (spec> -0.2 &&spec < 0.2) gl_FragColor *= 0.8;
   else gl_FragColor = color2;

   // Diffuse part
   float diffuse = max(dot(Normal,LightVert),0.0);
   if (diffuse >-0.5 && diffuse < 0.5) gl_FragColor *=0.8;

   if(spec > 0.9) gl_FragColor = vec4(0.8,0.8,0.8,1);
   }
}
