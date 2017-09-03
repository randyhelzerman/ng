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



#  Super-ultra-fast implementation of nondeterministic state transitions!


Basic idea:  lexicographic ordering of strings makes it possible to repreent
the transition out of one state to the other with an interval tree.


    [00 ------------- FF)  represents the entire space

## e.g. using . to match any single character,

      A -> . B
      


Suppose we have a production like:


We can add 1 to the last byte of any UTF-8 string, and get a value we can make an
open-ended interval with.


    [00------30)[30-----39)[39---------FF)
                    B-1


Now say we do:

     S -> "12" C


    [00------30)[30----------------39)[39---------FF)
                     B

                  [3132---3133)
                        C


    [00------30)[30---3132)[3132----3133)[3133---------39)[39---------FF)
                    B-1          B-1             B-1
                                 C-2

# negated bracket expressions:

A -> [^abc] B

   [00---'a')['d'----FF)



##  null transitions

How to handle producitons with an empty string of nonterminals?

     A->""B

     B->"c"C
     B->"d"D
     B->"e"E       c
                 ---- C
                / d
       A-----> B ---- D
                \  e
                 ---- E


Well, I can do it.  If the markers get pushed into a priority queue, and we
pull them off only when the string position is reached, that will work.

Represent them as an interval with FF as the first boundary?

[FF-----FF)

##  Probably faster alternative -- rule normalization

Its probably faster just t pre-process the rules.
    
     A->""B
     
     B->"c"C
     B->"d"D
     B->"e"E       

just becomes

     A->"c"C
     A->"d"D
     A->"e"E       

This seems a lot better.  Then there is just one char in the interval, one state as the
color, etc.  

Problem is that when we annotate the rule for extractig substrings, callimg
proceedures, etc, it might be problematic.



#  Extracting substrings


What would a syntax look like?


##  For base language, normalized rule form:

A -> a A
A ->

The only string we can extract from a rule would be its non terminal, if any.

A -> a A  { print a }
A -> a B

B -> b B
B -> 

once we allow non-recursive subrules, things could get more interesting.

A -> a A
A ->

B -> A C

C -> b C
C ->

we could annnotate the rule as follows:

B -> A>the_as  C  { print the_as }

##  When do we extract the string?  When do we execute the print?"

There can be many differnt threads working at once here.


One idea: postpone exrtraction of strings and callig of actions
until the entire string is parsed.

Amother idea: postpone them until there is only one 
thread still active.

If we are using this nfa to process an event loop, for example,
the latter could be the right thing to do.

B -> A>the_as  C  { yield the_as }


Yield makes it easy to make grammars which parse the
output of other grammars.

B -> A>the_as  C  { yield ('A from B', the_as) }

put a little type on it to tell the upper parser what it is.

I want theske to be flow coetrol statememts, like 
while.


**  Next ultra-cool idea

Use the other parser which is in prolog! The expression parser.

Its just a simple enhancement of the infix-to-postfix algorithm.

### syntax is the only thing which needs to be workedout....

Specify tokens with re's

PLUS -> "+"
MINUS -> "-"

LPAREN -> "("
RPAREN -> ")"

Then give them a precidence and associativity:

:-op(800,xfy,PLUS)


lol yeah right. I still don't know a good way to do this.


###  Relationship with CCG

     (E/E)\E

((1 + 2) + 3)


E    (E/E)\E   E     (E/E)\E  E

1        +     2         +    3


Weeeeelll.....


E = E  < + E


### Prolog operator precidence table


Priority     Specifier      Operators
-------------------------------------
1200          xfx           :-   -->
1200           fx           :-   ?-
1100          xfy           ;
1050          xfy           ->
1000          xfy           ,
 900           fy           \+   (proposed)
 700          xfx           = \= == \== @<  @=<   @>   @>=   is   =:=  =\
 	      		     =  < =< >  >= =..
 500          yfx           +  -  /\    \/
 400          yfx           *  /  //  rem mod << >>
 200          xfx           **
 200          xfy           ^
 200           fy           \  -
 100          xfx           @
  50          xfx           :


Terms which are not operators have priority 0

To avoid the need for unlimited lookahed, the same atom cannot be both
an infix operator and a postfix operator.


### better syntax?

Its hard to think there would be a better way to do it. :(
Prolog has been beaten up for 40 years now.

But I don't like it.  I've been programming in prolog for 30 years
and I still have to look up what yfx means.

<PRE>
	
ADD -> "+"  :  E <- (E + E) + E     # Addition 
SUB -> "-"  :  E <- (E - E) - E     # Subtraction
 
MUL -> "*"  :  E <- (E * E) * E     # Multiplication
DIV -> "/"  :  E <- (E / E) / E     # Division

EXP -> "^"  :  E <- E ^ (E ^ E)     # Exponentiation

NEG -> "-"  :  E <- -(-E)           # unary minus
</PRE>


<PRE>

COLON   --> ':'   :   E\E/E            # :

AT      --> '@'   :   E\E/E            # @

UMINUS  --> '-'   :   E/E              # -
BSLASH  --> '\'   :   E/E              # \
BNEG    --> '~'   :   E/E              # bitwise negation
LNEG    --> '!'   :   E/E              # logical negation
EXP     --> "^"   :  E\(E/E)           # Exponentiation
SSTAR 	--> "**"  :  E\(E/E)           # Star Star

MUL     --> "*"   :  (E\E)/E           # Multiplication
DIV     --> "/"   :  (E\E)/E           # Division
FFSLASH --> "//"  :  (E\E)/E           # two forward slashes
REM     --> "rem" :  (E\E)/E           # Remainder
MOD     --> "mod" :  (E\E)/E           # modulo
MOD     --> "%"   :  (E\E)/E           # modulo
LSHIFT  --> "<<"  :  (E\E)/E           # bitwise left shift
RSHIFT  --> ">>"  :  (E\E)/E           # bitwise right shift
BAND    --> "&"   :  (E\E)/E           # bitwise AND
LAND    --> "&&"  :  (E\E)/E           # logical AND

ADD     --> "+"   :  (E\E)/E           # Addition
SUB     --> "-"   :  (E\E)/E           # Subtraction
BOR     --> "|"   :  (E\E)/E           # bitwise OR
LOR     --> "||"  :  (E\E)/E           # logical OR

GT      --> ">"   :  E\E/E             # greater than
LT      --> "<"   :  E\E/E             # less than
GE      --> "=>"  :  E\E/E             # greater than
LE      --> "<="  :  E\E/E             # less than
 
ASN     --> "="   :  E\E/E             # asignment
EEQ     --> "=="  :  E\E/E             # equal equal

COMMA   --> ","   :  E\(E/E)           # comma

RARROW  --> "->"  :  E\(E/E)           # right arrow
LARROW  --> "<-"  :  E\(E/E)           # right arrow

PROD    --> "-->" :  P\N/T/N           # production

COLON   --> ':'   :   UKV\K/V          #  Unordered key-value pair
PROD    --> "->"  :   OKVE\K/V         #  ordered key-value pair

</PRE>


  (E\E)/E     (E\E)/E
E          E          E  
2    +     3    *      5

  (E\E)/E  
E            E 
2    +     (3*5)


  (E\E)/E      E\(E/E)
E           E           E  
2    +      3     ^     2    


#  Can I just jump to one for each interval?


A --> 'a'B
A --> 'a'C

Can I merge B and C?  well, if nobody feeds into B and C, sure.

But if we do, we could 

D --> 'x'B
E --> 'y'C




* Memory layout


a-1 : 35
b-3 : 10
c-2 : 6







