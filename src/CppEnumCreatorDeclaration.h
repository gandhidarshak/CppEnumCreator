/*

MIT License

Copyright (c) 2020 Darshak Gandhi

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
//------------------------------------------------------------------------------
// Note: Don't put compiler guard in this file.
//------------------------------------------------------------------------------

#ifndef CppEnumCreatorDllExportMacro
#define CppEnumCreatorDllExportMacro /*No Dll Export?*/
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
CppEnumCreatorDllExportMacro static void enum_to_ushort (const CppEnumName e, unsigned short& i);
CppEnumCreatorDllExportMacro static void ushort_to_enum (const unsigned short i, CppEnumName& e);
CppEnumCreatorDllExportMacro static void enum_to_string (const CppEnumName e, std::string& s);
CppEnumCreatorDllExportMacro static void string_to_enum (const std::string& s, CppEnumName& e);

// prefix/postfix operator ++/-- (++e, e++, --e, e++)
CppEnumCreatorDllExportMacro CppFriendClassifier CppEnumName& operator++(CppEnumName& e); // ++prefix
CppEnumCreatorDllExportMacro CppFriendClassifier CppEnumName& operator--(CppEnumName& e); // --prefix
CppEnumCreatorDllExportMacro CppFriendClassifier CppEnumName  operator++(CppEnumName& e, int); // postfix++
CppEnumCreatorDllExportMacro CppFriendClassifier CppEnumName  operator--(CppEnumName& e, int); // postfix--

// << operator
CppEnumCreatorDllExportMacro CppFriendClassifier std::ostream& operator<<( std::ostream& out, const CppEnumName& e );

// NumItems
CppEnumCreatorDllExportMacro static unsigned short num_enum_items(CppEnumName& e);

#undef CppEnumName
#undef CppEnumList
#undef CppEnumAsCSV
#undef CppEnumCreatorDllExportMacro
#undef CppEnumParentClass
#undef CppFriendClassifier
