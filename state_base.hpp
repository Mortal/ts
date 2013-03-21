// vim:set ts=4 sts=4 sw=4 noet:
#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

#include <vector>
#include <algorithm>

template <typename child_t>
class state_base {
	typedef state_base<child_t> state;
	const child_t & self() const {
		return *static_cast<const child_t *>(this);
	}

	static bool s_valid(const child_t & s) {
		return s.valid();
	}

public:
	bool operator<(const state & other) const {
		return self().repr() < other.self().repr();
	}

	bool operator==(const state & other) const {
		return self().repr() == other.self().repr();
	}

	std::vector<child_t> neighbourhood() const {
		std::vector<child_t> n = self().unfiltered_neighbourhood();
		std::vector<child_t> res;
		std::copy_if(n.begin(), n.end(), std::back_inserter(res), s_valid);
		return res;
	}
};

#endif // STATE_BASE_HPP
