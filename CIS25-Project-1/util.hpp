#pragma once

namespace util
{
	// Clear console window
	void clear_console();

	// Convert a string to lowercase
	void to_lower(std::string& str);

	// Execute external command
	std::string execute_command(const std::string& cmd);

	// Make HTTP request
	std::string make_http_request(const std::string& url);
}
