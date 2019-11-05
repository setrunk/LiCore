// BatchTable.glsl

uniform sampler2D batchTexture;
uniform int batchTextureInstancesPerRow;
uniform int batchTextureInstanceStride;
uniform int batchTextureAttributeOffset[8];

vec4 uintToColor(uint rgba)
{
    vec4 c;
    c.x =  rgba        & 0xff;
    c.y = (rgba >> 8)  & 0xff;
    c.z = (rgba >> 16) & 0xff;
    c.w =  rgba >> 24;
    return c / 255.0;
}

vec4 floatToColor(float f)
{
    uint rgba = f > 0 ? uint(f) : uint(-f) ^ 0xffffffff;
    return uintToColor(rgba);
}

ivec2 computeSt(int instanceId, int attributeId)
{
    int x = (instanceId % batchTextureInstancesPerRow)
            * batchTextureInstanceStride 
            + batchTextureAttributeOffset[attributeId];
    int y = instanceId / batchTextureInstancesPerRow;
    return ivec2(x, y);
}

vec4 sampleBatchTextureColor(int instanceId, int attributeId)
{
    ivec2 st = computeSt(instanceId, attributeId);
    vec4 value = floatToColor(float(texelFetch(batchTexture, st, 0).x));
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
