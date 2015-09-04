//#include <iostream>
//#include <SDL.h>
//
//int main(int, char**) {
//	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//	SDL_Quit();
//	return 0;
//}

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	std::for_each(
		in(std::cin), in(), std::cout << (_1 * 3) << " ");
}