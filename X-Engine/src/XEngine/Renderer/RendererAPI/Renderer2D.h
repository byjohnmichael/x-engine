// Renderer 2D(Full static class)
#pragma once
#include "XEngine/Renderer/Texture.h"
#include "XEngine/Renderer/CameraSystem/Cameras.h"
namespace XEngine
{
	class Renderer2D
	{
	public:
		// Renderer2D API
		static void Init();
		static void Shutdown();
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();
		// Flat Color
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		// Texture
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		// Rotated Flat Color
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		// Rotated Texture
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		// Stats
		struct Stats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t GetTotalVertexCount()
				{ return QuadCount * 4; }
			uint32_t GetTotalIndexCount()
				{ return QuadCount * 6; }
		};
		static Stats GetStats();
		static void ResetStats();
	private:
		static void FlushAndReset();
	};
}

// byjohnmichael
