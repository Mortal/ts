// vim:set ts=4 sts=4 sw=4 noet:
#ifndef PRESENTATION_HPP
#define PRESENTATION_HPP

#include <sstream>

template <typename state>
class presentation {
public:
	static std::string header() {
		std::stringstream ss;
		ss << state::name << '\n'
			<< std::string(std::string(state::name).size(), '-') << '\n'
			<< state::description << '\n';
		return ss.str();
	}

	static std::string solution_header() {
		return "Solution:\n";
	}

	static std::string no_solution_header() {
		return "No solution exists.\n";
	}
};

#endif // PRESENTATION_HPP
