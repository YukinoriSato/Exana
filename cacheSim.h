/******************************************************************
Exana: EXecution-driven Application aNAlysis tool

Copyright (C)   2014,   Yukinori Sato
All Rights Reserved. 
******************************************************************/

////////////////////////////////////////////////////
//*****    cacheSim.h   ********************///
////////////////////////////////////////////////////

#ifndef _cacheSim_H_
#define _cacheSim_H_



#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stddef.h>

#include "pin.H"
#include "portability.H"
using namespace std;

#include <string.h>
#include <iomanip>
#include <map>
//#include <list>

#include <sched.h>

#if 1
// for per inst analysis
const bool byInstAdr=1;

// for pseudo conflict detection based on FIFO
const bool pseudoFAsimOn=0;

// for conflict detection
const bool FAsimOn=1;

// for conflict detection
const bool missOriginOn=1;
#else
const bool byInstAdr=1;
const bool pseudoFAsimOn=0;
const bool FAsimOn=0;
const bool missOriginOn=0;
#endif

// for physical address based L2/L3 simulation
//const bool physicalAdrOn=0;
const bool physicalAdrOn=1;

const bool NRU_On=0;

// for FullAssociative cache simulation
struct listElem{
  uint64_t tag;
  struct listElem *next;
  struct listElem *prev;
};

//list<uint64_t> fullAssocList;
enum FAelemT{INVALID, incache, outcache};
struct FAentryT{
  uint64_t tag;
  enum FAelemT status;
  struct FAentryT *next;
  //list<uint64_t>::iterator it;
  struct listElem *it;
};
static const uint64_t HASH_TABLE_SIZE=0x100000;
enum FAstatusT{NONE, hit, compulsory, capacity};

//enum FAstatusT FA_status;


//FAentryT *findTagInHash(uint64_t);
//void fullAssocListErase(listElem *it);
//void fullAssocListPush_front(uint64_t tag);
//int UpdateFullAssoc(uint64_t tag);

void printFullAssocList(void);


struct lastTimeWhoEvictT{
  ADDRINT evictPC;
  ADDRINT originPC;
  struct lastTimeWhoEvictT *next;
};

////////////////////////////////////

#define KBYTE (1024)
#define MBYTE (1024*1024)

extern int l1_cache_size;
extern int l1_way_num;
extern int l2_cache_size, l2_way_num, l3_cache_size,
  l3_way_num, block_size;

enum clevel{
  clevel1=1,
  clevel2,
  clevel3,
  clevel_num
};

//UINT64 evicted_list_num=16;
//UINT64 evicted_list_num=32;
extern BUFFER_ID bufId;

extern TLS_KEY tls_key;

extern UINT64 evicted_list_num[clevel_num];


struct cacheT{
  UINT64 size;
  UINT64 assoc;
  UINT64 line_size;
  UINT64 nSets;
  UINT64 line_size_bits;
  UINT64* tags;
  enum clevel cacheLevel;
  //vector<list<uint64_t> *> evicted_list;  // in each set 
  UINT64* evicted_list;  // in each set 
  UINT64 n_pseudo_conflict;
  UINT64 n_conflict;
  UINT64 n_invalidate;
  UINT64 n_invalidateFA;

  //FAentryT *FAhash[HASH_TABLE_SIZE];
  FAentryT **FAhash;
  listElem *fullAssocList;
  listElem *fullAssocListTail;

  listElem *fullAssocListBase;
  uint64_t fullAssocListElemCnt;

  uint64_t fullAssocListCnt;
  uint64_t fullAssocListNum;
  enum FAstatusT FA_status;

  uint64_t FA_hitCnt;
  uint64_t FA_compulsoryCnt;
  uint64_t FA_capacityCnt;

  uint64_t conflict_agree, conflict_disagree, capacity_agree, capacity_disagree;

  //map<ADDRINT, ADDRINT> replaceOriginatedPC;
  struct lastTimeWhoEvictT **ltwet;
  UINT64 numLtwet;
  struct lastTimeWhoEvictT *baseLtwet;

