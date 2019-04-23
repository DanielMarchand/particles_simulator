#ifndef __MY_TYPES_HH__
#define __MY_TYPES_HH__

/* -------------------------------------------------------------------------- */
#include <iostream>

typedef unsigned int UInt;
typedef double Real;

/* -------------------------------------------------------------------------- */
#define TO_IMPLEMENT                                                           \
  {                                                                            \
    std::cerr << std::endl                                                     \
              << std::endl                                                     \
              << "*********************************************************\n" \
              << "To be filled @ " << __FILE__ << ":" << __LINE__ << std::endl \
              << "*********************************************************\n" \
              << std::endl                                                     \
              << std::endl;                                                    \
    throw;                                                                     \
  }
/* -------------------------------------------------------------------------- */

#define EXERCISE_BEGIN_CORRECTION
#define EXERCISE_END_CORRECTION

#endif /* __MY_TYPES_HH__ */
