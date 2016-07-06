#include "Wordbook.h"

int main(int argc, char** argv)
{
	Wordbook mybook;

	mybook.loadWordbook("wordbook.txt");
	mybook.translate("text.txt");

	return 0;
}