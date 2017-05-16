#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned char ubyte;

#define VERSION "0.4.5"

std::string parse_data( char * dat )
{
	std::string fullread = "<!-- Made with gert-ctml version#" VERSION " -->\n";
	std::vector<std::string> tagNest;

	size_t iterator(0u);
	size_t lineNumer(1u);

	while( dat[iterator] != '\0' )
	{
		if( dat[iterator] == '\\' )
		{
			//no magic check
			fullread += dat[++iterator];
			++iterator;
			continue;
		}
		else if( dat[iterator] == '*' )
		{
			fullread.append( "<!--" );
			while( dat[++iterator] != '\n' and dat[iterator] != '*' ) fullread += dat[iterator];
			fullread.append( "-->" );
			if( dat[iterator] == '*' ) ++iterator;
			continue;
		}
		else if( dat[iterator] == '[' )
		{
			//make tag
			std::string name;//tag name
			std::vector<std::string> adds;//attributes
			++iterator;
			while( dat[iterator] != ' ' and dat[iterator] != '\n' and dat[iterator] != ']' )
			{
				if( not isalpha( dat[iterator] ) and not isdigit( dat[iterator] ) )
				{
					//attribute detected
					std::string adtype;
					bool linkCheck = false;
					switch( dat[iterator] )
					{
						case '.': adtype = "class"; break;
						case '#': adtype = "id"; break;
						case '@': adtype = "href"; linkCheck = true; break;
						case '$': adtype = "src"; linkCheck = true; break;
						case '{': break;
						case '[':
							std::cout << "WARNING: " << lineNumer << ": extra [ in tag name \"" << name << "\"\n";
							break;
					}
					std::string name;//attribute name
					if( dat[iterator] == '{' )
					{
						//raw attribute add
						++iterator;
						while( dat[iterator] != '}' ) name += dat[iterator++];
						adds.push_back( " "  + name );
						++iterator;
						continue;
					}
					else if( linkCheck )
					{
						//href getting link
						while( dat[iterator] != ' ' and dat[iterator] != '\n' )
						{
							++iterator;
							name += dat[iterator];
						}
						name.pop_back();
						adds.push_back( " " + adtype + "=\"" + name + "\"" );
						continue;
					}
					//class or ID
					++iterator;
					while( isalpha( dat[iterator] ) or isdigit( dat[iterator] ) )
					{
						name += dat[iterator];
						++iterator;
					}

					if( adtype.empty() )
					{
						std::cout << "WARNING: " << lineNumer << ": unkown attribute notator\n";
						continue;
					}
					if( not name.empty() )
						adds.push_back( " " + adtype + "=\"" + name + "\"" );
					else
						std::cout << "WARNING: " << lineNumer << ": class or ID specified but not set\n";

					continue;
				}
				//out of attribute detector
				name += dat[iterator];
				++iterator;
			}
			//got full tag name + attributes

			tagNest.push_back( name );
			fullread.append( "<" + name  );
			for( size_t i = 0; i < adds.size(); i++ )
			{
				fullread.append( adds[i] );
			}
			fullread.append( ">" );
			if( dat[iterator] == ' ' ) ++iterator;
			continue;//in case two [ on same line
		}

		//append end tag abc-cba style
		if( dat[iterator] == ']' )
		{
			if( dat[iterator+1] == ')' )//no end tag
				++iterator;
			else if( tagNest.size() > 0 )
				fullread.append( "</" + tagNest.back() + ">" );

			if( tagNest.size() > 0 )
				tagNest.pop_back();
			else
				std::cout << "WARNING: " << lineNumer << ": too many ]\n";
		}
		else
		{
			if( dat[iterator] == '\n' ) ++lineNumer;
			fullread += dat[iterator];
		}

		++iterator;
	}

	return fullread;
}

int main( int argc, char** argv )
{
	if( argc <= 1 )
	{
		std::cout << "No input file. -h for help\n";
		return EXIT_FAILURE;
	}

	for( ubyte i = 1u; i < argc; i++ )
	{
		if( argv[i][0] == '-' )
		{
			switch( argv[i][1] )
			{
				case 'v':
					std::cout << "Version#" << VERSION << std::endl;
					break;
				case 'h':
					std::cout << R"at(INPUT FILE FORMAT:
[] is used to make a tag with a space after the tag name. Any characters after will be the contents of the tag, example below:
	[p this will be text] -> <p>this will be text</p>

adding ) to the end of [] tags will remove the end tag, example below:
	[div unclosed div!]) -> <div>unclosed div!

if you want to add any attributes to a tag just enclose the attribute in {} after tag name declaration
	[meta{charset="UTF-8"}]) -> <meta charset="UTF-8">

adding specifically 'class' or 'id' attributes is easier, just append # or . after the tag name declaration
	[div.large large class] -> <div class="large">large class</div>

this works with 'href' by adding @ after tag name declarations, this needs to be at the end as it ends links with a space at a space
	[a.large@http://gert.us go to my website] -> <a class="large" href="http://gert.us">go to my website</a>
like href, 'src' attribute is applied with $

putting a * will comment out the rest of the line or until another *, this doesn't work in tag name declartion
	*[a a comment] -> <!-- [a a comment] -->
	*[a a comment]* [p real text] -> <!--[a a comment]--> <p>real text</p>
	[a*not a comment*] -> ERROR

COMMNAND LINE ARGUMENTS:
-v * displays version
-h * displays this text)at" << std::endl;
			}
			continue;
		}
		//read file
		std::ifstream readFile( argv[i], std::ios::ate );
		if( not readFile.is_open() )
		{
			std::cout << "Couldn't read file " << argv[i] << std::endl;
			continue;
		}
		size_t readLength = readFile.tellg();
		char * readData = new char[ readLength ];
		readFile.seekg( 0, std::ios::beg );
		readFile.get( readData, readLength, '\0' );

		//write file
		std::string oname = argv[i];
		oname = oname.substr( 0, oname.rfind( '.' )+1 );
		oname.append( "html" );
		std::cout << "OUTPUT FILE: " << oname << std::endl;
		std::ofstream outFile( oname );
		if( not outFile.is_open() )
		{
			std::cout << "Could not write file " << oname << std::endl;
			continue;
		}
		std::string outData = parse_data( readData );
		outFile << outData;

		/* std::cout << outData << std::endl; */
		//clean up
		delete[] readData;
	}
	return EXIT_SUCCESS;
}
