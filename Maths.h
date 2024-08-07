#pragma once
#include <string.h> 
#include "glm/glm.hpp"

using namespace glm;
using namespace std;

/**
 * Linear interpolation between v1 and v2
 */
float Lerp(float v1, float v2, float t) {
    return (1 - t) * v1 + t * v2;
}

/**
 * Linear interpolation function for angles
 * Ensures that the interpolation direction is always
 * the shortest way
 */
float LerpAngle(float a1, float a2, float t) {
    float x = Lerp(glm::sin(a1), glm::sin(a2), t);
    float y = Lerp(glm::cos(a1), glm::cos(a2), t);
    return atan2(x, y);
}

/**
 * Linear interpolation function for 3D vectors
 */
glm::vec3 LerpVector(glm::vec3 v1, glm::vec3 v2, float t) {
    float x = Lerp(v1.x, v2.x, t);
    float y = Lerp(v1.y, v2.y, t);
    float z = Lerp(v1.z, v2.z, t);
    return(glm::vec3(x, y, z));
}

/**
 * Distance between two 2D points
 */
float Distance(glm::vec2 p1, glm::vec2 p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/**
 * Copy array values to a matrix
 */
glm::mat4 arrayToMatrix(float floatArray[16]) {
    mat4 mat;
    memcpy(&mat, floatArray, sizeof(floatArray));
    return mat;
}

/**
 * Convert a 3D Vector to a translation matrix
 */
glm::mat4 getTranslation(vec3 position) {
    float mat[16] = {
        1, 0, 0, position.x,
        0, 1, 0, position.y,
        0, 0, 1, position.z,
        0, 0, 0, 1
    };
    return arrayToMatrix(mat);
}

/**
 * Get a perspective projection matrix with provided 
 * field of view and clipping plane distances 
 */
glm::mat4 getPerspective(float fov, float near, float far) {
    float mat[16] = {
        1 / tan(fov / 2), 0, 0, 0,
        0, 1 / tan(fov / 2), 0, 0,
        0, 0, -(far + near / far - near), -(2 * far * near / far - near),
        0, 0, 1, 0
    };
    return arrayToMatrix(mat);
}

/**
 * Get a view matrix based on eye position
 * looking at target
 */
mat4 getView(vec3 eye, vec3 target, vec3 up) {
    vec3 zaxis = normalize(eye - target); // The "forward" vector.
    vec3 xaxis = normalize(cross(up, zaxis)); // The "right" vector.
    vec3 yaxis = cross(zaxis, xaxis); // The "up" vector.

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    float viewMatrix[16] = {
        xaxis.x, yaxis.x, zaxis.x, 0,
        xaxis.y, yaxis.y, zaxis.y, 0,
        xaxis.z, yaxis.z, zaxis.z, 0,
        -dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye),  1
    };

    return arrayToMatrix(viewMatrix);
}
