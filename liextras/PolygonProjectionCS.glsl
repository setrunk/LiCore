// PolygonProjectionCS.glsl

layout (local_size_x = 32, local_size_y = 32) in;

layout (r32f, binding = 0) uniform image2D t0_Depth;
layout (rg32f, binding = 1) uniform image2D t1_Info;
layout (rgb32ui, binding = 2) uniform image2D t2_Index;
layout (rg32f, binding = 3) uniform image2D t3_Vertex;
layout (r11f_g11f_b10f, binding = 4) uniform image2D t4_Color;

uniform vec4 u_color;
uniform float cellSize;
uniform vec4 bounds;
uniform mat4 viewToLocal;
uniform vec4 czm_frustumFarPlanes;
uniform vec2 czm_currentFrustum;

const float ABS_DOUBLE_0 = 0.0001;
	
float getTriangleArea(vec2 p0, vec2 p1, vec2 p2)
 {
	vec2 ab = vec2(p1.x - p0.x, p1.y - p0.y);
	vec2 bc = vec2(p2.x - p1.x, p2.y - p1.y);
	return abs((ab.x * bc.y - ab.y * bc.x) / 2.0);
}
	
bool isInTriangle(vec2 a, vec2 b, vec2 c, vec2 d)
{
	float sabc = getTriangleArea(a, b, c);
	float sadb = getTriangleArea(a, d, b);
	float sbdc = getTriangleArea(b, d, c);
	float sadc = getTriangleArea(a, d, c);
	float sumSuqar = sadb + sbdc + sadc;
		
	return (-ABS_DOUBLE_0 < (sabc - sumSuqar) && (sabc - sumSuqar) < ABS_DOUBLE_0);
}

vec4 computePositionEC(float sceneDepth, vec2 texcoords)
{
    vec4 planes = czm_frustumFarPlanes * sceneDepth;
    vec2 leftBottom = planes.zy;
    vec2 rightTop = planes.wx;
    float zFar = czm_currentFrustum.y;

    vec4 positionEC;
    positionEC.xy = leftBottom + (rightTop - leftBottom) * texcoords;
    positionEC.z = -sceneDepth * zFar;
    positionEC.w = 1.0;

    return positionEC;
}

bool contains(vec4 rect, vec2 pos)
{
	return pos.x > rect.x && pos.x < rect.z && pos.y > rect.y && pos.y < rect.w;
}

vec2 getVertex(int index, , ivec2 vertexTexSize)
{
	ivec2 uv;
	uv.x = index % vertexTexSize.x;
	uv.y = index / vertexTexSize.x;
	return imageLoad(t3_Vertex, uv).xy;
}

void getTriangle(int index, ivec2 indexTexSize, ivec2 vertexTexSize, out vec2 v0, out vec2 v1, out vec2 v2)
{
	ivec2 uv;
	uv.x = index % indexTexSize.x;
	uv.y = index / indexTexSize.x;
	ivec3 tri = ivec3(imageLoad(t2_Index, uv).xyz);
	v0 = getVertex(tri.x, vertexTexSize);
	v1 = getVertex(tri.y, vertexTexSize);
	v2 = getVertex(tri.z, vertexTexSize);
}

void main()
{
	ivec2 screenSize = imageSize(t4_Color);
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
	if (pos.x >= screenSize.x || pos.y >= screenSize.y)
		return;
		
	float depth = imageLoad(t0_Depth, pos).x;
	if (depth == 1.0)
		return;
		
	vec2 texcoords = vec2(pos) / (vec2(screenSize) - 1.0);
	vec4 positionEC = computePositionEC(depth, texcoords);
	vec4 localPos = viewToLocal * positionEC;
	if (!contains(bounds, localPos.xy))
		return;
	
	ivec2 infoTexSize = imageSize(t1_Info);
	float cellSize = params.w;
	ivec2 tileId = ivec2(floor((localPos.xy - bounds.xy) / cellSize));
	ivec2 info = ivec2(imageLoad(t1_Info, tileId).xy);
	int start = info.x;
	int count = info.y;
	
	ivec2 indexTexSize = imageSize(t2_Index);
	ivec2 vertexTexSize = imageSize(t3_Vertex);
	vec2 v0, v1, v2;
	
	for (int i = 0; i < count; i+=3)
	{
		getTriangle(i+start, indexTexSize, vertexTexSize, v0, v1, v2);
		
		if (isInTriangle(v0, v1, v2, localPos.xy))
		{
			imageStore(t4_Color, pos, u_color);
			return;
		}
	}
}
