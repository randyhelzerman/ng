#  Coding Guidlines

#  C

1.  Yes, C.  For Portability and small binary.
2.  C should be compilable both by a C compiler and a C++ compiler. Like Lua's source code.
2.  Brace style, As in the GNU C guildines
3.  Variable words are seperated by_underscores_like_this.  Because I'm not into the whole brevity thing.
4.  Everything prefixed with ng_.
5.  indentation is two spaces
6.  Try to keep lines shorter than 100 chars  
7.  In declarations/definitions, Stars go with the typename, not on the variable.e.g:
        void foo(int* p);
    not
        void foo(int *p);
8.  no tabs pls.
9.  Generic code is expressed with void*, not macros.
10.  Header files should have include guards and be able to be included in C++ files.   To this end they should be bracketed by an extern "C" statement like this:

      // include guard
      #ifndef NG_RB_TREE_NODE__H
      #define NG_RB_TREE_NODE__H

      // so we can include in C++ files
      #ifdef __cplusplus
      extern "C" {
      #endif

      ..... stuffs

      // end 
      #ifdef __cplusplus
      };
      #endif

      // end of include guard
      #endif

11. Every pointer should be checked to see if it is 0x0 before using.  In every code block where it is used.  After every time it could be modified.

# Commenting.

There is a philosophy which claims that it is not good to comment your code.  Reason being, the code will change, and its
hard to keep the comment in sync with the code.  Moreover, your code should be just so well-written that it is
transparently obvious what the code does, so comments really are not needed. There is much to be said for this 
philosophy.

However, it has two giant blind spots:

1.  header files
    a. naming conventions and descriptive names can help the reader understand what's going on
    b. but they are rarely enough.  There just isn't a lot of code there, so no matter how easy your code is to understand, it won't help somebody who only has accesss to your hnader files.
    c. Even if they have access to your .c files as well, they probalby are in a hurry and would appreciate a description of the functions.

2.  Normativity.
    a.  Suppose you are an awesome coder, who can always transparently and beautifully write code which is crystal-clear, and absolutely obvious what it does.
    b.  That *still* is not all the user needs to know about your code.
    c.  If somebody is debugging your code, they need to know two things:
        i.  What the code *should* be doing
	ii. What the code *aactually* does.

    d.  Code can only tell you what it actually does.  It cannot tell you what it *should* be doing.
    e.  For example, is this a bug?
        int a[10];
	for(int i=1;i<10;i++) {
	    a[i] = f(...);
	}
	
	It depends.  If the code *should* calculate a value for ever elmement of a[], then it is a bug.
	But if the code *shouldn't* claculate a value for a[0], then its not a bug.

English has two different verb modes to indicate this:
1.  my code does do x, y, and z....
2.  my code *should do* x, y, and z....

You should strive to make your code so transparently written that you don't need comments to express #1.

But no code can express #2.  Comment as much as possible about what your code *should* be doing.  Yeah,
its hard to keep these in sync with changing code.  Suck it up and do it anyways.


# Testing

We use google tests to test the code.  This has several implications:

1.  The google testing framework is in C++.  
2.  This is good, because it enforces us to make our header files includable in C++ source.
3.  Feel free to use any and all C++ code to make your tests.  
4.  Please keep the unit tests fast enough that we can invoke valgrind on all of them.


#  Struct Types

Since this is in C, we don't have the nice object facilities which C++ has.  So we define some
conventions to ape them to make C++ programmers feel more at home.


1.  Say we had a  a struct with which represents a node in an red black tree.    A good name for it would be "ng_rb_tree_node_t".  Since we probably
    want to be able to store anything in the red black tree, we represent the generic type as a void*.   E.g.:

     // represents a node in a red-black tree.
     typedef struct ng_rb_tree_node {
       struct ng_rb_tree_node*      parent_;      // parent node in the tree
       struct ng_rb_tree_node*      left_;        // left child
       struct ng_rb_tree_node*      right_;       // right child
       void*                        fruit_;       // the "fruit" i.e. the valuable thing which 
                                                  // is on the brances of the tree
     } ng_rb_tree_node_t;

2.  Note that field names of structs have a trailing _ in their names.


3.  It would have a constructor with a name like "ng_rb_tree_node_new",  which would return a ng_rb_tree_node_t*, and take as many arguments as it needed to initialize the type.

    // constructor
    ng_rb_tree_node_t* ng_rb_tree_node_new(ng_rb_tree_node_t* parent,
                                           ng_rb_tree_node_t* left,
					   ng_rb_tree_node_t* right,
					   void* fruit);
  

4.  It would have a destructor:
    a. The destructor would return void
    b. its first argument would be a pointer to a pointer to the object being deleted.  This is so we can zero out the pointer after we've freed the memory.
    c. Optionally, it can take a pointer to a function to delete the fruit.  If it does, the convention is that if
       the function pointer is non-null, it is invoked to delete the generic members of the struct.  e.g.

      // destructor
      void ng_rb_tree_node_delete(ng_rb_tree_node_t** selfp,
	                          void (*delete_fruit)(void**));


5.  It would have a function which dumps it out for debugging to stdout.  You are going to need this anyways, might as welll write it up front.


    void ng_rb_tree_node_dump(ng_rb_tree_node_t* self,
                              void (*fruit_dump)(void*));

6.  It would have a corresponding file "ng_rb_tree_node.t.cpp" in the unit test subdirectory, which would exercise each function and have a simple, fast test wehether it was correct.  Notice that a dumper function for a generic container might also take a dumper for the contained type in as a parameter.

7.  "Member" functions of a data structure should always have the name of the corresponding struct as their prefix. The variable which holds a pointer to the struct should be called "self".  e.g.  
           int ng_rb_tree_node_is_leaf(const ng_rb_tree_node_t* self);

8.  "Private" functions, i.e. functions which are used only internally and not really part of the api of the data structure 
    a.  Have a trailing _ in their names. e.g.

           void ng_rb_tree_rotate_node_left_(ng_rb_tree_node_t* node);

    b.  They are also declared in the header file, even though it is discouraged for users of the data structure to call them.  This is just to make it easier to unit test them.
 
9.  Conversly, the "public" api functions should never have a trailing _ in their names.



#  Most important rule.

Break any of these rules, rather than do something outright barbarious.  -G.W. Orwell.
