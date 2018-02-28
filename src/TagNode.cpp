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

void TagNode::write_to( std::ostream & o ) const
{
	o << '<' << name << attributes << '>';
	if( not endTag )
		return;
	o << contents;

	for( auto &i : _children )
	{
		i->write_to( o );
	}
	o << "</" << name << ">";
}

void TagNode::write_tree( std::ostream & o ) const
{
	o << name;
	if( _children.empty() )
	{
		o << ',';
		return;
	}

	o << "[\n";
	for( auto & i : _children )
	{
		i->write_tree( o );
	}
	o << "\n]";
}

TagNode * const TagNode::add_child()
{
	const auto f{ new TagNode };
	_children.push_back( f );
	return f;
}
