%option noyywrap
%option nounput
%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include "formula.hpp"

using namespace std;

// Including header where tokens are defined
#include "interactive_deduction.tab.hpp"

%}

%%
True                        { return true_token; }
False                       { return false_token; }
[a-zA-Z]([a-zA-Z_])*        {  
                              yylval.s = new string(yytext);
                              return atom_token;
                            }
"~"                         { return not_token; }
"/\\"                       { return and_token; }
"\\/"                       { return or_token; }
"==>"                       { return imp_token; }
"<=>"                       { return iff_token; }
[()\n]                      { return *yytext; }
[ \t]                       { }
.                           {
                              fprintf(stderr, "Lexical error: unknown character %c\n", *yytext);
                              exit(EXIT_FAILURE);
                            }
%%