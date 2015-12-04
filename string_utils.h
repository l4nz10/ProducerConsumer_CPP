#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <string>
#include <vector>
#include <algorithm>

namespace string_utils {
  std::string trim(std::string&& str, const std::string& whitespace = " \t\n") {
		const auto strEnd = str.find_last_not_of(whitespace);
		if (strEnd==std::string::npos)
			return {}; // no content
		str.erase(strEnd+1);

		const auto strBegin = str.find_first_not_of(whitespace);
		str.erase(0, strBegin);

		return std::move(str);
	}

	std::vector<std::string> split(std::string const& str, size_t pos = 0) {
		const char* const anySpace = " \t\r\n\v\f";

		std::vector<std::string> ret;
		while (pos != std::string::npos) {
			auto start = str.find_first_not_of(anySpace, pos);
			if (start == std::string::npos) break;

			auto end = str.find_first_of(anySpace, start);
			auto size = end==std::string::npos ? end : end-start;
			ret.emplace_back(str.substr(start, size));

			pos = end;
		}

		return ret;
	}

  bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
  }
}

#endif
