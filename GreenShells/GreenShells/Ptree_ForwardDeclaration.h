#pragma once
#include <string>

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}