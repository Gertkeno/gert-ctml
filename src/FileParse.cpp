#include <iostream>
#include <vector>
#include <fstream>

std::string extract_word( std::istream* i )
{
	std::string extract;
	char t;
	while( not i->get( t ).eof() )
	{
		extract += t;
		if( t == ' ' or t == '\n' or t == '\t' ) break;
	}
	return extract;
}

std::string tag_creator( std::istream* i )
{
	std::string tag;
	std::string name( extract_word( i ) );
	tag = '<' + name.substr( 0, name.length()-1 ) + '>';
	if( name[name.length() - 1] != ' ' )
	{
		 tag += name[name.length()-1];
	}
	return tag;
}

std::string parse_in_stream( std::istream* i )
{
	std::string out;

	char tester;

	while( not i->get( tester ).eof() )
	{
		if( tester == '[' )
		{
			out += tag_creator( i );
		}
		else
		{
			out += tester;
		}
	}
	return out;
}
