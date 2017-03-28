#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	void Scene::ForEachScript(ActionT action) const {
		for (set< SharedPtr< BehaviorScript > >::const_iterator it = m_scripts.cbegin(); it != m_scripts.cend(); ++it) {
			action(**it);
		}
	}
}