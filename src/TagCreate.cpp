#include <TagStacker.h>
#include <istream>

std::string extract_word( std::istream* i )
{
	std::string extract;
	char t;
	bool inbracket(false);
	while( not i->get( t ).eof() )
	{
		if( t == '{' ) inbracket = true;
		else if( t == '}' ) inbracket = false;
		extract += t;
		auto nex = i->peek();
		if( not inbracket and ( nex == ' ' or nex == '\n' or nex == '\t' or nex == ']') ) break;
	}
	return extract;
}

std::string attribute_create( std::string l );

std::string tag_creator( std::istream* i, TagStack* t )
{
	std::string tag;
	std::string name( extract_word( i ) );
	std::string attrib = attribute_create( name.substr( 0, name.length() ) );
	size_t quickSpot = name.find( '.' );
	quickSpot = std::min( name.find( '#' ), quickSpot );
	quickSpot = std::min( name.find( '@' ), quickSpot );
	quickSpot = std::min( name.find( '$' ), quickSpot );
	quickSpot = std::min( name.find( '{' ), quickSpot );
	tag = '<';
	if( quickSpot < std::string::npos )
		name = name.substr( 0, quickSpot );
	tag += name;
	if( not attrib.empty() )
	{
		tag += attrib;
	}

	tag += '>';
	//add end tag to end tag manager
	t->add( name );

	return tag;
}
