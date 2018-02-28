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
		private:
			void _from_string( TagNode * );
			std::ifstream _file;
	};
}

#endif
