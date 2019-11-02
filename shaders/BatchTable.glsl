// BatchTable.glsl

uniform sampler2D batchTexture;
uniform int batchTextureInstancesPerRow;
uniform int batchTextureAttributeOffset[8];

ivec2 computeSt(int instanceId, int attributeId)
{
    int x = (instanceId % batchTextureInstancesPerRow) + batchTextureAttributeOffset[attributeId];
    int y = instanceId / batchTextureInstancesPerRow;
    return ivec2(x, y);
}

vec4 sampleBatchTextureColor(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    vec4 value = uintToColor(uint(texelFetch(batchTexture, st, 0).x));
    return value;
}

float sampleBatchTextureFloat(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    float value = texelFetch(batchTexture, st, 0).x;
    return value;
}

vec2 sampleBatchTextureVec2(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    vec2 value;
    value.x = texelFetch(batchTexture, st, 0).x;
    value.y = texelFetch(batchTexture, st + ivec2(1, 0), 0).x;
    return value;
}

vec3 sampleBatchTextureVec3(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    vec3 value;
    value.x = texelFetch(batchTexture, st, 0).x;
    value.y = texelFetch(batchTexture, st + ivec2(1, 0), 0).x;
    value.z = texelFetch(batchTexture, st + ivec2(2, 0), 0).x;
    return value;
}

vec4 sampleBatchTextureVec4(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    vec4 value;
    value.x = texelFetch(batchTexture, st, 0).x;
    value.y = texelFetch(batchTexture, st + ivec2(1, 0), 0).x;
    value.z = texelFetch(batchTexture, st + ivec2(2, 0), 0).x;
    value.w = texelFetch(batchTexture, st + ivec2(3, 0), 0).x;
    return value;
}
