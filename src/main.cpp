#include <utility>
#include <core/core.h>
#include <ecs/ecs.h>
#include <events/events.h>
#include <ecs/extensions/common/common.h>
#include <ecs/extensions/rendering/rendering.h>
#include <graphics/opengl/graphics.h>
#include <input/input.h>
#include <math/geometry/geometry.h>
#include "lua/lua_state.h"
#include "lua/debug.h"
#include "lua/events.h"
#include "lua/ecs.h"

int main() {
    Debug::Log::info("Hello World!");
    return 0;
}