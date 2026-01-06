#include <iostream>

int main(int argc, char **argv) {
	std::cout << argc << std::endl;
	if (argv) {
		std::cout << argv[0] << std::endl;
	}
	return 0;
}