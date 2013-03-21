// vim:set ts=4 sts=4 sw=4 noet:
#include <iostream>

#include "state_base.hpp"
#include "presentation.hpp"
#include "bfs.hpp"
#include "civilians_and_killers.h"
#include "farmer.h"

int main() {
	civilians_and_killers::solve(std::cout);
	farmer::solve(std::cout);
	return 0;
}
