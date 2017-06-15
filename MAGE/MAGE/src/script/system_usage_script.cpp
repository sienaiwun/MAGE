//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\system_usage_script.hpp"
#include "system\system_usage.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	const double SystemUsageScript::s_resource_fetch_period = 1.00;

	SystemUsageScript::SystemUsageScript(SharedPtr< SpriteText > text)
		: BehaviorScript(), m_accumulated_time(0.0),
		m_last_cpu_usage(0.0), m_last_ram_usage(0),
		m_monitor(), m_text(text) {}

	SystemUsageScript::SystemUsageScript(SystemUsageScript &&script) = default;
	
	SystemUsageScript::~SystemUsageScript() = default;

	void SystemUsageScript::Update(double delta_time) {
		// CPU + MEM
		m_accumulated_time += delta_time;
		if (m_accumulated_time > SystemUsageScript::s_resource_fetch_period) {
			m_accumulated_time = 0.0;
			
			// CPU
			m_last_cpu_usage = m_monitor->GetCPUDeltaPercentage();

			// MEM
			m_last_ram_usage = static_cast< uint32_t >(GetVirtualMemoryUsage() >> 20);

		}

		wchar_t buffer[32];
		_snwprintf_s(buffer, _countof(buffer), L"CPU: %.1lf%%\nRAM: %uMB", m_last_cpu_usage, m_last_ram_usage);
		
		m_text->SetText(buffer);
	}
}