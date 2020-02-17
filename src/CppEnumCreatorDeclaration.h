//------------------------------------------------------------------------------
// Note: Don't put compiler guard in this file.
//------------------------------------------------------------------------------

#ifndef CppDllExportMacro
#define CppDllExportMacro /*No Dll Export?*/
#endif

#ifndef CppEnumName
#error "Please define CppEnumName macro before including CppEnumDeclarationCreator.h file."
#endif

#ifndef CppEnumList
#error "Please define CppEnumList macro before including CppEnumDeclarationCreator.h file."
#endif

#ifndef CppEnumParentClass
#define CppEnumParentClass /*Namespace API*/
#define CppFriendClassifier /*Namespace doesn't require friend classifier*/
#else
#define CppFriendClassifier friend
#endif

#ifndef CppStringify
#define CppStringify_(...) #__VA_ARGS__
#define CppStringify(x) CppStringify_(x)
#endif

#ifndef CppConcatenate
#define CppConcatenate_(x,y) x ## y
#define CppConcatenate(x,y) CppConcatenate_(x,y)
#endif

#ifdef CppEnumAsCSV
#error "Please un-define CppEnumAsCSV macro before including CppEnumDeclarationCreator.h file."
#else
#define CppEnumAsCSV CppConcatenate(CppEnumName,_as_CSV)
#endif

// Using strongly typed enum for better scope control /conversion safety
enum class CppEnumName : unsigned short { CppEnumList, NumItems };

// have to use char* as string is not yet supported for static constexpr
// variable initialization. Change after C++20 becomes mainstream.
static constexpr const char* CppEnumAsCSV = 
   CppStringify(CppEnumList)
   ", NumItems";

// enum/unsigned short/string conversions
CppDllExportMacro static void enum_to_ushort (const CppEnumName e, unsigned short& i);
CppDllExportMacro static void ushort_to_enum (const unsigned short i, CppEnumName& e);
CppDllExportMacro static void enum_to_string (const CppEnumName e, std::string& s);
CppDllExportMacro static void string_to_enum (const std::string& s, CppEnumName& e);

// prefix/postfix operator ++/-- (++e, e++, --e, e++)
CppDllExportMacro CppFriendClassifier CppEnumName& operator++(CppEnumName& e); // ++prefix
CppDllExportMacro CppFriendClassifier CppEnumName& operator--(CppEnumName& e); // --prefix
CppDllExportMacro CppFriendClassifier CppEnumName  operator++(CppEnumName& e, int); // postfix++
CppDllExportMacro CppFriendClassifier CppEnumName  operator--(CppEnumName& e, int); // postfix--

// << operator
CppDllExportMacro CppFriendClassifier std::ostream& operator<<( std::ostream& out, const CppEnumName& e );

// NumItems
CppDllExportMacro static unsigned short num_enum_items(CppEnumName& e);

#undef CppEnumName
#undef CppEnumList
#undef CppEnumAsCSV
#undef CppDllExportMacro
#undef CppEnumParentClass
#undef CppFriendClassifier
