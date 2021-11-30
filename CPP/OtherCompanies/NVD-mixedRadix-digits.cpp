/*
 
Consider a moment in time in a week --> some number of seconds since the beginning of the week.
 
(days, hours, minutes, seconds) <--> some integer representing the number of seconds since that week started.
 
(5, 14,22,10) "the digits" relative to the bases (7,24,60,60) can be converted to: 5*24*60*60 + 14*60*60 + 22*60 + 10 == 483730  [ ((5*24 + 14) * 60 + 22)*60 + 10 ]
 
483730 == (5,14,22,10) [ relative to bases (7,24,60,60)]
 
 
0fa1 (2,16,16,2) our bases == 0*16*16*2 + 0xf*16*2 + 0xa*2 + 1
 
*/

// base: four components? ()


#include <cstdio>
#include <cstdint>
#include <cstdlib>

struct mixed_radix_t {
  uint32_t * base;  // (7,24,60,60)
  uint32_t * digits; // (5,14,22,10) 
  int32_t n_base; // 4
  
  // vector<uint32_t *> children;  // delete[]
};

// mixed_radix_t *

mixed_radix_t * mr_create(const uint32_t * base, const uint32_t n_base) {  // n_base > base.size(),   base-NULL
  // what goes here?
  // new mixed_radix_t();
  // new uint32_t[something here]
  mixed_radix_t * mrt = new mixed_radix_t();
  
  // deep copy: base
  uint32_t * baseVal   = new uint32_t[n_base];  // -4, 1000 => 0111 -4 == (~4) + 1 (depends on the bit width)
  uint32_t * digitsVal = new uint32_t[n_base];
  // allocat mm for hodling base vals  
  
  for (int i = 0; i < n_base; i++) {
      baseVal[i] = base[i];
      digitsVal[i] = 0;
  }
  
  mrt->base = baseVal;
  
  mrt->digits = digitsVal;
  
  mrt->n_base = n_base;
  
  return mrt;
  
}

void mr_free(mixed_radix_t * p) {
    // delete, delete[]
  // what goes here?
  delete[] p->base;
  delete[] p->digits;
  delete p;
  
  // what would happen if we did this???
  // delete p;  // 
  // delete[] p->base;
  // delete[] p->digits;
  
  // memory stack 
  
}

bool can_represent(const uint64_t num, mixed_radix_t * mr) {
  // pretend implemented
}

void num_to_mr_digits(const uint64_t num, mixed_radix_t * mr) {
  // what goes here?
  
  //  483730 == (5,14,22,10)
  
  // 483730 % 60 = 10
}

void set_digits(mixed_radix_t * mr, const uint32_t * digits, const int32_t n_digits) {
  // pretend implemented
}

int64_t mr_digits_to_num(const mixed_radix_t * mr) {
  // what goes here?
  
  // digits=(5,14,22,10) == > 483730
  //  [ ((dit[0]%base[0]  * base[1] + dit[1]) * bas[2] + dit[2])*bas[3] + dit[3] ]
  
  // bases=(7,24,60,60)
//  [ ((5*24 + 14) * 60 + 22)*60 + 10 ]
}

int main(int argc, char * argv[]) {

  const uint32_t base[]   = {17,10,8,4,3,2,2};
  const uint32_t digits[] = {        2,2,1,0};

  // test our work
  mixed_radix_t * number_system;
  number_system = mr_create(base, sizeof(base)/sizeof(uint32_t));

  if(NULL == number_system) {
    exit(EXIT_FAILURE);
  }

  set_digits(number_system, digits, sizeof(digits)/sizeof(uint32_t));
  uint64_t test_num = mr_digits_to_num(number_system);

  printf("test_num: %" PRIu64 "\n", test_num);

  exit(EXIT_SUCCESS);
}
