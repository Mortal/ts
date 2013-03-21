// vim:set ts=4 sts=4 sw=4 noet:
#ifndef BFS_HPP
#define BFS_HPP

#include <map>
#include <deque>
#include <vector>

#include "presentation.hpp"

template <typename state>
void bfs(std::ostream & out) {
	typedef presentation<state> P;

	out << P::header() << std::flush;

	std::deque<std::pair<state, state> > to_visit;
	std::map<state, state> parent;
	to_visit.push_back(std::make_pair(state::initial(), state::initial()));

	while (!to_visit.empty()) {
		std::pair<state, state> s = to_visit.front();
		to_visit.pop_front();
		if (parent.count(s.first)) continue;
		parent.insert(s);
		if (s.first == state::goal()) break;
		std::vector<state> n = s.first.neighbourhood();
		for (size_t i = 0; i < n.size(); ++i) {
			to_visit.push_back(std::make_pair(n[i], s.first));
		}
	}

	if (parent.count(state::goal())) {
		out << P::solution_header() << std::flush;
		std::vector<state> result;
		result.push_back(state::goal());
		state cur = state::goal();
		while (!(cur == state::initial())) {
			cur = parent[cur];
			result.push_back(cur);
		}
		for (size_t i = result.size(); i--;) out << result[i] << '\n';
		out << std::endl;
	} else {
		out << P::no_solution_header() << std::flush;
	}
}

#endif // BFS_HPP
