#include <iostream>
#include <fstream>

using namespace std;

// This is a simple C++ console application where we experiment a bit with writing to a file
int main()
{
    cout << "Fun with writing to files" << std::endl;

    ofstream file1("dummy.txt");
    file1 << "Files can be tricky, but it is fun enough!";
    file1.close();

    ofstream file2("rectangles.svg");
    file2 << "<svg width=\"500\" height=\"500\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    file2 << "  <rect width=\"200\" height=\"100\" x=\"10\" y=\"10\" rx=\"20\" ry=\"20\" fill=\"blue\" />" << endl;
    file2 << "  <rect width=\"200\" height=\"100\" x=\"110\" y=\"60\" fill=\"green\" />" << endl;
    file2 << "</svg>" << endl;
    file2.close();

    return 0;
}