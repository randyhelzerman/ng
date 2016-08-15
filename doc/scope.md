Musings about scope-based garbage collection.


{
   var a
   var b
   var c

   {
      var d
      var e

      {
         var f
	 var g
      }
   }
}



What I want is some method of making this garbe collectgor to be scoped.

I want it to solve all my prooblems.  Lots of little segements, aging etc.

a = g

What would this do?  Transfer g to the scope of a?

What happens if we then do:

a = d


Does it go back to scope of g?   Here is the kicker, it looks like most assignments happen across
scopes.   I mean, why would you want two different names for the same thing in the same scope??? derp.



what if g just stays at its scope?  we know where to look for references when we clean it up, just
all the intersecing scopes?


how is that really different from just having a parent pointer in the scopes?  we really need
some better faster way.



Well the only thing is what if it gets assigned to some place which isn't in the scope family tree?

Or a disjoint part?



{
   var a
   var b
   var c

        proc1
        {
	   var d
	   var e
	}

        pro2
        {
	   var f
	   var g
	}
}


then somehow some ipc thing we set

     d = f

What if we just reference counted that?

Well....that should be good no?

There just isn't much here for that is there.  What to do about it?

If its returned, we just expand trhe interval to be the scope it was returned to


What about if we reference count every time that we assign to a higher scope?

I don't get it man. We need a pointer to every scope it is in somehow.

Crap.  Tasmic.  I don't see how this is an advance over just vanilla gc.


You know, if we had single assignment, we could do the prolog trick of path compression.

We can have it. In fact we are going to have it.  What does it buy us?

