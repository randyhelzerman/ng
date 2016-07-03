#  New Grammatical Formalism

Just researching around, seeing if I can come up with some extention
to RE's which is faster to parse than PEGs, but is as useful.


##  A subset of context free grammars which is equivalent to regular
    expressions

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


## first steps towards a more powerful formalism: Syntacic sugar