  UINT64 *NRU_position;
  UINT64 n_slice;


};
  
//struct cacheT l1c, l2c, l3c;


////////////////////////////////////////////////////////////
// for instruction local cache profiling


struct MEMREF
{
  ADDRINT     pc;
  ADDRINT     ea;
  UINT32      size;
  //BOOL        read;
};

struct missOriginatedListT{
  struct missOriginatedListT *next;
  ADDRINT instAdr;
  uint64_t cnt;
};

struct CacheAccessInfoT {
  ADDRINT instAdr;
  struct CacheAccessInfoT *next;
  uint64_t *c_hits;
  uint64_t miss;
  uint64_t *c_conflict;
  uint64_t n_access;
  ADDRINT maxAdr;
  ADDRINT minAdr;
  ADDRINT physicalAdr;
  struct missOriginatedListT *missOriginated[clevel_num];
};


/*
 * Number of OS pages for the buffer
 */
//#define NUM_BUF_PAGES 1024
#define NUM_BUF_PAGES 1


//map< uint64_t, CacheAccessInfo> addr_results;

//struct CacheAccessInfoT **addr_results;


struct mallocListT{
  int mlcount;
  ADDRINT callerIp;
  ADDRINT returnIp;
  ADDRINT instAdr;
  UINT64 size;
  THREADID threadid;
  string *gfileName;
  int line;
};


// for multithreaded programs

class ThreadLocalData
{
  public:
    ThreadLocalData(THREADID tid);
    ~ThreadLocalData();
  void DumpBuffer( struct MEMREF * reference, UINT64 numElements, THREADID tid );
  void csim_init(int l1_cache_size, int l1_way_num, int l2_cache_size, int l2_way_num, int l3_cache_size,int l3_way_num, int block_size);

  void cachesim(ADDRINT adr,  INT32 size, ADDRINT pc, THREADID threadid);
  bool isCacheMiss(struct cacheT *c, ADDRINT adr, INT32 size,  struct CacheAccessInfoT *cinfo, THREADID threadid);
  bool checkCacheMiss(struct cacheT *c, UINT64 set_no, UINT64 tag,  struct CacheAccessInfoT *cinfo);

  bool checkCacheMissNRU(struct cacheT *c, UINT64 set_no, UINT64 tag,  struct CacheAccessInfoT *cinfo);

  void Invalidate(struct cacheT *c, uint64_t tag);
  void InvalidateInFA(struct cacheT *c, uint64_t tag);

  FAentryT* findTagInHash(struct cacheT *c, uint64_t tag);
  //void flushFAHash(struct cacheT *c);

  int UpdateFullAssoc(struct cacheT *c, uint64_t tag);
  void fullAssocListErase(struct cacheT *c, listElem *it);
  void fullAssocListPush_front(struct cacheT *c, uint64_t tag);

  struct CacheAccessInfoT* findInstInHash(ADDRINT instAdr, struct CacheAccessInfoT **);

  struct cacheT l1c, l2c, l3c;
  struct CacheAccessInfoT **addr_results;
  UINT64 L1access,L1miss,L2miss,L3miss;

  // for mallocDetect
  vector <struct mallocListT *> mallocList;

  bool flushFlag;

  void printMissOriginate(struct CacheAccessInfoT *cinfo);
  void updateMissOriginate(struct CacheAccessInfoT *cinfo, int cacheLevel, ADDRINT originatedPC);
  struct lastTimeWhoEvictT* findMissPCInHash(struct cacheT *c, uint64_t tag);
  void updateMissOriginPCInHash(struct cacheT *c, ADDRINT replacedPC, ADDRINT missPC);


private:

  //ofstream _ofile;
};


void printCacheStat(void);
void outputByInst();

extern vector <THREADID > tid_list;
extern void flushCache(struct cacheT *c);

extern bool samplingSimFlag;
extern bool evaluationFlag;

#endif

