#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool IsLetter(char c)
{
    return (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')));
}

string RepairString(string s)
{
    while (!(IsLetter(s[0])))
        s.erase(0, 1);
    while (!(IsLetter(s[s.length() - 1])))
        s.erase(s.length() - 1, 1);
    return s;
}

int main()
{
    ifstream fin;
    fin.open("Input.txt");
    ofstream fout;
    fout.open("Output.txt");
    string s;
    while (!(fin.eof()))
    {
        fin >> s;
        s = RepairString(s);
        fout << s << endl;
    }
    fout.close();
    fin.close();
    return 0;
}
