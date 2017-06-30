#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "shader\compiled_shader.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Lighting
	//-------------------------------------------------------------------------

	/**
	 A struct of lighting buffers.
	 */
	struct Lighting final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a lighting buffer.
		 */
		Lighting()
			: m_light_data(nullptr), 
			m_omni_lights(nullptr), 
			m_spot_lights(nullptr) {}

		/**
		 Constructs a lighting buffer from the given lighting buffer.

		 @param[in]		buffer
						A reference to the lighting buffer to copy.
		 */
		Lighting(const Lighting &buffer) = default;

		/**
		 Constructs a lighting buffer by moving the given lighting buffer.

		 @param[in]		buffer
						A reference to the lighting buffer to move.
		 */
		Lighting(Lighting &&buffer) = default;

		/**
		 Destructs this lighting buffer.
		 */
		~Lighting() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given lighting buffer to this lighting buffer.

		 @param[in]		buffer
						A reference to the lighting buffer to copy.
		 @return		A reference to the copy of the given lighting buffer
						(i.e. this lighting buffer).
		 */
		Lighting &operator=(const Lighting &buffer) = default;

		/**
		 Moves the given lighting buffer to this lighting buffer.

		 @param[in]		buffer
						A reference to the lighting buffer to move.
		 @return		A reference to the moved lighting buffer
						(i.e. this lighting buffer).
		 */
		Lighting &operator=(Lighting &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the light data buffer of this lighting buffer.
		 */
		ID3D11Buffer *m_light_data;

		/**
		 A pointer to the shader resource view for omni lights 
		 of this lighting buffer.
		 */
		ID3D11ShaderResourceView *m_omni_lights;

		/**
		 A pointer to the shader resource view for spotlights
		 of this lighting buffer.
		 */
		ID3D11ShaderResourceView *m_spot_lights;
	};

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of vertex shaders.
	 */
	class VertexShader : public Resource< VertexShader > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex shader.

		 @pre			The current engine must be loaded.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(const wstring &fname,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);

		/**
		 Constructs a vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		
		/**
		 Constructs a vertex shader.

		 @pre			The current engine must be loaded.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(const wstring &guid,
			const CompiledVertexShader &compiled_vertex_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);

		/**
		 Constructs a vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit VertexShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledVertexShader &compiled_vertex_shader, 
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		
		/**
		 Constructs a vertex shader from the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 */
		VertexShader(const VertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a vertex shader by moving the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to move.
		 */
		VertexShader(VertexShader &&vertex_shader);
		
		/**
		 Destructs this vertex shader.
		 */
		virtual ~VertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the copy of the given vertex shader
						(i.e. this vertex shader).
		 */
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;

		/**
		 Moves the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the moved vertex shader
						(i.e. this vertex shader).
		 */
		VertexShader &operator=(VertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const;

	protected:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this vertex shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this vertex shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this vertex shader.
		 */
		ComPtr< ID3D11VertexShader > m_vertex_shader;

		/**
		 A pointer to the input layout of this vertex shader.
		 */
		ComPtr< ID3D11InputLayout >  m_vertex_layout;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this vertex shader.

		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to setup this vertex shader.
		 */
		void SetupShader(const CompiledVertexShader &compiled_vertex_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
	};

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of pixel shaders.
	 */
	class PixelShader : public Resource< PixelShader > {

	public:
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &fname);

		/**
		 Constructs a pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);

		/**
		 Constructs a pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &guid, 
			const CompiledPixelShader &compiled_pixel_shader);

		/**
		 Constructs a pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledPixelShader &compiled_pixel_shader);
		
		/**
		 Constructs a pixel shader from the given pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to copy.
		 */
		PixelShader(const PixelShader &pixel_shader) = delete;

		/**
		 Constructs a pixel shader by moving the given pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to move.
		 */
		PixelShader(PixelShader &&pixel_shader);

		/**
		 Destructs this pixel shader.
		 */
		virtual ~PixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given pixel shader to this pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to copy.
		 @return		A reference to the copy of the given pixel shader
						(i.e. this pixel shader).
		 */
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;

		/**
		 Moves the given pixel shader to this pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to move.
		 @return		A reference to the moved pixel shader
						(i.e. this pixel shader).
		 */
		PixelShader &operator=(PixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this pixel shader for shading.

		 @pre			@a texture is not equal to @c nullptr.
		 @param[in]		texture
						A pointer to the texture shader resource view.
		 */
		virtual void PrepareShading(ID3D11ShaderResourceView *texture) const;

		/**
		 Prepares this pixel shader for shading.

		 @param[in]		material
						A reference to the material.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		virtual void PrepareShading(const Material &material, const Lighting &lighting) const;

	protected:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this pixel shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this pixel shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the pixel shader of this pixel shader.
		 */
		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to setup this pixel shader.
		 */
		void SetupShader(const CompiledPixelShader &compiled_pixel_shader);
	};

	//-------------------------------------------------------------------------
	// CombinedShader
	//-------------------------------------------------------------------------

	/**
	 A struct of combined (vertex and pixel) shaders.
	 */
	struct CombinedShader final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a combined shader.

		 @pre			@c vertex_shader.get() is not equal to @c nullptr.
		 @pre			@c pixel_shader.get() is not equal to @c nullptr.
		 @param[in]		vertex_shader
						A pointer to the vertex shader.
		 @param[in]		pixel_shader
						A pointer to the pixel shader.
		 */
		explicit CombinedShader(
			SharedPtr< VertexShader > vertex_shader,
			SharedPtr< PixelShader > pixel_shader);
		
		/**
		 Constructs a combined shader from the given combined shader.

		 @param[in]		shader
						A reference to the combined shader to copy.
		 */
		CombinedShader(const CombinedShader &shader) = default;
		
		/**
		 Constructs a combined shader by moving the given combined shader.

		 @param[in]		shader
						A reference to the combined shader to move.
		 */
		CombinedShader(CombinedShader &&shader) = default;

		/**
		 Destructs this combined shader.
		 */
		~CombinedShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given combined shader to this combined shader.

		 @param[in]		shader
						A reference to the combined shader to copy.
		 @return		A reference to the copy of the given combined shader
						(i.e. this combined shader).
		 */
		CombinedShader &operator=(const CombinedShader &shader) = default;
		
		/**
		 Moves the given combined shader to this combined shader.

		 @param[in]		shader
						A reference to the combined shader to move.
		 @return		A reference to the moved combined shader
						(i.e. this combined shader).
		 */
		CombinedShader &operator=(CombinedShader &&shader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this combined shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @pre			@a texture is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		texture
						A pointer to the texture shader resource view.
		 */
		void PrepareShading(ID3D11Buffer *transform, 
			ID3D11ShaderResourceView *texture) const {

			m_vertex_shader->PrepareShading(transform);
			m_pixel_shader->PrepareShading(texture);
		}
		
		/**
		 Prepares this combined shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		material
						A reference to the material.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		void PrepareShading(ID3D11Buffer *transform, 
			const Material &material, const Lighting &lighting) const {

			m_vertex_shader->PrepareShading(transform);
			m_pixel_shader->PrepareShading(material, lighting);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the vertex shader of this combined shader.
		 */
		SharedPtr< VertexShader > m_vertex_shader;

		/**
		 A pointer to the pixel shader of this combined shader.
		 */
		SharedPtr< PixelShader > m_pixel_shader;
	};
}