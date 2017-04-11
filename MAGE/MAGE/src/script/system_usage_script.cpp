#pragma once

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

	const double SystemUsageScript::resource_fetch_period = 1.00;

	void SystemUsageScript::Load() {
		m_monitor->Start();
	}

	void SystemUsageScript::Update(double elapsed_time, const Scene &scene) {
		UNUSED(scene);

		// CPU + MEM
		m_time += elapsed_time;
		if (m_time > SystemUsageScript::resource_fetch_period) {
			m_cpu_usage = m_monitor->GetElapsedCPUPercentage();
			m_ram_usage = static_cast< uint32_t >(GetVirtualMemoryUsage() >> 20);
			m_time = 0.0;
		}

		wchar_t buffer[32];
		_snwprintf_s(buffer, _countof(buffer), L"CPU: %.1lf %%\nRAM: %u MB", m_cpu_usage, m_ram_usage);
		const wstring text = buffer;

		m_text->SetText(text);
	}

	void SystemUsageScript::Close() {
		m_monitor.reset();
	}
}