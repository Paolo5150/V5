#pragma once
#include <iostream>
#include <vector>
#include <V5/Renderer/stb_image.h>

namespace V5Rendering
{
	struct TextureData
	{
		void* Data;
		int Width;
		int Height;
		int Channels;

		void Delete();
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		//TODO: thils will probably move into a potential Asset manager class
		static TextureData LoadData(const std::string& filePath);

	};


	/*class Texture2D : public Texture
	{
	public:
		 uint32_t GetWidth() const override;
		 uint32_t GetHeight() const override;
		 void Bind(uint32_t slot) const override;
		 void SetData(void* data, uint32_t size) override;

		 static std::shared_ptr<Texture2D> Create(uint32_t w, uint32_t h);
		 static std::shared_ptr<Texture2D> Create(std::string filePath);
	};*/
}