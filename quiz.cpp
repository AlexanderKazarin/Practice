#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <cstdint>

auto getText(const char* path)
{
	std::map<std::string, std::string> database;
	std::ifstream resultStream;
	std::string line;
	std::string english, russian;
	std::regex expr("( - )");

	resultStream.open(path);
	if (!resultStream.is_open())
		throw std::string("Файл не найден.");

	while (std::getline(resultStream, line))
	{
		line = std::regex_replace(line, expr, " ");
		std::stringstream lineStream(line);
		std::getline(lineStream, english, ' ');
		std::getline(lineStream, russian, ' ');

		if (!english.empty() && !russian.empty())
			database.insert(std::pair<std::string, std::string>(english, russian));
	}

	return database;
}

int main(int argc, char** argv)
{
	try
	{	
		if (argc < 2)
			throw std::string("use ./quiz /path/to/result.txt");

		srand(time(NULL));
		std::string buf;
		auto database = getText(argv[1]);
		auto iterator = database.begin();
		int8_t index = rand() % (database.size() - 1);
		for (int8_t i = 0; i < index; i++)
			iterator++;

		std::cout << "Введите перевод слова " << iterator->first << ":\n";
                std::cin >> buf;
                if (iterator->second == buf)
                    std::cout << "Верно!" << '\n';
                else
                    std::cout << "Неверно! Правильный перевод - " << iterator->second << ".\n";
		return 0;
	}
	catch (std::string s)
	{
		std::cout << s << '\n';
		return -1;
	}
}