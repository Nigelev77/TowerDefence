#pragma once
#define DEBUGGING_MODE
#include "../SingleIncludes/ecs.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
//This might be put in a helper instead of a system
//Also need to find a way to easily render elements that require values from different systems/modules but for now passing the registry is fine
//as only the camera is being rendered.

void RenderImgui(Registry& registry, float dt);
