% Make a terminal expresion optional

opt(_X) --> [].
opt(X)  --> X.

opt(_X,_Y) --> [].
opt(X,Y)   --> X,Y.


star(_X) --> [].
star(X) --> X, star(X).


% make a list.
list(X,D) -->  X, opt(D,star(X)).


% Strings
string_form(L,R) --> L, star(nd(L,R)), R.
nd(L,R) --> [X], { X \= L, X \= R }.

string --> string_form(single_quote,single_quote).
string --> string_form(double_quote,double_quote).
string --> string_form(left_big_paren, right_big_paren).


% Terminal
terminal --> list(terminal_atom_q, ',').

terminal_atom_q --> terminal_atom, opt(quant).

terminal_atom --> string.
terminal_atom --> range.
terminal_atom --> nonterminal.


range --> '[', opt(range_neg), star(range_spec).

range_neg --> ['^'].

range_spec --> range_bound, opt(range_spec_ex).

range_bound --> [X], {X \= '-', X \= ']', X \= ']', X \= ','}.
range_bound --> string.

range_spec_ex --> [','], range_bound.

id --> alpha, star(alphanumeric_).

alpha --> lowercase ; uppercase.

alphanumeric_ --> alpha ; digit; [_].

lowercase --> [X], 'a' =< X , X =< 'z'.
uppercase --> [X], 'A' =< X,  X =< 'Z'.
digit     --> [X], '0' =< X,  X =< '9'.

param_args --> ['<'], list(id), ['>'].

type_spec  --> [].

nonterminal --> id, opt(template_params), opt(type_spec).

% testing
a --> [a].
b --> [b].
comma --> [','].
single_quote --> [39].
double_quote --> ['\"'].
left_big_paren --> ['-', '-', '['].
right_big_paren --> [']', '-', '-'].

test :-
    test_string.


test_string :-
    test_empty_string.


test_empty_string :-
    string_to_list("''", L),
    string(L,[]),

    string_to_list([34,34],L1),
    string(L1,[]),

    string_to_lit("--[]--", L2),
    string(L2,[]).


	
