%{
    #include "parser.tab.h"
    #include "storetokens.hh"
%}

digit                           [0-9]
letter                          [a-zA-Z_]
whitespace                      [ \t\n\r]
operator                        [-+*/]
delimiter                       [,;?:{}()]

%%

{whitespace}                    ;

"do"                            { store_token_name("DO", yytext, yylineno); return DO; }
"if"                            { store_token_name("IF", yytext, yylineno); return IF; }
"else"                          { store_token_name("ELSE", yytext, yylineno); return ELSE; }
"float"                         { store_token_name("FLOAT", yytext, yylineno); return FLOAT; }
"int"                           { store_token_name("INTEGER", yytext, yylineno); return INTEGER; }
"print"                         { store_token_name("PRINT", yytext, yylineno); return PRINT; }
"return"                        { store_token_name("RETURN", yytext, yylineno); return RETURN; }
"void"                          { store_token_name("VOID", yytext, yylineno); return VOID; }
"while"                         { store_token_name("WHILE", yytext, yylineno); return WHILE; }

"<"                             { store_token_name("LESS_THAN", yytext, yylineno); return LESS_THAN; }
"<="                            { store_token_name("LESS_THAN_EQUAL", yytext, yylineno); return LESS_THAN_EQUAL; }
">"                             { store_token_name("GREATER_THAN", yytext, yylineno); return GREATER_THAN; }
">="                            { store_token_name("GREATER_THAN_EQUAL", yytext, yylineno); return GREATER_THAN_EQUAL; }
"=="                            { store_token_name("EQUAL", yytext, yylineno); return EQUAL; }
"!="                            { store_token_name("NOT_EQUAL", yytext, yylineno); return NOT_EQUAL; }
"&&"                            { store_token_name("AND", yytext, yylineno); return AND; }
"||"                            { store_token_name("OR", yytext, yylineno); return OR; }
"!"                             { store_token_name("NOT", yytext, yylineno); return NOT; }

"="                             { store_token_name("ASSIGN_OP", yytext, yylineno); return ASSIGN; }
{operator}                      { store_token_name("ARITHOP", yytext, yylineno); return (int) yytext[0]; }
{delimiter}                     { store_token_name("META CHAR", yytext, yylineno); return (int) yytext[0]; }

{letter}({letter}|{digit})*     { store_token_name("NAME", yytext, yylineno); yylval.string_value = new std::string(yytext); return NAME; }
{digit}+\.{digit}*              { store_token_name("FNUM", yytext, yylineno); yylval.double_value = atof(yytext); return DOUBLE_NUMBER; }
{digit}+                        { store_token_name("NUM", yytext, yylineno); yylval.integer_value = atoi(yytext); return INTEGER_NUMBER; }

"//".*                          ;
.                               { printf("cs316: Error: in scanner at Line: %d\n", yylineno); exit(1); }

%%
