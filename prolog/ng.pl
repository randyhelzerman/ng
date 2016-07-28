:- discontiguous(make_it_stop/2).
 				  
% Make a terminal expresion optional

opt( X)  --> X.
opt(_X) --> [].

opt( X, Y)  --> X,Y.
opt(_X,_Y)  --> [].

star(X) --> X, star(X).
star(_X) --> [].

% make a list.
list(X,D) -->  X, opt(D,star(X)).


% Strings
string_form(L,R) --> L, star(nd(L,R)), R.
nd(L,R) --> [X], { X \= L, X \= R }.

string --> string_form(single_quote,single_quote).
string --> string_form(double_quote,double_quote).
string --> string_form(left_big_paren, right_big_paren).


% Terminal
terminal --> list(terminal_atom_q, comma).

terminal_atom_q --> terminal_atom, opt(quant).
 
terminal_atom --> string.
terminal_atom --> range.
terminal_atom --> nonterminal.

quant --> `*` .
quant --> `+` .
quant --> `?` .


range --> `[`, opt(range_neg), star(range_spec), `]` .

range_neg --> `^` .

range_spec --> range_bound, opt(range_spec_ex).

range_bound --> [X], {[X] \= `-`, [X] \= `]`, [X] \= `]`, [X] \= `,`}.
range_bound --> string.

range_spec_ex --> `,`, range_bound.

id --> alpha, star(alphanumeric_).

alpha --> lowercase ; uppercase.

alphanumeric_ --> alpha ; digit; `_`.

lowercase --> [X], { [A]=`a`, [Z]=`z`,  A=<X,  X=<Z }.
uppercase --> [X], { [A]=`A`, [Z]=`Z`,  A=<X,  X=<Z }.
digit     --> [X], { [Z]=`0`, [N]=`9`,  Z=<X,  X=<N }.

%nonterminal --> id, opt(template_params), opt(type_spec).
nonterminal --> id, opt(template_params), opt(type_spec).

template_params --> `<`, list(id,comma), `>` .

type_spec --> digit.


% testing
a --> `a` .
b --> `b` .
	      
comma            -->  `,`   .

single_quote     -->  `'`   .   make_it_stop     -->  `'`  .
double_quote     -->  `"`   .   make_it_stop     -->  `"`  .


left_big_paren   -->  `--[` .
right_big_paren  -->  `]--` .

    
test :-
    test_string,
    test_nonterminal.


test_string :-
    test_empty_string,
    test_some_strings.


test_empty_string :-
    string(`''`,[]),
    
    string(`""`,[]),
    
    string(`--[]--`,[]).


	
test_some_strings :-
    string(`'a'`,[]),

    string(`"'"`,[]),
    
    string(`--[yeah this is a lot of stuffs
	      whihc just keeps going on]--`,[]).


	
test_nonterminal :-
    nonterminal(`NONTERMINAL`,[]).
