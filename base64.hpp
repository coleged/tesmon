//
//  base64.hpp
//
//  snarfed from
//  https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
//
//  credit to Michal Lihocký
//
// added function to encode std::string in addition to std::vector<BYTE> - colege@gmail.com

/*  USAGE
 
 std::vector<BYTE> myData;
 ...
 std::string encodedData = base64_encode(&myData[0], myData.size());
 std::vector<BYTE> decodedData = base64_decode(encodedData);
 
 */

#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;

// encode a buffer - std::vector<BYTE>
std::string base64_encode(BYTE const* buf, unsigned int bufLen);
// encode a string - std::string
std::string base64_encode(std::string buf, unsigned int bufLen);

std::vector<BYTE> base64_decode(std::string const&);

#endif
