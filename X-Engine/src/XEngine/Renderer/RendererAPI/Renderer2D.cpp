// Source file for Renderer2D Includes startup and shutdown as well as draw calls
#include "Xpch.h"
#include "XEngine/Renderer/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/Renderer/VertexArray.h"
#include "XEngine/Renderer/RendererAPI/Renderer2D.h"
#include "XEngine/Renderer/RendererAPI/RenderCommand.h"
namespace XEngine
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TillingFactor;
	};
	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;
		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;
		glm::vec4 QuadVertexPositions[4] = {glm::vec4(1.0f), glm::vec4(1.0f), glm::vec4(1.0f), glm::vec4(1.0f)};
		Renderer2D::Stats RendererStats;
	}; 
	static Renderer2DData m_RendererData;
	void Renderer2D::Init()
	{
		XPROFILE_FUNCTION();
		m_RendererData.VertexArray = VertexArray::Create();
		m_RendererData.VertexBuffer = VertexBuffer::Create(m_RendererData.MaxVertices * sizeof(QuadVertex));
		m_RendererData.VertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float, "a_TexIndex"},
			{ ShaderDataType::Float, "a_TillingFactor"}
		});
		m_RendererData.VertexArray->AddVertexBuffer(m_RendererData.VertexBuffer);
		m_RendererData.QuadVertexBufferBase = new QuadVertex[m_RendererData.MaxVertices];
		uint32_t* quadIndices = new uint32_t[m_RendererData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < m_RendererData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, m_RendererData.MaxIndices);
		m_RendererData.VertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		// Textures
		m_RendererData.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		m_RendererData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		int32_t samplers[m_RendererData.MaxTextureSlots];
		for (uint32_t i = 0; i < m_RendererData.MaxTextureSlots; i++)
			samplers[i] = i;
		m_RendererData.TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		m_RendererData.TextureShader->Bind();
		m_RendererData.TextureShader->SetIntArray("u_Textures", samplers, m_RendererData.MaxTextureSlots);
		// Setting all texture slots to zero
		m_RendererData.TextureSlots[0] = m_RendererData.WhiteTexture;
		m_RendererData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_RendererData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		m_RendererData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		m_RendererData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}
	void Renderer2D::Shutdown() 
	{
		XPROFILE_FUNCTION();
		delete[] m_RendererData.QuadVertexBufferBase;
	}
	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		XPROFILE_FUNCTION();
		glm::mat4 viewProjection = camera.GetProjection() * glm::inverse(transform);
		m_RendererData.TextureShader->Bind();
		m_RendererData.TextureShader->SetMat4("u_ViewProjection", viewProjection);
		m_RendererData.QuadIndexCount = 0;
		m_RendererData.QuadVertexBufferPtr = m_RendererData.QuadVertexBufferBase;
		m_RendererData.TextureSlotIndex = 1;	
	}
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		XPROFILE_FUNCTION();
		m_RendererData.TextureShader->Bind();
		m_RendererData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		m_RendererData.QuadIndexCount = 0;
		m_RendererData.QuadVertexBufferPtr = m_RendererData.QuadVertexBufferBase;
		m_RendererData.TextureSlotIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		XPROFILE_FUNCTION();
		uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData.QuadVertexBufferPtr - (uint8_t*)m_RendererData.QuadVertexBufferBase);
		m_RendererData.VertexBuffer->SetData(m_RendererData.QuadVertexBufferBase, dataSize);
		Flush();
	}
	void Renderer2D::Flush()
	{
		if (m_RendererData.QuadIndexCount == 0)
			return;
		for (uint32_t i = 0; i < m_RendererData.TextureSlotIndex; i++)
			m_RendererData.TextureSlots[i]->Bind(i);
		RenderCommand::DrawIndexed(m_RendererData.VertexArray, m_RendererData.QuadIndexCount);
		m_RendererData.RendererStats.DrawCalls++;
	}
	void Renderer2D::FlushAndReset()
	{
		EndScene();
		m_RendererData.QuadIndexCount = 0;
		m_RendererData.QuadVertexBufferPtr = m_RendererData.QuadVertexBufferBase;
		m_RendererData.TextureSlotIndex = 1;
	}
	// Draw Calls
	// Draw Quad (x, y) (Color)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{ DrawQuad({position.x, position.y, 0.0}, size, color); }
	// Draw Quad (x, y, z) (Color)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, color);
	}
	// Draw Quad (mat4) (Color)
	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		constexpr size_t quadVertexCount = 4;
		const float defualtWhiteTextureIndex = 0.0f;
		constexpr glm::vec2 textureCoords[] =
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
		const float tilingFactor = 1.0f;
		if (m_RendererData.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			m_RendererData.QuadVertexBufferPtr->Position = transform * m_RendererData.QuadVertexPositions[i];
			m_RendererData.QuadVertexBufferPtr->Color = color;
			m_RendererData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			m_RendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
			m_RendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
			m_RendererData.QuadVertexBufferPtr++;
		}
		m_RendererData.QuadIndexCount += 6;
		m_RendererData.RendererStats.QuadCount++;
	}
	// Draw Quad (x, y) (Texture)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tillingFactor, const glm::vec4& tintColor)
		{ DrawQuad({ position.x, position.y, 0.0 }, size, texture, tillingFactor, tintColor); }
	// Draw Quad (x, y, z) (Texture)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tillingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture, tillingFactor, tintColor);
	}
	// Draw Quad (mat4) (Texture)
	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, float tillingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] =
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
		if (m_RendererData.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();
		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < m_RendererData.TextureSlotIndex; i++)
		{
			if (*m_RendererData.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			if (m_RendererData.QuadIndexCount >= Renderer2DData::MaxIndices)
				FlushAndReset();
			textureIndex = (float)m_RendererData.TextureSlotIndex;
			m_RendererData.TextureSlots[m_RendererData.TextureSlotIndex] = texture;
			m_RendererData.TextureSlotIndex++;
		}
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			m_RendererData.QuadVertexBufferPtr->Position = transform * m_RendererData.QuadVertexPositions[i];
			m_RendererData.QuadVertexBufferPtr->Color = tintColor;
			m_RendererData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			m_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
			m_RendererData.QuadVertexBufferPtr->TillingFactor = tillingFactor;
			m_RendererData.QuadVertexBufferPtr++;
		}
		m_RendererData.QuadIndexCount += 6;
		m_RendererData.RendererStats.QuadCount++;
	}
	// Draw Rotated Quad (x, y) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{ DrawRotatedQuad({position.x, position.y, 0.0}, size, rotation, color); }
	// Draw Rotated Quad (x, y, z) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, color);
	}
	// Draw Rotated Quad (x, y) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
		{ DrawRotatedQuad({ position.x, position.y, 0.0 }, size, rotation, texture, tilingFactor, tintColor); }
	// Draw Rotated Quad (x, y, z) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture, tilingFactor, tintColor);
	}
	Renderer2D::Stats Renderer2D::GetStats()
		{ return m_RendererData.RendererStats; }
	void Renderer2D::ResetStats()
		{ memset(&m_RendererData.RendererStats, 0, sizeof(Stats)); }
}

// byjohnmichael
