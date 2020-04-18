//------------------------------------------------------------------------------
// Note: Don't put compiler guard in this file.
//------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <mutex>

#ifndef CppEnumName
#error "Please define CppEnumName macro before including CppEnumDefinitionCreator.h file."
#endif

#ifdef CppEnumAsCSV
#error "Please un-define CppEnumAsCSV macro before including CppEnumDefinitionCreator.h file."
#else
#define CppEnumAsCSV CppConcatenate(CppEnumName,_as_CSV)
#endif

void 
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_ushort (const CppEnumName e, unsigned short& i)
{
   i = static_cast<unsigned short>(e);
}

void 

#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
ushort_to_enum (const unsigned short i, CppEnumName& e)
{
   unsigned short lastI=0;
   enum_to_ushort(CppEnumName::NumItems,lastI);
   if(i<=lastI)
      e = static_cast<CppEnumName>(i);
   else
   {
      e = CppEnumName::NumItems; 
      std::cerr << "Out of bounds ushort_to_enum conversion for ushort " << i << std::endl;
   }
}

void 
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_string (const CppEnumName e, std::string& s)
{
   static std::vector<std::string> s_e2s;
   unsigned short i = 0;
   enum_to_ushort(e,i);
   if(s_e2s.empty()) // Initialize - thread safe.
   {
      static std::mutex s_e2sMutex;
      std::lock_guard<std::mutex> lock(s_e2sMutex);
      if(s_e2s.empty()) // Race condition check
      {
         std::string varsCSV = CppEnumAsCSV;
         // Remove spaces from string CSV
         varsCSV.erase(std::remove(varsCSV.begin(), varsCSV.end(), ' '), varsCSV.end());
         auto pos = varsCSV.find(',');
         while(pos != std::string::npos)
         {
            std::string varNext = varsCSV.substr(0,pos);
            varsCSV = varsCSV.substr(pos+1);
            s_e2s.push_back(varNext);
            pos = varsCSV.find(',');
         }
         s_e2s.shrink_to_fit();
      }
   }
   if(i < s_e2s.size())
      s = s_e2s.at(i);
   else
      s = "";  // This can never happen
}

void 
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
string_to_enum (const std::string& s, CppEnumName& e)
{
   std::unordered_map<std::string, unsigned short> l_s2e;
   if(l_s2e.empty()) // Initialize - thread safe.
   {
      static std::mutex s2eMutex;
      std::lock_guard<std::mutex> lock(s2eMutex);
      if(l_s2e.empty()) // Race condition check
      {
         std::string varsCSV = CppEnumAsCSV;
         // Remove spaces from string CSV
         varsCSV.erase(std::remove(varsCSV.begin(), varsCSV.end(), ' '), varsCSV.end());
         auto pos = varsCSV.find(',');
         unsigned short i = 0;
         while(pos != std::string::npos)
         {
            std::string varNext = varsCSV.substr(0,pos);
            varsCSV = varsCSV.substr(pos+1);
            l_s2e.insert(std::make_pair(varNext,i));
            pos = varsCSV.find(',');
            ++i;
         }
      }
   }
   auto itr = l_s2e.find(s);
   if(itr != l_s2e.end())
      ushort_to_enum(itr->second,e);
   else
   {
      std::cerr << "Out of bounds string_to_enum conversion for string " << s << std::endl;
      e = CppEnumName::NumItems;
   }
}

// https://en.cppreference.com/w/cpp/language/operator_incdec

#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& operator++(
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& e)
{
   if(e==
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName::NumItems)
   {
      std::cerr << "Out of bounds prefix increment operator used." << std::endl;
      return e;
   }
   unsigned short i;
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_ushort(e,i);
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
ushort_to_enum(++i,e);
   return e;
}

// prefix operator --e

#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& operator--(
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& e)
{
   unsigned short i;
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_ushort(e,i);
   if(i==0)
   {
      std::cerr << "Out of bounds prefix decrement operator used." << std::endl;
      return e;
   }
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
ushort_to_enum(--i,e);
   return e;
}


#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName operator++(
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& e, int )
{
   auto origE = e;
   ++e;
   return origE;
}


#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName operator--(
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& e, int )
{
   auto origE = e;
   --e;
   return origE;
}

std::ostream& operator<<( std::ostream& out,
                          const 
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
CppEnumName& e )
{
   std::string s;
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_string(e, s);
   return (out << s);
}

unsigned short 
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
num_enum_items(CppEnumName& e)
{
   unsigned short i;
   e = CppEnumName::NumItems;
   
#ifdef CppEnumParentClass
CppEnumParentClass::
#endif
enum_to_ushort(e, i);
   return i;
}

#undef CppEnumParentClass
#undef CppEnumName
#undef CppEnumAsCSV
#undef CppIsClass
