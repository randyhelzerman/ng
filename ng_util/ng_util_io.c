#include <ng_util_io.h>

#include <stdio.h>
#include <stdlib.h>


char* loadFileIntoBuffer(const char* filename,
			 char** buffer)
{
  // open the file
  FILE* fh = fopen(filename,"rb");
  if(0x0==fh){
    *buffer = 0x0;
    return 0x0;
  }
  
  // Janky way to do it: seek to end of the file...
  if(fseek(fh,0,SEEK_END)){
    *buffer = 0x0;
    return 0x0;
  }
  
  //... and ask how many bytes we are at.
  // always succeeds so we don't check for
  // errors here; but we do check the return
  // value later.
  const size_t numb_bytes_in_file = ftell(fh);
  
  // reset to beginning so we can read the whole file
  // rewind always succeeds, so we don't have to
  // do any error checking.
  rewind(fh);
  
  // allocate memory to contain the whole file:
  *buffer = (char*)malloc(sizeof(char)*(numb_bytes_in_file+1));
  if(0x0 == *buffer) return 0x0;
  
  // copy the file into the buffer:
  const size_t numb_bytes_read = fread(*buffer,
				       sizeof(char),
				       numb_bytes_in_file,
				       fh);
  
  // paste in the 0 to indicate end of string
  (*buffer)[numb_bytes_in_file] = 0x0;
  
  // insanity check
  printf("numb_bytes_read=%ld\n", numb_bytes_read);
  printf("numb_bytes_in_file=%ld\n", numb_bytes_in_file);
  if(numb_bytes_read != numb_bytes_in_file) {
    free(*buffer);
    *buffer = 0x0;
    return 0x0;
  }
  
  // success!!  cleanup and exit.  User is responsible
  // for freeing the buffer.
  fclose(fh);
  return *buffer;
}
  


