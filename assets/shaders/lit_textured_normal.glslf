// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

varying mediump vec2 vTexCoord;
varying mediump vec3 vObjectSpacePosition;
varying lowp vec3 vTangentSpaceLightVector;
varying lowp vec3 vTangentSpaceCameraVector;
uniform sampler2D texture_unit_0;   //texture
uniform sampler2D texture_unit_1;   //normalmap
uniform lowp vec4 color;
uniform lowp vec3 ambient_material;
uniform lowp vec3 diffuse_material;
uniform lowp vec3 specular_material;
uniform float shininess;


void main(void)
{
    lowp vec4 texture_color =  texture2D(texture_unit_0, vTexCoord);

    texture_color *= color;

    // Extract the perturbed normal from the texture:
    lowp vec3 tangent_space_normal =
      texture2D(texture_unit_1, vTexCoord).yxz * 2.0 - 1.0;

    vec3 N = normalize(tangent_space_normal);

    // Standard lighting math:
    vec3 L = normalize(vTangentSpaceLightVector);
    vec3 E = normalize(vTangentSpaceCameraVector);
    vec3 H = normalize(L + E);
    float df = abs(dot(N, L));  // change these abs() to max(0.0, ...
    float sf = abs(dot(N, H));  // to make the facing matter.
    sf = pow(sf, shininess);

    vec3 lighting = ambient_material +
        df * diffuse_material +
        sf * specular_material;
    gl_FragColor = vec4(lighting, 1) * texture_color;
}

