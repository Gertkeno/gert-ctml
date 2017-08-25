#include <iostream>
#include <vector>
#include <fstream>
#include <TagStacker.h>

std::string tag_creator( std::istream* i, TagStack* t );

std::string parse_in_stream( std::istream* i )
{
	std::string out;

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
				out += "-->";
				continue;
			}
			out += tester;
			i->get( tester );
			continue;
		}
		if( tester == '[' )
		{
			out += tag_creator( i, &myTags );
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
			out += "<!--";
		}
		else
		{
			out += tester;
		}
		i->get( tester );
	}
	if( myTags.count() > 0 )
	{
		std::cerr << "WARNING: missing " << myTags.count() << " end tags" << std::endl;
	}
	return out;
}
