#include <FileParse.hpp>
#include <iostream>

using namespace ctml;

FileParse::FileParse( std::string fn ):
fileName{fn}
,_file(fileName)
{
	if( not _file.is_open() )
	{
		std::cerr << "ERROR: couldn't open file " << fileName << std::endl;
		return;
	}
	_from_string( &root );
}

FileParse::~FileParse()
{
}

TagNode * FileParse::_from_string( TagNode * n )
{
	//if more [ blocks found
	//_from_string( n->add_child() );
}
