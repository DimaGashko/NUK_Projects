teach(syslov, ds).
teach(makarova, programming).
teach(gayda, oop).
study(ivan, ds).
study(marina, programming).
study(marina, oop).
study(petro, ds).
study(petro, oop).

teaches(P,S) :- teach(P,C), study(S,C).
