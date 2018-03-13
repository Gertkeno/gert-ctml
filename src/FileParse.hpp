#ifndef FILE_PARSE_H
#define FILE_PARSE_H

#include <TagNode.hpp>
#include <fstream>

namespace ctml
{
	class FileParse
	{
		public:
			FileParse( std::string fn );
			~FileParse();

			const std::string fileName;
			TagNode root;
			bool get_error() const { return error; };
		private:
			bool error;
			void _from_string( TagNode * );
			void _attribute_detect( TagNode *, char );
			std::ifstream _file;
	};
}

#endif
