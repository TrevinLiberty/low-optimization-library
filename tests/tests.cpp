#include "lol/string.h"
#include "lol/ObjectManager.h"

#include <iostream>
#include <vector>
#include <cassert>

const char* TestFilePath = "text.txt";

void TestObjectManager();

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

	TestObjectManager();

    std::cout << "Done! (Press ENTER to exit)";
    getchar();
}

void TestObjectManager()
{
	//------------------------------------------------------------------------------------------------------------------
	//	Object Manager - tliberty

	lol::ObjectManager<std::vector<long long> > manager;
	std::vector<lol::ObjectID> objects;

	static const int s_numObjectsToTest = 128;

	for(size_t i = 0; i < s_numObjectsToTest; ++i)
	{
		objects.push_back(manager.CreateNewObject());
		assert(manager.GetObject(objects.back()) != nullptr);
	}

	std::random_shuffle(objects.begin(), objects.end());

	for(size_t i = 0; i < s_numObjectsToTest * 0.5f; ++i)
	{
		manager.RemoveObject(objects.back());
		assert(manager.GetObject(objects.back()) == nullptr);
		objects.pop_back();
	}

	for(size_t i = 0; i < s_numObjectsToTest * 0.5f; ++i)
	{
		objects.push_back(manager.CreateNewObject());
		assert(manager.GetObject(objects.back()) != nullptr);
	}

	std::random_shuffle(objects.begin(), objects.end());

	const size_t objectSize = objects.size();
	for(size_t i = 0; i < objectSize; ++i)
	{
		lol::ObjectID back = objects.back();
		assert(manager.GetObject(back) != nullptr);
		manager.RemoveObject(back);
		assert(manager.GetObject(back) == nullptr);
		objects.pop_back();
	}

	//	~Object Manager - tliberty
	//------------------------------------------------------------------------------------------------------------------
}