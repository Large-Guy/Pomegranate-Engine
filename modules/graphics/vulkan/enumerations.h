#ifndef POMEGRANATEENGINE_ENUMERATIONS_H
#define POMEGRANATEENGINE_ENUMERATIONS_H

#include <vulkan/vulkan.h>

enum RenderMode {
    RENDER_MODE_FILL = VK_POLYGON_MODE_FILL,
    RENDER_MODE_WIRE_FRAME = VK_POLYGON_MODE_LINE,
    RENDER_MODE_POINTS = VK_POLYGON_MODE_POINT
};

enum CullMode {
    CULL_MODE_NONE = VK_CULL_MODE_NONE,
    CULL_MODE_FRONT = VK_CULL_MODE_FRONT_BIT,
    CULL_MODE_BACK = VK_CULL_MODE_BACK_BIT,
    CULL_MODE_BOTH = VK_CULL_MODE_FRONT_AND_BACK
};

enum TopologyMode {
    TOPOLOGY_MODE_TRIANGLE_INDEXED = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    TOPOLOGY_MODE_TRIANGLE_STRIP = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
    TOPOLOGY_MODE_TRIANGLE_FAN = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
    TOPOLOGY_MODE_LINE_INDEXED = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
    TOPOLOGY_MODE_LINE_STRIP = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
    TOPOLOGY_MODE_POINT = VK_PRIMITIVE_TOPOLOGY_POINT_LIST
};

enum BufferType {
    BUFFER_TYPE_NONE = 0,
    BUFFER_TYPE_VERTEX = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
    BUFFER_TYPE_INDEX = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
};

struct RenderInfo {
    RenderMode renderMode = RENDER_MODE_FILL;
    CullMode cullMode = CULL_MODE_BACK;
    TopologyMode topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED;
};

#endif //POMEGRANATEENGINE_ENUMERATIONS_H
