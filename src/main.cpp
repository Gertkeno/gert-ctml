#include <iostream>
#include <fstream>
#include <Version.h>
#include <FileParse.hpp>
#ifdef __linux__
#include <unistd.h>
#endif

int main( int argc, char ** argv )
{
	ctml::FileParse m( "test.ctml" );
	m.root.write_tree( std::cout );
	std::cout << std::endl;
	m.root.write_to( std::cout );
	std::cout << std::endl;

	return EXIT_SUCCESS;
}

/*
int main( int argc, char **argv )
{
	bool foundFile( false );
	for( ubyte i = 1u; i < argc; i++ )
	{
		if( argv[i][0] != '-' )
		{
			std::ifstream inFile( argv[i] );
			if( not inFile.is_open() )
			{
				std::cerr << "[ERROR] could not open file '" << argv[i] << "' continuing..." << std::endl;
				continue;
			}
			std::string outFile( parse_in_stream( &inFile ) );
			if( useCout )
			{
				std::cout << outFile;
			}
			else
			{
				std::string filename( argv[i] );
				filename = filename.substr( 0, filename.rfind( '.' ) );
				filename += ".html";
				std::cerr << "[INFO] Writing to: " << filename << std::endl;
				std::ofstream output( filename );
				if( output.is_open() )
				{
					output << outFile;
				}
			}
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
		std::cerr << "[INFO] No command line files, parsing from cin" << std::endl;
		#ifdef __linux__
		if( not isatty( fileno( stdin ) ) )
		#else
		if( true )
		#endif
		{
			std::string outFile( parse_in_stream( &std::cin ) );
			std::cout << outFile;
		}
		else
		{
			std::cerr << "[ERROR] No piped data from cin" << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
*/
