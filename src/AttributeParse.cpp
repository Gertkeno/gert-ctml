#include <string>

std::string attribute_create( std::string line )
{
	std::string attribs;

	//specific attributes
	std::string classes;
	std::string ids;

	//IDS
	size_t ifind = line.find( '#' );
	if( ifind < std::string::npos )
	{
		bool ignore(false);
		for( auto i = ifind+1; i < line.length(); ++i )
		{
			if( line[i] == '#' )
			{
				ignore = false;
				ids += ' ';
				continue;
			}
			else if( line[i] == '@' or line[i] == '$' ) break;
			else if( not isalpha( line[i] ) and not isdigit( line[i] ) )
			{
				ignore = true;
			}
			if( ignore ) continue;
			ids += line[i];
		}
	}

	if( not ids.empty() )
		attribs += " id=\"" + ids + "\"";

	//CLASSES
	size_t cfind = line.find( '.' );
	if( cfind < std::string::npos )
	{
		bool ignore(false);
		for( auto i = cfind+1; i < line.length(); ++i )
		{
			if( line[i] == '.' )
			{
				ignore = false;
				classes += ' ';
				continue;
			}
			else if( line[i] == '@' or line[i] == '$' ) break;
			else if( not isalpha( line[i] ) and not isdigit( line[i] ) )
			{
				ignore = true;
			}
			if( ignore ) continue;
			classes += line[i];
		}
	}

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
