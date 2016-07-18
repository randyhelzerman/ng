#include<ng_vector.h>
#include<ng_vector.t.h>


// debugging
void ng_vector_dump(const ng_vector_t* self, const int fruit_size, void(*fruit_dump)(const void*))
{
  // print out basic stats
  printf("vector: numb=%d  max=%d ", self->numb_, self->max_);
  
  // if we have a dump function, dump the contents
  if(0x0 != fruit_dump){
    printf("[ ");
    for(int i=0;i<self->numb_;i++){
      const void* position = (const void*)(self->fruits_ + i*fruit_size);
      fruit_dump(position);
      printf(" ");
    }
    printf("] ");
  }
}
