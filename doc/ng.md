#  New Grammatical Formalism

Just researching around, seeing if I can come up with some extention
to RE's which is faster to parse than PEGs, but is as useful.


##  A subset of context free grammars which is equivalent to regular expressions

Our goal is to have something which has efficiency as close as
possible to regular languages, but with expressivity as close as
possible to context-free langauges.  Therefore, a good point of
departure is the subset of context-free languages which generates the
same set of languages as regular expressions do.


###  Here is a handy set:

1.  Set of Nonterminal Symbols.  We denote these using strings which
    could be C variables, e.g. S, T, expr.  We will usually start
    these with an upper-case letter to make them stand out as
    nonterminals.

2.  Set of Terminal symbols.  These wil be quoted strings.  Quotation
    works as in shell quotation, e.g. '"' is the nonterminal ", "'" is
    the nonterminal ', etc.  The empty string ("" or '') is also
    terminal symbol.
    
3.  Set of productions of the forms:
    a.  Nonterminal -> "terminal"
    b.  Nonterminal1 -> "terminal" Nonterminal2

4.  A distinguished Nonterminal, S -- for "start".  


### Implementation as a NFA:

1.  For each non-terminal which figures in the productions, there is a
    state.

2.  In addition, there is a distinguished state called T (for
    "termination") which does not not figure in the productions.

3.  For each production of the form:
    A -> "a" B
    We introduce an arc from state A to state B which consumes "a"
    when traversing it.

4.  For each production of the form:
    A -> "a"
    We introduce an arc from state A to state T, which consumes "a"
    when traversing it.


## First steps towards a more powerful formalism: Syntacic sugar

First some easy extensions which are very useful, but don't increase
the expressivity of the grammar at all.


### using a r.e. instead of a single non-terminal

One interesting first step would be to observe that we could use any r.e.
instead of a nonterminal in the productions.

Easy proof: just construct the nfa corresponding to the r.e., and then 
paste it into the NFA you are construcitng.


A -> /[a-z]+[a-z0-9_]*/ B


However, we might could get some implementation ease and efficienty by
consideirng special cases of the above first....


##  Recognizing a literal.

    S -> "foobar"  


We can have a string of non-terminals instead of just one non-terminal.  This can be translated to:

   S -> "f"A1,  A1->"o"A2, A2 -> "o"A3, etc

but we might be able to make it even faster than that.  


##  Accepting any single character.

    S -> .

   Honestly, I don't know if I can assimilate this or not.  Is it really needed?
   



#  Super-ultra-fast implementation of nondeterministic state transitions!


Basic idea:  lexicographic ordering of strings makes it possible to repreent
the transition out of one state to the other with an interval tree.


    [00 ------------- FF)  represents the entire space


Suppose we have a production like:

     A -> [0-9] B


We can add 1 to the last byte of any UTF-8 string, and get a value we can make an open-ended interval with.


    [00------30)[30-----39)[39---------FF)
                     B


Now say we do:

     S -> "12" C


    [00------30)[30----------------39)[39---------FF)
                     B

                  [3132---3133)
                        C


    [00------30)[30---3132)[3132----3133)[3133---------39)[39---------FF)
                    B            B               B
                                 C

