#include <cstdlib>	// For system
#include <cctype>	// For tolower
#include <stdexcept>// For runtime_error

#ifdef _WIN32 // Windows MSVC
#include <windows.h>// For _popen, _pclose
#define popen _popen
#define pclose _pclose
#else // Linux, MacOS
#include <stdio.h>	// For popen, pclose
#endif

#include "util.hpp"

using namespace std;

namespace util
{
#ifdef _WIN32 // Windows MSVC
	void clear_console() { system("cls"); }
#else // Linux, MacOS
	void clear_console() { system("clear"); }
#endif

	void to_lower(string& str)
	{
		for (size_t i = 0;i < str.length();i++)
			str[i] = tolower(str[i]);
		while (!str.empty() && string(" \r\n").find_first_of(str[str.length() - 1]) != string::npos)
			str.pop_back();
	}

	string execute_command(const string& cmd)
	{
		FILE* pipe = popen(cmd.c_str(), "r");
		char* buf = static_cast<char*>(malloc(1024));
		string res;

		if (!pipe)
			throw runtime_error("Error: Failed to execute curl command, please make sure curl is installed and added to path");

		if (!buf)
			throw runtime_error("Error: Failed to allocate memory, please make sure your system have enough aviliable RAM");

		while (fgets(buf, 1024, pipe) != nullptr) res += buf;

		pclose(pipe);
		return res;
	}

	string make_http_request(const string& url) {
		// Make http request by executing curl command so I don't have to write sockets and link openssl for https
		return execute_command("curl -s \"" + url + "\"");
	}
}
