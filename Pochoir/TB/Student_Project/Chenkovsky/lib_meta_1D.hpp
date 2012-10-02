/* Author: Chenkovsky */

#include <cstdlib>
#include "lib_common.hpp"
#include <functional>

using namespace std;

template<typename Dtype>
void inline ps2mid(function<Dtype (Dtype, Dtype)>  op, Dtype *arr, Dtype *cache, size_t start, size_t end, size_t mid_range_size);


template<typename Dtype, int Dim, int A>
class Meta{

};

template<typename Dtype>
class Meta<Dtype,1,0>{
public:
  Meta(function<Dtype (Dtype, Dtype)>  op, Dtype *arr, size_t size);
  Dtype query(size_t *a, size_t *b);
  ~Meta();
private:
  size_t size;
  Dtype *arr;
  Dtype * cache;
  size_t logceil;
  size_t logfloor;
  size_t sizeround;
  size_t cache_size;
  void preprocess();
  protected:
      function<Dtype (Dtype, Dtype)>  op;
};
template<typename Dtype>
Meta<Dtype,1,0>::~Meta(){
    delete [] cache;
}
template<typename Dtype>
Meta<Dtype, 1, 0>::Meta(function<Dtype (Dtype, Dtype)>  op, Dtype *arr, size_t size){
  this->op = op;
  this->arr = arr;
  this->size = size;
  this->logceil = log2_ceil(size);
  this->logfloor = log2_floor(size);
  this->preprocess();
}


template<typename Dtype>
Dtype Meta<Dtype,1,0>::query(size_t *a,size_t *b){
  if(*a + 1 == *b){
    return this->arr[*a];
  }
  size_t sig_place = msb_pos((*a)^(*b-1));
  size_t mask = ((1<<(sig_place -1))-1)^((size_t)((long)-1)) ;
  size_t mid = ((*b)-1) & mask;
  size_t sigdiff = this->logceil - sig_place;
  size_t idx = sigdiff * this->sizeround;
  if(*b-1 == mid){
        return this->cache[(*a) +idx];
    }
  return this->op(this->cache[idx+*a],this->cache[idx+*b-1]);
}

template<typename Dtype>
void Meta<Dtype, 1, 0>::preprocess(){
  this->sizeround = 1<< this->logceil ;
  this->cache_size = this->logceil * this->sizeround;
  this->cache = new Dtype[this->cache_size]();
  size_t i;
  size_t j;
  size_t k;
  size_t cache_idx = 0;
  for(i = 0;i<this->logceil;i++){
    k = 1<<i;
    size_t range_size = this->sizeround >> i;
    size_t start = 0;
    size_t end = range_size;
    size_t mid_range_size = range_size >> 1;
    for(j = 0;j<k;j++){
        if(start + mid_range_size >= this->size){
            cache_idx += range_size*(k-j);
            break;
        }
      if(end >= this->size){
	ps2mid(op,this->arr, &(this->cache[cache_idx]),start, this->size, start + mid_range_size);
                  cache_idx += range_size*(k-j);
	break;
      }
      ps2mid(op,this->arr, &(this->cache[cache_idx]),start, end, start + mid_range_size);
      cache_idx += range_size;
      start = end;
      end += range_size;
    }
  }
}

template<typename Dtype>
void inline ps2mid(function<Dtype (Dtype, Dtype)>  op, Dtype *arr, Dtype *range_cache, size_t a, size_t b, size_t mid){
    range_cache[(mid-a)] = arr[mid];
    long i;
    if(mid+1<b){
        range_cache[mid+1-a] = arr[mid+1];
    }
    for(i = mid+2;i<b;i++){
        range_cache[(i-a)] = op(range_cache[(i-a-1)],arr[i]);
    }
    for(i = mid-1;i>=(long)a;i--){
        range_cache[(i-a)] = op(range_cache[(i-a+1)],arr[i]);
    }
}



template<typename Dtype>
inline Dtype* ps_cache(function<Dtype(Dtype,Dtype)> op, Dtype *arr, size_t size,size_t usize){
    size_t i = 0;
    size_t end = i+usize;
    size_t end2 = size-usize;
    Dtype *cache = new Dtype[size*2];
    while(i<end2){
        ps2side(op,arr,&cache[i*2],&cache[(i*2)+usize],i,end);
        i= end;
        end += usize;
    }
    ps2side(op,arr,&cache[i*2],&cache[(i*2)+size-i],i,size);
    return cache;
}

