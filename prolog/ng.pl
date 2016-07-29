:- discontiguous(make_it_stop/2).

% Make a terminal expresion optional

% true means the option was taken. 
opt(F,I,O,   P) -->
    { PX =.. [P,X] },
    PX,
    { call(F,I,X, O) }.

opt(F,I,O,  P) --> [], { call(F,I,[], O) }.

opt(F,I,O,  P1, P2)  -->
    { PX1 =.. [P1, X1],
      PX2 =.. [P2, X2] },
    
    PX1,PX2,
    
    { call(F,I,X1,X2, O) }.

opt(F,I,O, _P1,_P2)  --> [], { call(F,I,[],[], O) }.


star(F,I,O2,   P)  -->
    { PX =.. [P,X] },
    PX,

    % combine input with P's output
    { call(F,I,X, O1) },

    % and recurse
    star(F,O1,O2, P).

star(F,I,O,  _X)  --> [],         { call(F,I,[], O) }.

% make a list.
%list(F,I,O, L) -->  X, opt(O, D,star(X)).


% Strings
string_form(L,R) --> L, star(nd(L,R)), R.
nd(L,R) --> [X], { X \= L, X \= R }.

string() --> string_form(single_quote,   single_quote).
string() --> string_form(double_quote,   double_quote).
string() --> string_form(left_big_paren, right_big_paren).


% Terminal
terminal() --> list(terminal_atom_q, comma).

terminal_atom_q() --> terminal_atom(), opt(quant).
 
terminal_atom() --> string().
terminal_atom() --> range().
terminal_atom() --> nonterminal().

quant() --> `*` .
quant() --> `+` .
quant() --> `?` .


range()--> `[`, opt(range_neg), star(range_spec), `]` .

range_neg() --> `^` .

range_spec() --> range_bound, opt(range_spec_ex).

range_bound() --> [X], {[X] \= `-`, [X] \= `]`, [X] \= `]`, [X] \= `,`}.
range_bound() --> string.

range_spec_ex() --> `,`, range_bound().

id(O) -->
    alpha(O1),                          { L = [O1|T1] },
    star(list_op,T1,[], alphanumeric_), { string_to_list(O,L) }.

alpha(O) --> lowercase(O) ; uppercase(O).

alphanumeric_(O) --> alpha(O).
alphanumeric_(O) --> digit(O).
alphanumeric_(O) --> [O], { [O]=`_`}.

lowercase(O) --> [O], { [A]=`a`, [Z]=`z`,  A=<O,  O=<Z }.
uppercase(O) --> [O], { [A]=`A`, [Z]=`Z`,  A=<O,  O=<Z }.
digit(O)     --> [O], { [Z]=`0`, [N]=`9`,  Z=<O,  O=<N }.

nonterminal() --> id, opt(template_params), opt(type_spec).

template_params() --> `<`, list(id,comma), `>` .

%type_spec() --> id(L), opt(application(Op), id(R)).
%type_spec() --> `(`, type_spec, `)` .
    
application() --> foreward_ap.
    application() --> backward_ap.
    
foreward_ap('\\') --> `\\` .
backward_ap('/') --> `/` .

% useful combining functions

no_op( I,_X, I).

up_op(_I, X, X).

list_op(T1,X,  T2) :-
    ( []=X
     -> T2 = T1
     ;
     T1=[X|T2]
    ).

% testing
a --> `a` .
b --> `b` .
	      
comma()         -->  `,` .

single_quote()     -->  `'`   .   make_it_stop     -->  `'`  .
double_quote()     -->  `"`   .   make_it_stop     -->  `"`  .


left_big_paren()   -->  `--[` .
right_big_paren()  -->  `]--` .

    
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
