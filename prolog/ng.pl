% Make a terminal expresion optional

opt(_X) --> [].
opt(X) --> X.

opt(_X,_Y) --> [].
opt(X,Y) --> X,Y.


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




% testing
a --> [a].
b --> [b].
comma --> [','].
single_quote --> ['\''].
double_quote --> ['\"'].
left_big_paren --> ['-', '-', '['].
right_big_paren --> [']', '-', '-'].







