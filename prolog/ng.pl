:- discontiguous(make_it_stop/2).

%  dirt poor man's lambda calculs substitue.  Lame.  Come on prolog, in
%  45 years you couldn't do better than this??

% apply arguments to a function and execute it
apf(F,I, O)        --> [], { F=..FL1, append(FL1,[I,        O],  FL2),  FX=..FL2,   FX  }.
apf(F,I1,I2, O)    --> [], { F=..FL1, append(FL1,[I1,I2,    O],  FL2),  FX=..FL2,   FX  }.
apf(F,I1,I2,I3, O) --> [], { F=..FL1, append(FL1,[I1,I2,I3, O],  FL2),  FX=..FL2,   FX  }.


% apply arguments to a parser and parse with it
app(P,          O)  --> { P=..PL1, append(PL1, [          O], PL2), PX=..PL2 },  PX.
app(P,I,        O)  --> { P=..PL1, append(PL1, [I,        O], PL2), PX=..PL2 },  PX.
app(P,I1,I2,    O)  --> { P=..PL1, append(PL1, [I1,I2,    O], PL2), PX=..PL2 },  PX.
app(P,I1,I2,I3, O)  --> { P=..PL1, append(PL1, [I1,I2,I3, O], PL2), PX=..PL2 },  PX.


% Make a terminal expresion optional


% Pass up the return value of the parser if it was choosen, otherwise
% pass up the default value
opt( P, _V, O)  -->  app(P, O).
opt(_P,  O, O)  -->  [].


% return one or the other
alt(P,_Q, O)  --> app(P,O).
alt(_P,Q, O)  --> app(Q,O).


% use F to combine results of individual parsers; return D on empy
star( P,  F,D,  O)   -->   app(P, O1),  star(P, F,D, O2),  apf(F,O1,O2, O). 
star(_P, _F,O,  O)   -->   [].

% plus
plus( P,  F,D,  O)   -->   app(P, O1),  star(P, F,D, O2),  apf(F,O1,O2, O). 

% make a list.
% P -- parser for the thing we're making a list of
% D -- delimiter of the list

list(P,D, F, O)      -->  app(P,PO),   opt(list_ex(P,D, F,PO), PO, O).

list_ex(P,D, F,I, O) -->  app(D,O1),   list(P,D, F, O2), apf(F,O1,I,O2, O).


func_op(F,D, X,T, O)  :-  O =.. [F,D,X,T].

list_op(I, L, [I|L]).


% ----------------------------------------------------------------------

% whitespace

ws --> opt(ws_chars,[],_), !.

ws_chars(_) -->  star(ws_char, list_op,[], _).

ws_char(_) --> ` `  .
ws_char(_) --> `\t` .
ws_char(_) --> `\n` .

% strings

string_form(L,R, string_form(S,LO,RO)) -->
    app(L, LO),
    star(nd(L,R), string_form_list_op,[],  SLO),  apf(string_to_list, S, SLO),
    app(R, RO).

nd(L,R, O) --> \+ app(L,_), \+app(R,_), [O].

string_form_list_op(I, L, [I|L]).

string(O) --> string_form(single_quote,   single_quote,     O).
string(O) --> string_form(double_quote,   double_quote,     O).
string(O) --> string_form(left_big_paren, right_big_paren,  O).

single_quote(O)     -->  [O], {[O]=`'`}   .   make_it_stop     -->  `'`  .
double_quote(O)     -->  [O], {[O]=`"`}   .   make_it_stop     -->  `"`  .

left_big_paren( `--[` )  -->  `--[` .
right_big_paren(`]--`)   -->  `]--` .



% Terminal
terminal(O) --> list(terminal_atom_q,comma, func_op(terminal_exp), O).
comma(O)    -->  [O], {[O]=`,`} .


terminal_atom_q(quant(OQ,OT)) --> terminal_atom(OT), opt(quant,no_quantifier, OQ).

terminal_atom(O) --> string(O).
terminal_atom(O) --> range(O).
% terminal_atom(O) --> nonterminal(O).  % with caveat that it can't be recursive.

quant(O) --> [O], { [O]=`*` } .
quant(O) --> [O], { [O]=`+` } .
quant(O) --> [O], { [O]=`?` } .


range(range(RT, Rs)) --> `[`, opt(range_neg, positive_range, RT), plus(range_spec, list_op,[], Rs), `]` .

range_neg(negative_range) --> `^` .

range_spec(range_spec(L,H)) --> range_bound(L), { DH is L+1 }, opt(range_spec_ex,DH, H).

range_bound(X) --> [X], {[X] \= `-`, [X] \= `]`, [X] \= `]`, [X] \= `,`, [X] \= `^`}.
range_bound(S) --> string(S).

range_spec_ex(S2) -->
    alt(close_range_op, open_range_op,D),
    range_bound(S1), { S2 is S1+D }.

close_range_op(1) --> `-` .
open_range_op(0)  --> `--` .



id(O) -->
    alpha(C), apf(list_op, C,T, LO),
    star(alphanumeric_, list_op,[], T), apf(string_to_list,O,LO).

alpha(O) --> lowercase(O) ; uppercase(O).

alphanumeric_(O) --> alpha(O).
alphanumeric_(O) --> digit(O).
alphanumeric_(O) --> [O], { [O]=`_`}.

lowercase(O) --> [O], { [A]=`a`, [Z]=`z`,  A=<O,  O=<Z }.
uppercase(O) --> [O], { [A]=`A`, [Z]=`Z`,  A=<O,  O=<Z }.
digit(O)     --> [O], { [Z]=`0`, [N]=`9`,  Z=<O,  O=<N }.


% nonterminal -- tbd when we get the expression parser

nonterminal(nonterminal(S,Ps)) --> id(S), opt(template_params,[],Ps).  %, opt(type_spec,[],TS).

template_params(O) --> `<`, list(id,comma, func_op(param), O), `>` .

%type_spec() --> id(L), opt(application(Op), id(R)).
%type_spec() --> `(`, type_spec, `)` .
    
application() --> foreward_ap.
application() --> backward_ap.

foreward_ap('\\') --> `\\` .
backward_ap('/')  --> `/`  .

% productions

prod(prod(H,T,R)) -->
    ws, prod_head(H),
    ws, `-->` ,
    ws, prod_tail(prod_tail(T,R)).

prod_head(H) -->
    nonterminal(H).  % add type spec here.


prod_tail(prod_tail(T,R)) -->
    terminal(T), ws, opt(nonterminal, [], R).

% program
prog(S) --> star(prod, list_op,[], S), ws.

%------------------------------------------------------------------------
    
% testing
a --> `a` .
b --> `b` .
	      
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
