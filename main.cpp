#include "Dictionary.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	try	
	{
		if (argc < 3)
			throw std::string("use ./translator /path/to/dictionary.txt /path/to/text.txt");

		Dictionary *book = new Dictionary(argv[1]);
		
		book->translateText(argv[2]);

		delete book;
		return 0;
	}
	catch (std::string s)
	{
		std::cout << s << '\n';
		return -1;
	}
}