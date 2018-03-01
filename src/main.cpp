#include <iostream>
#include <fstream>
#include <Version.h>
#include <FileParse.hpp>
#ifdef __linux__
#include <unistd.h>
#endif

int main( int argc, char ** argv )
{
	struct Option
	{
		char name;
		enum bit: char
		{
			STDOUT       = 1 << 0,
			TREE         = 1 << 1 | STDOUT,
			PRINT_VERSION= 1 << 2,
			HELP         = 1 << 3,
		} var;
	} static constexpr o[]{
		{'c',Option::STDOUT},
		{'t',Option::TREE},
		{'v',Option::PRINT_VERSION},
		{'h',Option::HELP},
	};

	int setting{0};
	for( int i = 1; i < argc; ++i )
	{
		if( argv[i][0] != '-' )
			continue;
		for( auto cv = argv[i] + 1; *cv != '\0'; ++cv )
		{
			bool valid{false};
			for( auto & a : o )
			{
				if( *cv == a.name )
				{
					setting |= a.var;
					valid = true;
					break;
				}
			}
			if( not valid )
				std::cerr << "Unknown option '" << *cv << "' try -h\n";
		}
	}

	if( setting & Option::PRINT_VERSION )
		std::cerr << "Version#" VERSION << std::endl;
	if( setting & Option::HELP )
	{
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
-t * outputs a structure tree based on input
-v * displays version
-h * displays this text
PROGRAM USE:
$ gert-ctml [arguments] [FILENAMES SPACE SEPARATED])at" << std::endl;
	}

	for( int i = 1; i < argc; ++i )
	{
		if( argv[i][0] == '-' )
			continue;
		ctml::FileParse m( argv[i] );
		std::ostream * output{nullptr};

		std::ofstream file;
		if( setting & Option::STDOUT )
			output = &std::cout;
		else
		{
			const std::string as{ argv[i] };
			const std::string nfileName{ as.substr( 0, as.rfind( '.' ) ).append(".html") };
			file.open( nfileName );
			output = &file;
		}

		if( setting & Option::TREE )
			m.root.write_tree( *output );
		else
			m.root.write_html( *output );

		*output << '\n';
	}

	return EXIT_SUCCESS;
}
