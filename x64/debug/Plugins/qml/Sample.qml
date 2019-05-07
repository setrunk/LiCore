import QtQuick 2.7
import LiQuick.Core 1.0

Entity {
    id: root

    function toRadians(degrees) {
        var RADIANS_PER_DEGREE = 3.14159265358979 / 180.0;
        return degrees * RADIANS_PER_DEGREE;
    }

    function toDegrees(radians) {
        var DEGREES_PER_RADIAN = 180.0 / 3.14159265358979;
        return radians * DEGREES_PER_RADIAN;
    }

    Texture2D {
        id: tex
        width: 1024
        height: 1024
        format: Texture.RGBA8_UNorm
        wrapModeS: Texture.ClampToEdge
        wrapModeT: Texture.ClampToEdge
        minificationFilter: Texture.Linear
        magnificationFilter: Texture.Linear
    }

    Entity {
        id: computeEntity

        ShaderProgram {
            id: computeShader
            computeShaderCode: loadSource(Qt.resolvedUrl('./shaders/ComputeShader.glsl'))
        }

        ComputeRenderer {
            id: computeRenderer
            workGroupX: 32
            workGroupY: 32
            material: Material {
                shaderProgram: computeShader
                parameters: [
                    Parameter { name: "texOutput"; value: tex }
                ]
            }
        }
    }

    Entity {
        id: drawEntity
        transform.cartographic: Li.cartographic(toRadians(114.054494), toRadians(22.540745), 500);

        Entity {
            id: boxEntity
            transform.position: Li.vector3(0, 0, -400)

            GeometryRenderer {
                id: renderer
                castShadow: true
                receiveShadow: true
                geometry: BoxGeometry {
                    extent: Li.vector3(100, 200, 300)
                    hasNormal: true
                    hasTexCoord: true
                }
                material: Material {
                    texture: tex
                }
            }
        }

        Entity {
            id: projectionEntity
            transform.rotationX: -90

            TextureProjection {
                id: textureProjection
                projectionType: TextureProjection.Orthographic
                width: 2000
                height: 1000
                texture: tex
                textureFlip: true
            }
        }
    }

    Component.onCompleted: {
        console.log('onCompleted');
    }
}
