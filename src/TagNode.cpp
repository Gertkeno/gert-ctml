#include <TagNode.hpp>

using namespace ctml;

TagNode::TagNode():
endTag{ true }
{
}

TagNode::~TagNode()
{
	for( auto & i : _children )
	{
		delete i;
	}
}

void TagNode::write_to( std::ostream & o, int a ) const
{
	const bool t{ not name.empty() };
	if( t )
	{
		o << '<' << name;
		for( auto & i : attributes )
		{
			o << ' ';
			if( i.first == "RAW" )
			{
				o << i.second;
				continue;
			}
			o << i.first << "=\"" << i.second << '"';
		}
		o << '>';
	}

	if( not endTag )
		return;
	o << contents;

	for( auto &i : _children )
	{
		i->write_to( o );
	}
	if( t )
		o << "</" << name << ">";
}

void TagNode::write_tree( std::ostream & o, int a ) const
{
	o << ( name.empty() ? "~" : name );
	if( _children.empty() )
	{
		o << ',';
		return;
	}

	o << "[\n" << std::string( a+1, ' ' );
	for( auto & i : _children )
	{
		i->write_tree( o, a+1 );
	}
	o << '\n' << std::string( a, ' ' ) << ']';
}

TagNode * const TagNode::add_child()
{
	const auto f{ new TagNode };
	_children.push_back( f );
	return f;
}
