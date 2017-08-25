#ifndef TAG_STACKER_H
#define TAG_STACKER_H
#include <vector>
#include <string>

class TagStack
{
	public:
		TagStack();
		~TagStack();
		void add( std::string name );
		std::string remove( void );
	private:
		std::vector<std::string> _stack;
};

#endif //TAG_STACKER_H
