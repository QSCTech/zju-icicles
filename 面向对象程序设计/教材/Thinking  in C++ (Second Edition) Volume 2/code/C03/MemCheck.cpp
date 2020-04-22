//: C03:MemCheck.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Memory allocation tester
//{-msc}
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
// MemCheck.h must not be included here

// Output file object using cstdio
// (cout constructor calls malloc())
class OFile {
  FILE* f;
public:
  OFile(char* name) : f(fopen(name, "w")) {}
  ~OFile() { fclose(f); }
  operator FILE*() { return f; }
};
extern OFile memtrace;
// Comment out the following to send all the
// information to the trace file:
#define memtrace stdout

const unsigned long _pool_sz = 50000L;
static unsigned char _memory_pool[_pool_sz];
static unsigned char* _pool_ptr = _memory_pool;

void* getmem(size_t sz) {
  if(_memory_pool + _pool_sz - _pool_ptr < sz) {
    fprintf(stderr,
           "Out of memory. Use bigger model\n");
    exit(1);
  }
  void* p = _pool_ptr;
  _pool_ptr += sz;
  return p;
}

// Holds information about allocated pointers:
class MemBag { 
public:
  enum type { Malloc, New };
private:
  char* typestr(type t) {
    switch(t) {
      case Malloc: return "malloc";
      case New: return "new";
      default: return "?unknown?";
    }
  }
  struct M {
    void* mp;  // Memory pointer
    type t;     // Allocation type
    char* file; // File name where allocated
    int line;  // Line number where allocated
    M(void* v, type tt, char* f, int l)
      : mp(v), t(tt), file(f), line(l) {}
  }* v;
  int sz, next;
  enum { increment = 50 };
public:
  MemBag() : v(0), sz(0), next(0) {}
  void* add(void* p, type tt = Malloc,
            char* s = "library", int l = 0) {
    if(next >= sz) {
      sz += increment;
      // This memory is never freed, so it
      // doesn't "get involved" in the test:
      const int memsize = sz * sizeof(M);
      // Equivalent of realloc, no registration:
      void* p = getmem(memsize);
      if(v) memmove(p, v, memsize);
      v = (M*)p;
      memset(&v[next], 0,
             increment * sizeof(M));
    }
    v[next++] = M(p, tt, s, l);
    return p;
  }
  // Print information about allocation:
  void allocation(int i) {
    fprintf(memtrace, "pointer %p"
      " allocated with %s",
      v[i].mp, typestr(v[i].t));
    if(v[i].t == New)
      fprintf(memtrace, " at %s: %d",
        v[i].file, v[i].line);
    fprintf(memtrace, "\n");
  }
  void validate(void* p, type T = Malloc) {
    for(int i = 0; i < next; i++)
      if(v[i].mp == p) {
        if(v[i].t != T) {
          allocation(i);
          fprintf(memtrace,
          "\t was released as if it were "
          "allocated with %s \n", typestr(T));
        }
        v[i].mp = 0;  // Erase it
        return;
      }
    fprintf(memtrace,
    "pointer not in memory list: %p\n", p);
  }
  ~MemBag() {
    for(int i = 0; i < next; i++)
      if(v[i].mp != 0) {
        fprintf(memtrace,
        "pointer not released: ");
        allocation(i);
      }
  }
};
extern MemBag MEMBAG_;

void* malloc(size_t sz) {
  void* p = getmem(sz);
  return MEMBAG_.add(p, MemBag::Malloc);
}

void* calloc(size_t num_elems, size_t elem_sz) {
  void* p = getmem(num_elems * elem_sz);
  memset(p, 0, num_elems * elem_sz);
  return MEMBAG_.add(p, MemBag::Malloc);
}  

void* realloc(void* block, size_t sz) {
  void* p = getmem(sz);
  if(block) memmove(p, block, sz);
  return MEMBAG_.add(p, MemBag::Malloc);
}

void free(void* v) { 
  MEMBAG_.validate(v, MemBag::Malloc);
}

void* operator new(size_t sz) {
  void* p = getmem(sz);
  return MEMBAG_.add(p, MemBag::New);
}

void*
operator new(size_t sz, char* file, int line) {
  void* p = getmem(sz);
  return MEMBAG_.add(p, MemBag::New, file, line);
}

void operator delete(void* v) {
  MEMBAG_.validate(v, MemBag::New);
}

MemBag MEMBAG_;
// Placed here so the constructor is called
// AFTER that of MEMBAG_ :
#ifdef memtrace
#undef memtrace
#endif
OFile memtrace("memtrace.out");
// Causes 1 "pointer not in memory list" message
///:~
