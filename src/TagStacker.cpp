#include <TagStacker.h>

TagStack::TagStack()
{
}

TagStack::~TagStack()
{
}

void TagStack::add( std::string name )
{
	_stack.push_back( name );
}

std::string TagStack::remove()
{
	std::string end = "</" + *(_stack.end()-1) + '>';
	_stack.pop_back();
	return end;
}
