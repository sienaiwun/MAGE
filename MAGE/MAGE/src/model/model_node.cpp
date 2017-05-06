//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ModelNode::ModelNode(const string &name, UniquePtr< Model > &&model)
		: SceneNode(name), m_model(std::move(model)) {}

	ModelNode::ModelNode(const ModelNode &model_node)
		: SceneNode(model_node), m_model(model_node.GetModel()->Clone()) {}

	ModelNode::ModelNode(ModelNode &&model_node) = default;

	ModelNode::~ModelNode() = default;

	UniquePtr< Node > ModelNode::CloneImplementation() const {
		return UniquePtr< Node >(new ModelNode(*this));
	}
}