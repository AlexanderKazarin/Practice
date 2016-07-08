#include "Dictionary.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv)
{
	try 
	{
		Dictionary mybook;

		mybook.loadDictionary("dictionary.txt");
		mybook.translate("text.txt");
		mybook.test();
		return 0;
	}
	catch (std::exception e)
	{
		std::cout << e.what();
		return -1;
	}
}