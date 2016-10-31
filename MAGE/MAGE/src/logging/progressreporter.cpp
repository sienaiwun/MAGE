//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ProgressReporter::ProgressReporter(uint32_t nb_work, const string &title, uint32_t bar_length)
		: m_nb_work_total(nb_work), m_nb_work_done(0), m_nb_plusses_printed(0) {
		
		if (bar_length == 0) {
			bar_length = TerminalWidth() - 28;
		}
		
		m_mutex = Mutex::Create();
		
		m_nb_plusses_total = max(2, bar_length - (uint32_t)title.size());
	
		m_timer = new Timer();
		m_timer->Start();
		
		m_fout = stdout;
		
		// Initialize progress string
		const size_t buffer_length = title.size() + m_nb_plusses_total + 64;
		m_buffer = new char[buffer_length];
		// Composes a string with the same text that would be printed 
		// if format was used on printf, but instead of being printed, 
		// the content is stored in the buffer.
		snprintf(m_buffer, buffer_length, "\r%s: [", title.c_str());
		
		// A C string is as long as the number of characters between 
		// the beginning of the string and the terminating null character 
		// (without including the terminating null character itself).
		m_current_pos = m_buffer + strlen(m_buffer);
		char *s = m_current_pos;
		for (uint32_t i = 0; i < m_nb_plusses_total; ++i) {
			*s++ = ' ';
		}
		*s++ = ']';
		*s++ = ' ';
		*s++ = '\0';
		
		if (general_configuration.IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer, m_fout);

		// If the given stream was open for writing
		// (or if it was open for updating and the last 
		// i/o operation was an output operation) 
		// any unwritten data in its output buffer is written 
		// to the output file stream.
		fflush(m_fout);
	}

	ProgressReporter::~ProgressReporter() {
		delete[] m_buffer;
		delete m_timer;
		Mutex::Destroy(m_mutex);
	}

	void ProgressReporter::Update(uint32_t nb_work) {
		if (nb_work == 0 || general_configuration.IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		MutexLock lock(*m_mutex);
		
		m_nb_work_done += nb_work;
		const float percent_done = float(m_nb_work_done) / float(m_nb_work_total);
		uint32_t plusses_needed = (uint32_t)round(percent_done * m_nb_plusses_total);
		if (plusses_needed > m_nb_plusses_total) {
			plusses_needed = m_nb_plusses_total;
		}
		while (m_nb_plusses_printed < plusses_needed) {
			*m_current_pos++ = '+';
			++m_nb_plusses_printed;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer, m_fout);
		// Update elapsed time and estimated time to completion
		const float seconds = (float)m_timer->Time();
		const float estimation_remaining = seconds / percent_done - seconds;
		if (percent_done == 1.0f) {
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs)       ", seconds);
		}
		else {
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs|%.1fs)  ", seconds, max(0.0f, estimation_remaining));
		}

		// If the given stream was open for writing
		// (or if it was open for updating and the last 
		// i/o operation was an output operation) 
		// any unwritten data in its output buffer is written 
		// to the output file stream.
		fflush(m_fout);
	}

	void ProgressReporter::Done() {
		if (general_configuration.IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		MutexLock lock(*m_mutex);
		
		while (m_nb_plusses_printed < m_nb_plusses_total) {
			*m_current_pos++ = '+';
			++m_nb_plusses_printed;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer, m_fout);
		// Update elapsed time
		const float seconds = (float)m_timer->Time();
		// Writes the string format to the output file stream.
		fprintf(m_fout, " (%.1fs)       \n", seconds);
		
		// If the given stream was open for writing
		// (or if it was open for updating and the last 
		// i/o operation was an output operation) 
		// any unwritten data in its output buffer is written 
		// to the output file stream.
		fflush(m_fout);
	}
}