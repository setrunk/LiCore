// ComputeCartographicCS.glsl

layout (local_size_x = 32, local_size_y = 32) in;

layout (r32f) uniform image2D texDepth;
layout (rg32f) uniform image2D texOutput;

uniform vec4 czm_frustumFarPlanes;
uniform vec2 czm_currentFrustum;
uniform dmat4 inverseView;

const dvec3 czm_radii = dvec3(6378137.0, 6378137.0, 6356752.3142451793);
const dvec3 czm_radiiSquared = czm_radii * czm_radii;
const dvec3 czm_oneOverRadii = 1.0 / czm_radii;
const dvec3 czm_oneOverRadiiSquared = czm_oneOverRadii * czm_oneOverRadii;
const double czm_EPSILON12 = 0.000000000001;

dvec4 computePositionEC(double sceneDepth, dvec2 texcoords)
{
    dvec4 planes = dvec4(czm_frustumFarPlanes) * sceneDepth;
    dvec2 leftBottom = planes.zy;
    dvec2 rightTop = planes.wx;
    double zFar = double(czm_currentFrustum.y);

    dvec4 positionEC;
    positionEC.xy = leftBottom + (rightTop - leftBottom) * texcoords;
    positionEC.z = -sceneDepth * zFar;
    positionEC.w = 1.0;

    return positionEC;
}

dvec3 scaleToGeodeticSurface(dvec3 cartesian)
{
    dvec3 position2 = cartesian * cartesian * czm_oneOverRadiiSquared;

    // Compute the squared ellipsoid norm.
    double squaredNorm = position2.x + position2.y + position2.z;
    double ratio = sqrt(1.0 / squaredNorm);

    // As an initial approximation, assume that the radial intersection is the projection point.
    dvec3 intersection = cartesian * ratio;

    const double centerToleranceSquared = 0.1;
    // If the position is near the center, the iteration will not converge.
    if (squaredNorm < centerToleranceSquared) {
        return intersection;//!isfinite(ratio) ? vec3(0.0) : intersection;
    }

    // Use the gradient at the intersection point in place of the true unit normal.
    // The difference in magnitude will be absorbed in the multiplier.
    dvec3 gradient = intersection * czm_oneOverRadiiSquared * 2.0;

    // Compute the initial guess at the normal vector multiplier, lambda.
    double lambda = (1.0 - ratio) * length(cartesian) / (0.5 * length(gradient));
    double correction = 0.0;

    double func;
    double denominator;
    dvec3 multiplier;
    dvec3 multiplier2;
    dvec3 multiplier3;

    do {
        lambda -= correction;
        multiplier = 1.0 / (1.0 + lambda * czm_oneOverRadiiSquared);
        multiplier2 = multiplier * multiplier;
        multiplier3 = multiplier2 * multiplier;
        func = dot(position2, multiplier2) - 1.0;

        // "denominator" here refers to the use of this expression in the velocity and acceleration
        // computations in the sections to follow.
        dvec3 v = position2 * multiplier3 * czm_oneOverRadiiSquared;
        denominator = v.x + v.y + v.z;
        // denominator = position2.x * multiplier3.x * czm_oneOverRadiiSquared.x +
        // position2.y * multiplier3.y * czm_oneOverRadiiSquared.y +
        // position2.z * multiplier3.z * czm_oneOverRadiiSquared.z;
        correction = func / (-2.0 * denominator);
    } while (abs(func) > czm_EPSILON12);

    return cartesian * multiplier;
}

dvec3 geodeticSurfaceNormal(dvec3 cartesian)
{
    dvec3 p = cartesian * czm_oneOverRadiiSquared;
    return normalize(p);
}

vec4 cartesianToCartographic(dvec4 cartesian)
{
    dvec3 p = scaleToGeodeticSurface(cartesian.xyz);
    vec3 n = vec3(geodeticSurfaceNormal(p));
    return vec4(atan(n.y, n.x), asin(n.z), 0.0, 0.0);
}

void main()
{
    ivec2 screenSize = imageSize(texDepth);
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    if (pos.x >= screenSize.x || pos.y >= screenSize.y)
        return;

    float depth = imageLoad(texDepth, pos).x;
    if (depth == 1.0)
    {
        imageStore(texOutput, pos, vec4(10.0));
        return;
    }

    dvec4 positionEC = computePositionEC(depth, vec2(pos) / (vec2(screenSize) - 1.0));
    vec4 result = cartesianToCartographic(inverseView * positionEC);

    imageStore(texOutput, pos, result);
}
