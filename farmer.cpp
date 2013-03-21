// vim:set ts=4 sts=4 sw=4 noet:

#include <array>
#include <tuple>

#include "farmer.h"
#include "state_base.hpp"
#include "bfs.hpp"

namespace farmer {
	enum side { LEFT, RIGHT };

	void invert(side & s) {
		if (s == LEFT) s = RIGHT;
		else s = LEFT;
	}

	class state : public state_base<state> {
	public:
		constexpr static const char name[] = "Wolf, cabbage and sheep";
		constexpr static const char description[] =
"A farmer wants to transport his wolf, cabbage and single sheep across a river.\n"
"However, his boat can only hold himself and one of the three items at a time.\n"
"If the sheep is left unguarded with the cabbage, it eats the sheep.\n"
"If the wolf is left unguarded with the sheep, it eats the wolf.\n"
"How can the farmer cross the bridge with no one being eaten?\n";

	private:
		friend class state_base<state>;

		static const size_t ITEMS = 3;
		std::array<side, ITEMS> sides;
		side & wolf;
		side & sheep;
		side & cabbage;
		side farmer;

	public:
		static state initial() {
			state s;
			s.wolf = s.sheep = s.cabbage = s.farmer = LEFT;
			return s;
		}

		static state goal() {
			state s;
			s.wolf = s.sheep = s.cabbage = s.farmer = RIGHT;
			return s;
		}

	private:
		bool valid() const {
			return (farmer == wolf || wolf != sheep)
				&& (farmer == sheep || sheep != cabbage);
		}

		std::vector<state> unfiltered_neighbourhood() const {
			std::vector<state> n;
			{
				state mv = *this;
				invert(mv.farmer);
				n.push_back(mv);
			}
			for (size_t i = 0; i < ITEMS; ++i) {
				if (sides[i] != farmer) continue;
				state mv = *this;
				invert(mv.farmer);
				invert(mv.sides[i]);
				n.push_back(mv);
			}
			return n;
		}

	public:
		friend std::ostream & operator<<(std::ostream & os, const state & s) {
			if (s.wolf == LEFT) os << "wolf ";
			if (s.sheep == LEFT) os << "sheep ";
			if (s.cabbage == LEFT) os << "cabbage ";

			if (s.farmer == LEFT) os << "< ";
			else os << "> ";

			if (s.wolf == RIGHT) os << "wolf ";
			if (s.sheep == RIGHT) os << "sheep ";
			if (s.cabbage == RIGHT) os << "cabbage ";
			return os;
		}

		state()
			: wolf(sides[0])
			, sheep(sides[1])
			, cabbage(sides[2])
		{
		}

		state(const state & other)
			: sides(other.sides)
			, wolf(sides[0])
			, sheep(sides[1])
			, cabbage(sides[2])
			, farmer(other.farmer)
		{
		}

		state & operator=(const state & other) {
			sides = other.sides;
			farmer = other.farmer;
			return *this;
		}

	public:
		std::tuple<const side &, const side &, const side &, const side &>
		repr() const {
			return std::tie(wolf, sheep, cabbage, farmer);
		}
	};

	const char state::name[];
	const char state::description[];

	void solve(std::ostream & os) {
		bfs<state>(os);
	}
}
