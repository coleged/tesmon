//
//  base64.hpp
//  tesmon
//
//  snarfed from
//  https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
//
//  credit to Michal Lihocký
//
// added overload to encode std::string in addition to std::vector<BYTE> - colege@gmail.com

/*  USAGE
 
 std::vector<BYTE>  myData;
 std::string        myString;
 std::string        encodedString;
 ...
 std::string encodedData = base64_encode(&myData[0], myData.size());
 std::string encodedData = base64_encode(myString, myString.size());
 std::vector<BYTE> decodedData = base64_decode(encodedString);
 
 */

#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;

// encode a buffer - std::vector<BYTE> into BASE64 std::string
std::string base64_encode(BYTE const* buf, unsigned int bufLen);
// encode a string - std::string into BASE64 std::string
std::string base64_encode(std::string buf, unsigned int bufLen);
// decode BASE64 std::string into std::vector<BYTE>
std::vector<BYTE> base64_decode(std::string const&);

#endif
