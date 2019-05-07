// ProjectImageryFS.glsl

layout(location = 0) out vec4 FragColor;

in vec2 v_textureCoordinates;

uniform sampler2D u_texture;
uniform sampler2D u_lonlatTex;
uniform vec4 u_rectangle;
uniform vec4 u_texRect;

const float PI = 3.14159265;

bool contains(vec4 rect, vec2 v)
{
    return v.x >= rect.x && v.x < rect.z && v.y >= rect.y && v.y < rect.w;
}

void main()
{
    vec2 lonlat = texture(u_lonlatTex, v_textureCoordinates).xy;
    if (abs(lonlat.x) > PI)
        discard;

    if (!contains(u_rectangle, lonlat))
        discard;

    const vec4 weight = vec4(0.0625, 0.125, 0.0625, 0.125);

    vec2 uv = vec2((lonlat.x - u_texRect.x) / (u_texRect.z - u_texRect.x),
                   (u_texRect.w - lonlat.y) / (u_texRect.w - u_texRect.y));

    vec4 color = texture(u_texture, uv) * 0.25;

    color += textureOffset(u_texture, uv, ivec2(-1, -1)) * weight.x;
    color += textureOffset(u_texture, uv, ivec2(-1,  0)) * weight.y;
    color += textureOffset(u_texture, uv, ivec2(-1,  1)) * weight.z;
    color += textureOffset(u_texture, uv, ivec2( 0, -1)) * weight.w;

    color += textureOffset(u_texture, uv, ivec2( 1, -1)) * weight.x;
    color += textureOffset(u_texture, uv, ivec2( 0,  1)) * weight.y;
    color += textureOffset(u_texture, uv, ivec2( 1,  1)) * weight.z;
    color += textureOffset(u_texture, uv, ivec2( 1,  0)) * weight.w;

    FragColor = color;
}
