#version 430

// ComputeShader.glsl

layout (local_size_x = 32, local_size_y = 32) in;
layout (rgba8) uniform image2D texOutput;

void main()
{
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 screenSize = imageSize(texOutput);

    vec3 result = vec3(vec2(pos) / vec2(screenSize-1), 1.0);

    imageStore(texOutput, pos, vec4(result, 1.0));
}
