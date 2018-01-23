#include <iostream>
#include <vector>
#include <fstream>
#include <TagStacker.h>
#include <Version.h>

std::string tag_creator( std::istream* i, TagStack* t );

std::string parse_in_stream( std::istream* i )
{
	std::string out( "<!-- Made with gert-ctml version#" VERSION " -->\n" );

	char tester;
	i->get( tester );
	TagStack myTags;
	bool commenting(false);

	while( not i->eof() )
	{
		if( commenting )
		{
			if( tester == '*' or tester == '\n' )
			{
				commenting = false;
				if( tester == '*' ) i->get(tester);
				continue;
			}
			//out += tester;
			i->get( tester );
			continue;
		}
		else if( tester == '\\' )
		{
			//skip \ character escape
			i->get(tester);
			out += tester;
			//skip escaped character
			i->get(tester);
			continue;
		}
		if( tester == '[' )
		{
			out += tag_creator( i, &myTags );
			//remove space directly after tag declaration
			if( i->peek() == ' ' )
				i->get(tester);
		}
		else if( tester == ']' )
		{
			i->get( tester );
			if( tester == ')' )
				myTags.remove();
			else
			{
				out += myTags.remove();
				continue;
			}
		}
		else if( tester == '*' )
		{
			commenting = true;
			while( std::isspace( out.back() ) and out.length() > 1 )
				out.pop_back();
		}
		else
		{
			out += tester;
		}
		i->get( tester );
	}
	if( myTags.count() > 0 )
	{
		std::cerr << "[WARNING] missing " << myTags.count() << " end tags" << std::endl;
	}
	return out;
}
