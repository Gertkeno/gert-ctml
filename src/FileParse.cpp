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
		//ATTRIB,
		CONTENT,
		COMMENT,
	}state{n == &root ? CONTENT : NAME};

	while( (state == COMMENT or get != ']') and get != '\0' and not _file.eof() )
	{
		switch( state )
		{
		case COMMENT:
			if( get == '*' or get == '\n' )
				state = CONTENT;
			break;
		case CONTENT:
			if( get == '[' )
				_from_string( n->add_child() );
			else if( get == '*' )
				state = COMMENT;
			else if( get == '\\' )
			{
				get = _file.get();
				n->contents += get;
			}
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
			{
				_attribute_detect( n, get );
				state = CONTENT;
			}
			break;
		}
		get = _file.get();
	}

	if( _file.peek() == ')' )
	{
		n->endTag = false;
		_file.get();
	}
}

void FileParse::_attribute_detect( TagNode * n, char sen )
{
	struct Token
	{
		char a;
		enum: char
		{
			HREF,
			CLASS,
			ID,
			RAW,
			SOURCE,
		} b;
		std::string name;
	};
	static const Token tokens[]{
		{'.',Token::CLASS,"class"},
		{'#',Token::ID,"id"},
		{'$',Token::SOURCE,"src"},
		{'@',Token::HREF,"href"},
		{'{',Token::RAW,"RAW"},
	};
	const Token * select{ nullptr };

	for( auto & i : tokens )
	{
		if( i.a != sen )
			continue;
		select = &i;
		if( n->attributes.count(i.name) > 0 )
			n->attributes[i.name] += ' ';
	}

	if( select == nullptr )
		return;

	char get;
	while( select != nullptr )
	{
		get = _file.get();
		bool append{false};
		switch( select->b )
		{
		case Token::CLASS:
		case Token::ID:
			if( get == select->a )
				n->attributes[select->name] += ' ';
			else if( std::isalnum( get ) or get == '-' )
				append = true;
			else
				select = nullptr;
			break;
		case Token::RAW:
			if( get == '}' )
			{
				select = nullptr;
				get = _file.get();
			}
			else
				append = true;
			break;
		case Token::SOURCE:
		case Token::HREF:
			if( std::isspace( get ) )
				select = nullptr;
			else
				append = true;
			break;
		}

		if(append)
			n->attributes[ select->name ] += get;
	}
	_attribute_detect( n, get );
}
