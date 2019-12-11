%Jane and Alan - Alex and Josh; Alexa and Kim - Alan; Jady and Jack - Kim
%       Alex and Josh
% -Jane              Alan
%             Alexa         Kim
%                      Jady       Jack

mom(jane, alex).
mom(alexa, alan).
mom(jady, kim).
mom(jane, josh).
dad(alan, alex).
dad(alan, josh).
dad(kim, alan).
dad(jack, kim).

% X is Y's brother or sister
sibling(X, Y) :- mom(Mom, X), mom(Mom, Y), 
   dad(Dad, X), dad(Dad, Y), X \= Y.

% X is Y's dad
grandfather(X, Y) :- dad(X, D), dad(D, Y).