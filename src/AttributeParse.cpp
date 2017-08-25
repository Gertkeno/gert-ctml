#include <string>

//character lists
bool whitelisted_character( char a )
{
	return isalpha( a ) or isdigit( a ) or a == '-';
}

bool link_characters( char a )
{
	return a == '@' or a == '$';
}

//word type attributes
std::string word_attribute( std::string l, char sig, bool (*escape)(char) )
{
	std::string output;
	size_t ifind = l.find( sig );
	if( ifind < std::string::npos )
	{
		bool ignore(false);
		for( auto i = ifind+1; i < l.length(); ++i )
		{
			if( l[i] == sig )
			{
				ignore = false;
				output += ' ';
				continue;
			}
			else if( escape( l[i] ) ) break;
			else if( not whitelisted_character( l[i] ) )
			{
				ignore = true;
			}
			if( ignore ) continue;
			output += l[i];
		}
	}
	return output;
}

std::string attribute_create( std::string line )
{
	std::string attribs;

	//specific attributes
	std::string classes;
	std::string ids;

	//IDS
	ids = word_attribute( line, '#', link_characters );

	if( not ids.empty() )
		attribs += " id=\"" + ids + "\"";

	//CLASSES
	classes = word_attribute( line, '.', link_characters );

	if( not classes.empty() )
		attribs += " class=\"" + classes + "\"";

	//HREF/SRC
	size_t hfind = line.find( '@' );
	if( hfind < std::string::npos )
	{
		attribs += " href=\"" + line.substr( hfind+1, std::string::npos ) + '"';
	}

	size_t sfind = line.find( '$' );
	if( sfind < std::string::npos )
	{
		attribs += " src=\"" + line.substr( sfind+1, std::string::npos ) + '"';
	}

	return attribs;
}
