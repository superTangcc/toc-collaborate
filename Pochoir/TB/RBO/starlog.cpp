/* starlog.cpp
   6/18/12
   Joshua Slocum <jslocum@mit.edu>
   Implements the alpha function:


   Yuan Tang:
   Definition:
   
    log^*(N) = min{k | log(log(\underbrace{...}_k (N) <= 2}, which means how
    many log function need to be applied to input N to make it equal to or
    less than 2.
   
    log^**(N) = min{k | log^*(log^*(\underbrace{...}_k (N) <= 2}, which
    means how many log^* function needs to be applied to input N to make it
    equal to or less than 2.
   
    ...
   
    alpha(N) = min{k | log^**\underbrace{...*}_k (N) <= 2}, which means how
    many above procedure (* notation) needs to be applied to input N to make
    it equal to or less than 2.
*/

#include <iostream>
#include <math.h>

using namespace std;

//Note: if you're using non-integral types or want numbers larger than can fit into a dobule, you'll have to adjust the return types. Using long double ensures that it works properly with integral types.
template<typename F>
class CurriedStarLog
{
  CurriedStarLog *one_less_star;
  long double starLog(F num) {
    if(one_less_star) {
      unsigned long n = num, res = 0;
      while (n >= 2) {
        n = one_less_star->starLog(n); ++res;
      }
      return res;
    }
    else {
      return log(num);
    }
  }

public:

  static long double alpha(CurriedStarLog* csl, long double num, int recursion_depth)
  {
    long double star_log = csl->starLog(num);
    if (star_log <= 2) {
      return recursion_depth;
    }
    else {
      CurriedStarLog<F>* one_more_star = new CurriedStarLog(csl);
      long double answer =
        CurriedStarLog::alpha(one_more_star, num, recursion_depth + 1);
      delete one_more_star;
      return answer;
    }
  }
  
  CurriedStarLog(void) {
    this->one_less_star = 0;
  }

  CurriedStarLog(CurriedStarLog<F>* csl) {
    this->one_less_star = csl;
  }

};

template<typename F>
F alpha(F num)
{
  CurriedStarLog<F>* csl = new CurriedStarLog<F>();
  F answer = CurriedStarLog<F>::alpha(csl, num, 1);
  delete csl;
  return answer;
}


int main(int argc, char **argv) {
  cout << alpha(2) << endl;
  cout << alpha(10) << endl;
  cout << alpha(100000) << endl;
  cout << alpha(1000000000000) << endl;
  cout << alpha(100000000000000000) << endl;
}

/*
$ ./starlog.cpp
  1
  2
  3
  3
  3
*/
