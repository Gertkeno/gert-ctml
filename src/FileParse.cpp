#include <iostream>
#include <vector>
#include <fstream>
#include <TagStacker.h>

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

std::string attribute_create( std::string line )
{
	std::string attribs;
	return attribs;
}

std::string tag_creator( std::istream* i, TagStack* t )
{
	std::string tag;
	std::string name( extract_word( i ) );
	std::string attrib = attribute_create( name );
	size_t quickSpot = name.find( '.' );
	quickSpot = std::min( name.find( '#' ), quickSpot );
	quickSpot = std::min( name.find( '@' ), quickSpot );
	quickSpot = std::min( name.find( '$' ), quickSpot );
	tag = '<';
	char end = name[name.length() - 1];
	if( quickSpot >= std::string::npos )
		name = name.substr( 0, name.length()-1 );
	else
		name = name.substr( 0, quickSpot );
	tag += name;

	tag += '>';
	//appending returns
	if( end == '\n' )
	{
		 tag += '\n';
	}
	//add end tag to end tag manager
	t->add( name );

	return tag;
}

std::string parse_in_stream( std::istream* i )
{
	std::string out;

	char tester;
	TagStack myTags;

	while( not i->get( tester ).eof() )
	{
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
				out += tester;
			}

		}
		else
		{
			out += tester;
		}
	}
	return out;
}
