// Precompiled Header File
#pragma once
#include "XEngine/Core/PlatformDetection.h"
#ifdef XPLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif
#include <array>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "XEngine/Core/XCore.h"
#include "XEngine/Debug/Logging.h"
#include "XEngine/Debug/Instrumentor.h"
#ifdef XPLATFORM_WINDOWS
	#include <Windows.h>
#endif

// byjohnmichael
