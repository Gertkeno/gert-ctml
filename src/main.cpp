#include <iostream>
#include <fstream>
#include <FileParse.h>

typedef unsigned char ubyte;

#define VERSION "1.0.0"
bool useCout;

int main( int argc, char **argv )
{
	bool useCout( false );
	bool foundFile( false );
	for( ubyte i = 1u; i < argc; i++ )
	{
		if( argv[i][0] != '-' )
		{
			std::ifstream inFile( argv[i] );
			if( not inFile.is_open() )
			{
				std::cerr << "ERROR: could not open file '" << argv[i] << "' continuing..." << std::endl;
				continue;
			}
			std::string outFile( parse_in_stream( &inFile ) );
			std::cout << outFile;
			foundFile = true;
			continue;
		}
		switch( argv[i][1] )
		{
			case 'v':
				std::cerr << "Version#" << VERSION << std::endl;
				break;
			case 'c':
				useCout = true;
				break;
			case 'h':
				std::cerr << R"at(INPUT FILE FORMAT:
[] is used to make a tag with a space after the tag name. Any characters after will be the contents of the tag, example below:
   [p this will be text]              <p>this will be text</p>

Adding ) to the end of [] tags will remove the end tag, example below:
   [div unclosed div!])               <div>unclosed div!

If you want to add any attributes to a tag just enclose the attribute in {} after tag name declaration
   [meta{charset="UTF-8"}])           <meta charset="UTF-8">

Adding specifically 'class' or 'id' attributes is easier, just append # or . after the tag name declaration
   [div.large large class]            <div class="large">large class</div>

You can concatenate several id or class attributes of the same type easily
   [div.large.btn.blue large blue]    <div class="large btn blue">large blue</div>
   [h1#main#banner.btn banner h1]     <h1 id="main banner" class="btn">banner h1</h1>

The attribute 'href' is added with @ after tag name declarations, this needs to be at the end as it ends links at a space
   [a.large@http://gert.us website]   <a class="large" href="http://gert.us">website</a>
like href, 'src' attribute is applied with $
   [img$http://image.png ])           <img src="http://image.png">

Here is a list of the quick attribute notations
	.	class
	#	id
	@	href
	$	src

Putting a * will comment out the rest of the line or until another *, this doesn't work in tag name declaration
   *[a a comment]  [p real text]      <!--[a a comment]  [p real text]-->
   *[a a comment]* [p real text]      <!--[a a comment]--> <p>real text</p>
   [a*not a comment*]                 ERROR

COMMAND LINE ARGUMENTS:
-c * outputs to command line instead of automatically determined file
-v * displays version
-h * displays this text
PROGRAM USE:
$ gert-ctml [arguments] [FILENAMES SPACE SEPARATED])at" << std::endl;
			break;
		}
	}//for( args )
	if( not foundFile )
	{
		std::string outFile( parse_in_stream( &std::cin ) );
		std::cout << outFile;
	}

	return EXIT_SUCCESS;
}
