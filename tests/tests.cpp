#include "lol/string.h"
#include <iostream>

const char* TestFilePath = "text.txt";

void main()
{
    // TODO [AndrewC]: Make this actually print benchmarking results.

    lol::string greeting( "Hello, World!" );
    std::cout << greeting << std::endl;

    FILE* file = nullptr;

    if( fopen_s( &file, TestFilePath, "r" ) == 0 )
    {
        fseek( file, 0, SEEK_END );
        int length = ftell( file );
        rewind( file );
        char* buffer = new char[ length ];
        int totalChars = fread( buffer, 1, length, file );
        lol::string text( buffer, totalChars );
        std::cout << text << std::endl;
    }
    else
    {
        std::cout << "Error: The file \"" << TestFilePath << "\" could not be opened!" << std::endl;
    }

    std::cout << "Done! (Press ENTER to exit)";
    getchar();
}