/* recognize tokens for the calculator and pront them out */
%%
"+"     { printf("PLUS\n"); }
"-"     { printf("MINUS\n"); }
"*"     { printf("TIMES\n"); }
"/"     { printf("DIVIDE\n"); }
[0-9]+  { printf("NUMBERS %s \n", yytext); }
\n      { printf("NEWLINE\n"); }
[/t]    { }
.       { printf("Mystery character %s\n", yytext); }
%%
