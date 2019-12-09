#pragma once

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <memory>
#include <string_view>
#include "Memory/FMemory.h"
#include "Math/Vectors.h"
#include "Overlay/FOverlay.h"



// overlay stuff
// need to include those libs else we will get errors.
#include <dwmapi.h> 
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "Dwrite")

#pragma comment(lib, "Dwmapi.lib") 
#pragma comment(lib, "d2d1.lib")



