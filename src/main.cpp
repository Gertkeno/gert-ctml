#include <iostream>
#include <FileParse.h>

typedef unsigned char ubyte;

#define VERSION "1.0.0"
bool strip;

int main( int argc, char **argv )
{
	for( ubyte i = 1u; i < argc; i++ )
	{
		if( argv[i][0] != '-' )
		{
			std::string outFile( parse_in_stream( &std::cin ) );
			std::cout << outFile;
			continue;
		}
		switch( argv[i][1] )
		{
			case 'v':
				std::cerr << "Version#" << VERSION << std::endl;
				break;
			case 'c':
				//useCout = true;
				break;
			/*case 's':
				if( not strip )
					std::cerr << "STRIPPING ENABLED\n";
				else
					std::cerr << "STRIPPING DISABLED\n";
				strip = not strip;
				break;*/
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
-s * toggles removing comments, off by default
-v * displays version
-h * displays this text
PROGRAM USE:
$ gert-ctml [arguments] FILENAMES SPACE SEPARATED)at" << std::endl;
			break;
		}
	}

	return EXIT_SUCCESS;
}
