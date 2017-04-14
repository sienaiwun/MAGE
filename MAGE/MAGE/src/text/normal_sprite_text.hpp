#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class NormalSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit NormalSpriteText(const string &name, SharedPtr< SpriteFont > font,
			SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, font, effects) {}
		NormalSpriteText(const NormalSpriteText &sprite_text) = default;
		NormalSpriteText(NormalSpriteText &&sprite_text) = default;
		virtual ~NormalSpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		NormalSpriteText &operator=(const NormalSpriteText &sprite_text) = default;
		NormalSpriteText &operator=(NormalSpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual NormalSpriteText *Clone() const override {
			return new NormalSpriteText(*this);
		}

		virtual void Draw(SpriteBatch &sprite_batch) const override;
	};
}