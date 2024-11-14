#ifndef POMEGRANATEENGINE_ENUMERATIONS_H
#define POMEGRANATEENGINE_ENUMERATIONS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum RenderMode {
    RENDER_MODE_FILL = GL_FILL,
    RENDER_MODE_WIRE_FRAME = GL_LINE,
    RENDER_MODE_POINTS = GL_POINT
};

enum CullMode {
    CULL_MODE_NONE = GL_NONE,
    CULL_MODE_FRONT = GL_FRONT,
    CULL_MODE_BACK = GL_BACK,
    CULL_MODE_BOTH = GL_FRONT_AND_BACK
};

enum TopologyMode {
    TOPOLOGY_MODE_TRIANGLE_INDEXED = GL_TRIANGLES,
    TOPOLOGY_MODE_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TOPOLOGY_MODE_TRIANGLE_FAN = GL_TRIANGLE_FAN,
    TOPOLOGY_MODE_LINE_INDEXED = GL_LINES,
    TOPOLOGY_MODE_LINE_STRIP = GL_LINE_STRIP,
    TOPOLOGY_MODE_POINT = GL_POINTS
};

enum BufferType {
    BUFFER_TYPE_NONE = 0,
    BUFFER_TYPE_VERTEX = GL_ARRAY_BUFFER,
    BUFFER_TYPE_INDEX = GL_ELEMENT_ARRAY_BUFFER
};

enum InputRate {
    INPUT_RATE_VERTEX = GL_VERTEX_ATTRIB_ARRAY_POINTER,
    INPUT_RATE_INSTANCE = GL_VERTEX_ATTRIB_ARRAY_DIVISOR
};

struct RenderInfo {
    RenderMode renderMode = RENDER_MODE_FILL;
    CullMode cullMode = CULL_MODE_BACK;
    TopologyMode topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED;
};

enum AttributeFormat {
    ATTRIBUTE_TYPE_FLOAT,
    ATTRIBUTE_TYPE_FLOAT2,
    ATTRIBUTE_TYPE_FLOAT3,
    ATTRIBUTE_TYPE_FLOAT4,
    ATTRIBUTE_TYPE_INT,
    ATTRIBUTE_TYPE_INT2,
    ATTRIBUTE_TYPE_INT3,
    ATTRIBUTE_TYPE_INT4,
    ATTRIBUTE_TYPE_UNSIGNED_INT,
    ATTRIBUTE_TYPE_UNSIGNED_INT2,
    ATTRIBUTE_TYPE_UNSIGNED_INT3,
    ATTRIBUTE_TYPE_UNSIGNED_INT4
};

struct VertexBindingInfo {
    uint32_t binding;
    uint32_t stride;
    uint32_t offset;
    InputRate inputRate;
};

struct VertexAttributeInfo {
    uint32_t binding;
    uint32_t location;
    size_t offset;
    AttributeFormat type;
};

#endif //POMEGRANATEENGINE_ENUMERATIONS_H
