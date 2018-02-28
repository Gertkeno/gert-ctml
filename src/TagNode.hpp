#ifndef TAG_NODE_H
#define TAG_NODE_H

#include <vector>
#include <string>
#include <ostream>
#include <map>

namespace ctml
{
	class TagNode
	{
		public:
			TagNode();
			~TagNode();

			std::string contents, name;
			std::map<std::string, std::string> attributes;
			void write_to( std::ostream &, int = 0 ) const;
			void write_tree( std::ostream &, int = 0 ) const;
			TagNode * const add_child();
			bool endTag;
		private:
			std::vector<TagNode*> _children;
	};
}
#endif
