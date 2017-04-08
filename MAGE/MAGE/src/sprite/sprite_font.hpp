#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "sprite\sprite_font_output.hpp"
#include "sprite\sprite_font_descriptor.hpp"
#include "sprite\sprite_batch.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteFont : public Resource {

	public:

		explicit SpriteFont(ID3D11Device2 *device, const wstring &fname, const SpriteFontDescriptor &desc);
		SpriteFont(SpriteFont &&font) = default;
		virtual ~SpriteFont() = default;

		void DrawString(SpriteBatch &sprite_batch, const wchar_t *text, const SpriteTransform &transform,
			XMVECTOR color = Colors::White, SpriteEffect effects = SpriteEffect_None) const;

		XMVECTOR MeasureString(const wchar_t *text) const;
		RECT MeasureDrawBounds(const wchar_t *text, const XMFLOAT2 &position) const;
		
		float GetLineSpacing() const {
			return m_line_spacing;
		}
		void SetLineSpacing(float spacing) {
			m_line_spacing = spacing;
		}
		wchar_t GetDefaultCharacter() const {
			return m_default_glyph ? static_cast< wchar_t >(m_default_glyph->m_character) : L'0';
		}
		void SetDefaultCharacter(wchar_t character) {
			m_default_glyph = (character) ? GetGlyph(character) : nullptr;
		}
		bool ContainsCharacter(wchar_t character) const;
		const Glyph *GetGlyph(wchar_t character) const;

	private:

		SpriteFont(const SpriteFont &font) = delete;
		SpriteFont &operator=(const SpriteFont &font) = delete;
		SpriteFont &operator=(SpriteFont &&font) = delete;

		HRESULT InitializeSpriteFont(const SpriteFontOutput &output);

		ComPtr< ID3D11ShaderResourceView > m_texture;
		vector < Glyph > m_glyphs;
		const Glyph *m_default_glyph;
		float m_line_spacing;
	};
}