/* Generated By:JavaCC: Do not edit this line. JavaCC.h Version 7.0 */
/* JavaCCOptions:STATIC=false,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef JAVACC_JAVACC_H_
#define JAVACC_JAVACC_H_

#include <string>
#include <memory>
#include <cassert>
#include <functional>

#ifndef JAVACC_CHAR_TYPE
#define JAVACC_CHAR_TYPE char
#endif

#ifndef JAVACC_STRING_TYPE
#define JAVACC_STRING_TYPE std::basic_string<JAVACC_CHAR_TYPE>
#endif

#define JAVACC_SIMPLE_STRING std::basic_string<char>

typedef JAVACC_CHAR_TYPE     JJChar;
typedef JAVACC_STRING_TYPE   JJString;
typedef JAVACC_STRING_TYPE   JJStringBuffer;
typedef JAVACC_SIMPLE_STRING JJSimpleString;

// Abstraction on stream classes to read a block of data into a buffer.
class ReaderStream {
public:
  // Read block of data into a buffer and return the actual number read.
  virtual size_t read(JAVACC_CHAR_TYPE *buffer, int offset, size_t len) { return 0; }
  virtual bool   endOfInput() { return true; }
  virtual ~ReaderStream() {}
};

const JAVACC_CHAR_TYPE EMPTY[] = { 0 };

#ifndef MAX
#define MAX(a,b) ((a)>=(b)?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) ((a)<=(b)?(a):(b))
#endif

template<typename T>
struct JJEnter
{
    JJEnter(T f_) : f{f_} {f();}
    ~JJEnter(){}
    T f;
};
template<typename T>
struct JJExit
{
    JJExit(T f_) : f{f_} {}
    ~JJExit(){f();}
    T f;
};

#endif
/* JavaCC - OriginalChecksum=b719dd5e5f87efc5315d14df0b701850 (do not edit this line) */
