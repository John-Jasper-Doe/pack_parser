
#define NDEBUG
#include <cassert>
#include <iostream>

bool is_littleendian() {
  const int current_byte_order = (*reinterpret_cast<const int*>("\x01\x02\x03\x04"));
  return (current_byte_order == 0x04030201);
}

bool is_bigendian() {
  const int current_byte_order = (*reinterpret_cast<const int*>("\x01\x02\x03\x04"));
  return (current_byte_order == 0x01020304);
}

unsigned short byte_order(unsigned short value) {
  unsigned char res[] = {0, 0};

  if (is_littleendian()) {
    res[0] = (reinterpret_cast<unsigned char*>(&value))[1];
    res[1] = (reinterpret_cast<unsigned char*>(&value))[0];
  }
  else if (is_bigendian()) {
    res[0] = (reinterpret_cast<unsigned char*>(&value))[0];
    res[1] = (reinterpret_cast<unsigned char*>(&value))[1];
  }
  else
    throw std::runtime_error("Undefined byte order");

  return *reinterpret_cast<unsigned short*>(res);
}

void test_byteorder() {
  std::cout << "test_byteorder:" << std::flush;

  unsigned char val1[] = { 0x00, 0x21 };
  unsigned char val2[] = { 0x01, 0xbd };

  unsigned short expected1 = 0x0021;
  unsigned short expected2 = 0x01bd;

  unsigned short res1 = byte_order(*reinterpret_cast<unsigned short*>(val1));
  unsigned short res2 = byte_order(*reinterpret_cast<unsigned short*>(val2));

  std::cout << " test1 .. " << ((expected1 == res1) ? "[OK]" : "[ERROR]");
  std::cout << " test2 .. " << ((expected2 == res2) ? "[OK]" : "[ERROR]");
  std::cout << std::endl;
}
