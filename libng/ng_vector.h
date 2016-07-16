#ifndef NG_VECTOR___H
#define NG_VECTOR___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_vector {
    int       max_;       // maximum number of items this vector can hold.
    int       numb_;      // the current number of items this vector holds.
    char      fruits_[];  // you know how this works
  } ng_vector_t;
  
  // constructors
  ng_vector_t* ng_vector_new(const size_t fruit_size, const int max);
  
  ng_vector_t* ng_vector_init(ng_vector_t* self,
			      const size_t fruit_size, const int max);
  
  // destructors
  void ng_vector_delete(ng_vector_t** selfp,
			const int fruit_size,
			void(*fruit_uninit)(void*));
  
  void ng_vector_uninit(ng_vector_t* self,
			const int fruit_size,
			void(*fruit_uninit)(void*));
  
  // accesss

  // just for convenience
  bool ng_vector_empty(const ng_vector_t* self);
  
  // get a pointer to an elment in the vector
  void* ng_vector_at(ng_vector_t* self, const int index, const int fruit_size);

  // returns the back ("top") of th stack...
  void* ng_vector_back(ng_vector_t* self, const int fruit_size);
  
  // add an element to the end of the vector
  void
  ng_vector_push_back(ng_vector_t** selfp,
		      const int fruit_size, const void* fruit,
		      void*(*fruit_cp_init)(const void*,
					    void*),
		      void(*fruit_uninit)(void*));
  
  // remove an element from the end of the vector
  void
  ng_vector_pop_back(ng_vector_t* self,
		     const int fruit_size,
		     void(*fruit_uninit)(void*));

  // binary search.  Equivalent to upper_bound in c++ STL
  int
  ng_vector_binary_search_upper_bound(const ng_vector_t* v,
				      const int l, const int h,
				      const int fruit_size,
				      const void* fruit,
				      int(*fruit_compare)(const void*,
							  const void*));
  
  // binary search.  Equivalent to lower_bound in c++ STL
  int
  ng_vector_binary_search_lower_bound(const ng_vector_t* v,
				      const int l, const int h,
				      const int fruit_size,
				      const void* fruit,
				      int(*fruit_compare)(const void*,
							  const void*));
  
  // private functions
  
  
  // debugging
  void ng_vector_dump(const ng_vector_t* self, const int fruit_size,
		      void(*fruit_dump)(const void*));
  
  
#ifdef __cplusplus
};
#endif

#endif
