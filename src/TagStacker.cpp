#include <TagStacker.h>
#include <iostream>

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
	if( _stack.size() <= 0 )
	{
		std::cerr << "ERROR: Too many end tags" << std::endl;
		return std::string();
	}
	std::string end = "</" + *(_stack.end()-1) + '>';
	_stack.pop_back();
	return end;
}
