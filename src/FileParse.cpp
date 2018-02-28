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
	root.name = "html";
	_from_string( &root );
}

FileParse::~FileParse()
{
}

void FileParse::_from_string( TagNode * n )
{
	char get( _file.get() );
	enum : char
	{
		NAME,
		ATTRIB,
		CONTENT,
	}state{n == &root ? CONTENT : NAME};

	while( get != ']' and get != '\0' and not _file.eof() )
	{
		switch( state )
		{
		case CONTENT:
			if( get == '[' )
				_from_string( n->add_child() );
			else if( get != '\n' and get != '\t' )
				n->contents += get;
			break;
		case NAME:
			if( std::isalnum( get ) )
				n->name += get;
			else if( get == '[' )
				std::cerr << fileName << ": Warning [ found in name declaration\n";
			else if( std::isspace( get ) )
				state = CONTENT;
			else
				state = ATTRIB;
			break;
		case ATTRIB:
			if( std::isspace( get ) )
				state = CONTENT;
			break;
		}
		get = _file.get();
	}
}
