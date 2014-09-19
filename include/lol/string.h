#pragma once

#include <list>
#include <iostream>


namespace lol {

/**
 * Basic string class. Internally, stores a linked list of character pointers,
 * each pointing to a buffer containing a single character, for maximum memory
 * fragmentation. Additionally, storing the characters in a linked list ensures
 * that random access is as slow as possible. This has the added bonus of making
 * assignment, resizing, and printing of the string obscenely sluggish, as the
 * memory for each character must be created, manipulated, and destroyed
 * individually.
 */
class string
{
public:
    string( const char* charz );
    string( const char* charz, size_t size );
    ~string();

    void assign( const char* charz, size_t size );
    void resize( size_t size );

    char& operator[]( size_t index ) const;
    size_t size() const;

private:
    std::list< char* > m_characters;
};


inline string::string( const char* charz )
{
    size_t size = strlen( charz );
    assign( charz, size );
}


inline string::string( const char* charz, size_t size )
{
    assign( charz, size );
}


inline string::~string()
{
    resize( 0 );
}


inline void string::assign( const char* charz, size_t size )
{
    resize( size );
    for( size_t i = 0; i < size; ++i )
    {
        ( *this )[ i ] = charz[ i ];
    }
}


inline void string::resize( size_t size )
{
    if( size < m_characters.size() )
    {
        std::list< char* >::iterator start = m_characters.begin();
        size_t diff = ( m_characters.size() - size );
        for( size_t i = 0; i < diff; ++i )
        {
            ++start;
        }

        for( std::list< char* >::iterator itr = start; itr != m_characters.end(); ++itr )
        {
            delete *itr;
        }

        m_characters.resize( size );
    }
    else if( size > m_characters.size() )
    {
        size_t before = m_characters.size();
        m_characters.resize( size );

        std::list< char* >::iterator start = m_characters.begin();
        for( size_t i = 0; i < before; ++i )
        {
            ++start;
        }

        for( std::list< char* >::iterator itr = start; itr != m_characters.end(); ++itr )
        {
            *itr = new char( '\0' );
        }
    }
}


inline char& string::operator[]( size_t index ) const
{
    std::list< char* >::const_iterator itr = m_characters.begin();

    for( size_t i = 0; i < index; ++i )
    {
        ++itr;
    }

    return **itr;
}


inline size_t string::size() const
{
    return m_characters.size();
}


inline std::ostream& operator<<( std::ostream& stream, const string& str )
{
    for( size_t i = 0; i < str.size(); ++i )
    {
        stream << str[ i ];
    }
    return stream;
}

}