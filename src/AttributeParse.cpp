#include <string>

//character lists
bool whitelisted_character( char a )
{
	return isalpha( a ) or isdigit( a ) or a == '-' or a == '_';
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
	size_t plainBeg = l.find( '{' );
	size_t plainEnd = l.find( '}' );
	if( ifind >= std::string::npos ) return output;
	bool ignore(true);
	for( auto i = 0u; i < l.length(); ++i )
	{
		if( i > plainBeg and i < plainEnd ) continue;
		if( l[i] == sig )
		{
			ignore = false;
			if( not output.empty() ) output += ' ';
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
	return output;
}

std::string link_attribute( std::string l, char sig )
{
	size_t hfind = l.rfind( sig );
	if( hfind < std::string::npos )
	{
		return l.substr( hfind+1, std::string::npos );
	}
	return std::string();
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
	std::string href = link_attribute( line, '@' );
	if( not href.empty() )
	{
		attribs += " href=\"" + href + '"';
	}

	std::string src = link_attribute( line, '$' );
	if( not src.empty() )
	{
		attribs += " src=\"" + src + '"';
	}

	size_t bfind = line.find( '{' );
	if( bfind < std::string::npos )
	{
		size_t bend = line.find( '}' );
		attribs += ' ' + line.substr( bfind+1, bend-bfind-1 );
	}

	return attribs;
}
