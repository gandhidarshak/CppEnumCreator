#include "test.h"
#include <iomanip>
// #include "CppReflection.h"

// Define APIs related to Enum
#define CppEnumName Digits 
#define CppEnumParentClass Foo
#include "./../src/CppEnumCreatorDefinition.h" 

namespace Bar {
#define CppEnumName Days 
#include "./../src/CppEnumCreatorDefinition.h" 
}

void testDigitsEnum()
{
   // Test Digits enum defined inside class Foo
   Foo::Digits e, eLast;
   std::string enumAsString;
   unsigned short enumAsInt;

   std::cout << "Enum Digits has "  << Foo::num_enum_items(eLast) << " items." << std::endl;
   std::cout << "Iterating over enums using increment(++) operator:" << std::endl;

   // ushort_to_enum converts unsigned short number into enum
   // Get the first item in enum by passing 0 index.
   Foo::ushort_to_enum(0,e);

   std::cout.width(15);
   std::cout  << "enum_to_ushort" << " "  << "enum_to_string" << std::endl;
    
   for(; e != eLast ; ++e)
   {
      Foo::enum_to_string(e,enumAsString);
      Foo::enum_to_ushort(e,enumAsInt);
      std::cout.width(15);
      std::cout  << enumAsInt << " "  << enumAsString << std::endl;
   }
}

void testDaysEnum()
{
   // Test Digits enum defined inside class Foo
   Bar::Days e, eLast;
   std::string enumAsString;
   unsigned short enumAsInt;

   std::cout << "Enum Days has "  << Bar::num_enum_items(eLast) << " items." << std::endl;
   std::cout << "Iterating over enums using increment(++) operator:" << std::endl;

   // ushort_to_enum converts unsigned short number into enum
   // Get the first item in enum by passing 0 index.
   Bar::ushort_to_enum(0,e);

   std::cout.width(15);
   std::cout  << "enum_to_ushort" << " "  << "enum_to_string" << std::endl;
    
   for(; e != eLast ; ++e)
   {
      Bar::enum_to_string(e,enumAsString);
      Bar::enum_to_ushort(e,enumAsInt);
      std::cout.width(15);
      std::cout  << enumAsInt << " "  << enumAsString << std::endl;
   }

   Bar::Days eAnother;
   // string_to_enum converts a string to enum when possible.
   Bar::string_to_enum(enumAsString,eAnother);
   std::cout << "Example of using << operator for enum: " << eAnother << std::endl;
   
}


int main()
{
   testDigitsEnum();
   testDaysEnum();
   return 0;
}
