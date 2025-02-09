#include "vertex2d.h"

void Vertex2D::serialize(Archive& archive) {
    archive << position;
    archive << texCoord;
    archive << color;
}

void Vertex2D::deserialize(Archive& archive) {
    archive >> position;
    archive >> texCoord;
    archive >> color;
}

VertexBindingInfo Vertex2D::getBindingInfo() {
    VertexBindingInfo bindingInfo{};
    bindingInfo.binding = 0;
    bindingInfo.stride = sizeof(Vertex2D);
    bindingInfo.offset = 0;
    bindingInfo.inputRate = InputRate::INPUT_RATE_VERTEX;

    return bindingInfo;
}

std::vector<VertexAttributeInfo> Vertex2D::getAttributeInfo() {
    std::vector<VertexAttributeInfo> attributeDescriptions(3);

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = AttributeFormat::ATTRIBUTE_FORMAT_FLOAT2;
    attributeDescriptions[0].offset = offsetof(Vertex2D, position);
    attributeDescriptions[0].type = AttributeType::ATTRIBUTE_TYPE_POSITION;

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = AttributeFormat::ATTRIBUTE_FORMAT_FLOAT2;
    attributeDescriptions[1].offset = offsetof(Vertex2D, texCoord);
    attributeDescriptions[1].type = AttributeType::ATTRIBUTE_TYPE_TEXCOORD;

    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = AttributeFormat::ATTRIBUTE_FORMAT_FLOAT3;
    attributeDescriptions[2].offset = offsetof(Vertex2D, color);
    attributeDescriptions[2].type = AttributeType::ATTRIBUTE_TYPE_COLOR;

    return attributeDescriptions;
}