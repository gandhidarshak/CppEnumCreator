#include "./../src/CppEnumCreatorIncludes.h"

class Foo {
   public:

      // Declare Enum List
#define CppDllExportMacro /* give declspec macro's name if defined */
#define CppEnumParentClass Foo
#define CppEnumName Digits
#define CppEnumList \
   Zero, \
   One, \
   Two, \
   Three, \
   Four, \
   Five, \
   Six, \
   Seven, \
   Eight, \
   Nine

#include "./../src/CppEnumCreatorDeclaration.h"

};

namespace Bar {

      // Declare Enum List
#define CppDllExportMacro /* give declspec macro's name if defined */
// #define CppEnumParentClass - Don't define ParentClass as this enum resides directly in a namespace
#define CppEnumName Days 
#define CppEnumList \
   Monday, \
   Tuesday, \
   Wednesday, \
   Thursday, \
   Friday, \
   Saturday, \
   Sunday

#include "./../src/CppEnumCreatorDeclaration.h"

};
