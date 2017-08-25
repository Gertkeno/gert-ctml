#include <iostream>
#include <vector>
#include <fstream>

std::string extract_word( std::istream* i )
{
	std::string extract;
	char t;
	while( not i->get( t ).eof() )
	{
		if( t == ' ' or t == '\n' or t == '\t' ) break;
		extract += t;
	}
	return extract;
}

std::string parse_in_stream( std::istream* i )
{
	std::string out;

	//declare mode based compiling modes.
	enum parseMode_t
	{
		TAG_DECLARATION,
		PLAIN
	} modal(PLAIN);
	char tester;

	while( not i->get( tester ).eof() )
	{
		bool printPlain(false);
		switch( modal )
		{
			case TAG_DECLARATION:
				if( tester == ' ' or tester == '\n' )
				{
					modal = PLAIN;
					out += '>';
					if( tester == '\n' ) out += '\n';
					break;
				}
				printPlain = true;
				break;
			case PLAIN:
				if( tester == '[' )
				{
					out += '<';
					modal = TAG_DECLARATION;
					break;
				}
				printPlain = true;
				break;
		}
		
		if( printPlain )
		{
			out += tester;
		}
	}
	return out;
}
