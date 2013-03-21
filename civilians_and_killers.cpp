// vim:set ts=4 sts=4 sw=4 noet:

#include "civilians_and_killers.h"
#include "state_base.hpp"
#include "bfs.hpp"

#include <tuple>

namespace civilians_and_killers {
	enum side { LEFT, RIGHT };

	class state : public state_base<state> {
	public:
		constexpr static const char name[] = "Civilians and killers";
		constexpr static const char description[] =
"Three civilians and three killers must cross a river with a boat that\n"
"can carry at most two people at a time.\n"
"Whenever there are more killers than civilians on any side of the river,\n"
"they kill the civilians.\n"
"How can the group all get across the river without anyone getting hurt?\n";

	private:
		friend class state_base<state>;

		// Number of civilians on the other side of the river.
		size_t civilians;
		// Number of killers on the other side of the river.
		size_t killers;
		// Which side of the river the boat is docked on.
		side boat;

	public:
		// Initially, the boat is on the left side, and no one has crossed.
		static state initial() {
			state s;
			s.civilians = s.killers = 0;
			s.boat = LEFT;
			return s;
		}

		// The goal is to have the boat on the right side, and everyone across.
		static state goal() {
			state s;
			s.civilians = s.killers = 3;
			s.boat = RIGHT;
			return s;
		}

	private:
		bool valid() const {
			return civilians <= 3
				&& killers <= 3
				&& (civilians == 0 || killers <= civilians)
				&& (3-civilians == 0 || 3-killers <= 3-civilians);
		}

		std::vector<state> unfiltered_neighbourhood() const {
			std::vector<state> n;
			int movement = (boat == LEFT) ? 1 : -1;
			n.push_back(move_boat().add_civilians(movement));
			n.push_back(move_boat().add_civilians(2*movement));
			n.push_back(move_boat().add_civilians(movement).add_killers(movement));
			n.push_back(move_boat().add_killers(2*movement));
			n.push_back(move_boat().add_killers(movement));
			return n;
		}

	public:
		friend std::ostream & operator<<(std::ostream & os, state & s) {
			return os << (3-s.civilians) << "+" << (3-s.killers)
				<< ((s.boat == LEFT) ? " < " : " > ")
				<< s.civilians << "+" << s.killers << "";
		}

	private:
		std::tuple<const size_t &, const size_t &, const side &> repr() const {
			return std::tie(civilians, killers, boat);
		}

		state add_civilians(int count) const {
			state s(*this);
			s.civilians += count;
			return s;
		}

		state add_killers(int count) const {
			state s(*this);
			s.killers += count;
			return s;
		}

		state move_boat() const {
			state s(*this);
			s.boat = (boat == LEFT) ? RIGHT : LEFT;
			return s;
		}
	};

	const char state::name[];
	const char state::description[];

	void solve(std::ostream & os) {
		bfs<state>(os);
	}
}
