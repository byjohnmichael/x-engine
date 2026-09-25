// X-Engine Core File
#pragma once
#include <memory>
#include "XEngine/Core/PlatformDetection.h"
// Configurations
#ifdef XDEBUG
	#if defined(XPLATFORM_WINDOWS)
		#define XDEBUGBREAK() __debugbreak()
	#elif defined(X_PLATFORM_LINUX)
		#include <signal.h>
		#define XDEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define  XENABLE_ASSERTS
#else
	#define XDEBUGBREAK()
#endif
#ifdef XENABLE_ASSERTS
	#define XASSERT(x, ...) {if(!(x)) {XCLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); XDEBUGBREAK(); } }
	#define XCORE_ASSERT(x, ...)  {if(!(x)) {XCORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); XDEBUGBREAK(); } }
#else
	#define XASSERT(x, ...)
	#define XCORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)
#define XBIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
namespace XEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
		{ return std::make_unique<T>(std::forward<Args>(args)...); }
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
		{ return std::make_shared<T>(std::forward<Args>(args)...); }
}

// byjohnmichael
