%{
	#include <iostream>
	#include <string>
	using namespace std;

	extern int yylineno;

	extern "C" void yyerror(string msg);
	extern int yylex(void);

	Symbol_Table* local_symbol_table;
	Table_Scope current_scope = global;
	bool ast_error = false;
%}

%union {
	int 	integer_value;
	double  double_value;
	string  *string_value;

	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;
}

%token  				AND
%token  				ASSIGN
%token  				DO
%token	<double_value>  DOUBLE_NUMBER
%token  				ELSE
%token  				EQUAL
%token  				FLOAT
%token  				GREATER_THAN
%token  				GREATER_THAN_EQUAL
%token  				IF
%token	 				INTEGER
%token	<integer_value> INTEGER_NUMBER
%token  				LESS_THAN
%token  				LESS_THAN_EQUAL
%token  <string_value>  NAME
%token 					NOT
%token  				NOT_EQUAL
%token  				OR
%token					PRINT
%token  				VOID
%token  				WHILE

%nonassoc "then" 
%nonassoc ELSE
%right '?' ':'
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_EQUAL GREATER_THAN_EQUAL
%left '+' '-'
%left '*' '/'
%right NOT
%right UMINUS



%type	<ast_list>		statement_list optional_statement_list
%type	<ast>			variable constant expression conditional_statement assignment_statement sequence while_statement do_while_statement if_statement if_else_statement statement_list_basic1 statement_list_basic print_statement
%type	<symbol_table>	integer_variable_list float_variable_list declaration variable_declaration variable_declaration_list optional_variable_declaration_list
%type	<procedure>		procedure

%start program


%%

program:
	optional_variable_declaration_list {
		program_object.set_global_table( *$1);
		current_scope = local;
	}
	procedure {
		program_object.set_procedure($3, yylineno);
		current_scope = global;
	}
;


procedure:
	VOID NAME '(' ')' '{' optional_variable_declaration_list {
		local_symbol_table = $6;
	}
	optional_statement_list '}' {
		if (ast_error) exit(1);
		$$ = new Procedure(void_data_type, *$2, yylineno);
		$$->set_local_list( *$6);
		$$->set_ast_list( *$8);
	}
;


/* Declarations */

optional_variable_declaration_list:
	/* empty */ {
		$$ = new Symbol_Table();
		$$->set_table_scope(current_scope);
	}
|	variable_declaration_list {
		$$ = $1;
	}
;

variable_declaration_list:
	variable_declaration { $$ = $1; }
|	variable_declaration_list variable_declaration {
		$$ = $1;
		$$->append_list( *$2, yylineno);
	}
;

variable_declaration:
	declaration ';' { $$ = $1; }
;

declaration:
	INTEGER integer_variable_list { $$ = $2; }
|	FLOAT	float_variable_list { $$ = $2; }
;

integer_variable_list:
	NAME {
		$1->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$1, int_data_type, yylineno);
		variable->set_symbol_scope(current_scope);
		
		$$ = new Symbol_Table();
		$$->set_table_scope(current_scope);
		$$->push_symbol(variable);
	}
|	integer_variable_list ',' NAME {
		$3->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$3, int_data_type, yylineno);
		variable->set_symbol_scope(current_scope);

		$$ = $1;
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(current_scope);
		temp_table->push_symbol(variable);
		$$->append_list( *temp_table, yylineno);
	}
;

float_variable_list:
	NAME {
		$1->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$1, double_data_type, yylineno);
		variable->set_symbol_scope(current_scope);
		
		$$ = new Symbol_Table();
		$$->set_table_scope(current_scope);
		$$->push_symbol(variable);
	}
|	float_variable_list ',' NAME {
		$3->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$3, double_data_type, yylineno);
		variable->set_symbol_scope(current_scope);

		$$ = $1;
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(current_scope);
		temp_table->push_symbol(variable);
		$$->append_list( *temp_table, yylineno);
	}
;


/* Statements */

optional_statement_list:
	/* empty */ { $$ = new list<Ast *>(); }
|	statement_list { $$ = $1; }
;

statement_list_basic:
	sequence {$$ = $1;}

statement_list_basic1:
	assignment_statement { $$=$1; }
| 	while_statement { $$=$1; }
| 	do_while_statement { $$=$1; }
|	if_statement { $$=$1; }
|	if_else_statement { $$=$1; }
|	print_statement { $$=$1; }
;

statement_list:
	statement_list_basic {
		$$ = new list<Ast *>();
		$$->push_back($1);
	}
|	statement_list statement_list_basic {
		$$ = $1;
		$$->push_back($2);
	}
;

assignment_statement:
	variable ASSIGN expression ';' {
		$$ = new Assignment_Ast($1, $3, yylineno);
		if (!$$->check_ast()) ast_error = true;
	}
;

conditional_statement:
	expression LESS_THAN expression  { $$ = new Relational_Expr_Ast($1, less_than, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression LESS_THAN_EQUAL expression { $$ = new Relational_Expr_Ast($1, less_equalto, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression GREATER_THAN_EQUAL expression { $$ = new Relational_Expr_Ast($1, greater_equalto, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression EQUAL expression { $$ = new Relational_Expr_Ast($1, equalto, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression GREATER_THAN expression { $$ = new Relational_Expr_Ast($1, greater_than, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression NOT_EQUAL expression { $$ = new Relational_Expr_Ast($1, not_equalto, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	'(' conditional_statement ')' { $$ = $2; if (!$$->check_ast()) ast_error = true; }
|   conditional_statement AND conditional_statement { $$ = new Logical_Expr_Ast($1, _logical_and, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	conditional_statement OR conditional_statement  { $$ = new Logical_Expr_Ast($1, _logical_or, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	NOT conditional_statement { $$ = new Logical_Expr_Ast(NULL, _logical_not, $2, yylineno); if (!$$->check_ast()) ast_error = true; }
;

expression:
	variable { $$ = $1; }
|	constant { $$ = $1; }
|	'(' expression ')' { $$ = $2; }
|	'-' expression { $$ = new UMinus_Ast($2, NULL, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression '+' expression { $$ = new Plus_Ast($1, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression '-' expression { $$ = new Minus_Ast($1, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression '*' expression { $$ = new Mult_Ast($1, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
|	expression '/' expression {  $$ = new Divide_Ast($1, $3, yylineno); if (!$$->check_ast()) ast_error = true; }
| 	conditional_statement '?' expression ':' expression { $$ = new Conditional_Expression_Ast($1, $3, $5, yylineno); }
;

variable:
	NAME {
		$1->push_back('_');
		if (local_symbol_table->variable_in_symbol_list_check( *$1)) {
			$$ = new Name_Ast( *$1, local_symbol_table->get_symbol_table_entry( *$1), yylineno);
		}
		else if (program_object.variable_in_symbol_list_check( *$1)) {
			$$ = new Name_Ast( *$1, program_object.get_symbol_table_entry( *$1), yylineno);
		}
		else {
			yyerror("Variable has not been declared");
			exit(1);
		}
	}
;

constant:
	INTEGER_NUMBER {
		$$ = new Number_Ast<int>($1, int_data_type, yylineno);
	}
|	DOUBLE_NUMBER {
		$$ = new Number_Ast<double>($1, double_data_type, yylineno);
	}
;

if_statement:
	IF '(' conditional_statement ')' sequence %prec "then" {
		$$ = new Selection_Statement_Ast($3, $5, NULL, yylineno);
	}
;

if_else_statement:
	IF '(' conditional_statement ')' sequence
	ELSE sequence {
		$$ = new Selection_Statement_Ast($3, $5, $7, yylineno);
	}
;

while_statement:
	WHILE '(' conditional_statement ')' sequence {
		$$ = new Iteration_Statement_Ast($3, $5, yylineno, false);
	}
;

do_while_statement:
	DO sequence WHILE '(' conditional_statement ')' ';' {
		$$ = new Iteration_Statement_Ast($5, $2, yylineno, true);
	}
;

print_statement:
	PRINT variable ';' {
		$$ = new Print_Ast($2, yylineno);
	}
;

sequence:
	statement_list_basic1 {
		auto seq = new Sequence_Ast(yylineno);
		seq->ast_push_back($1);
		$$ = seq;
	}
|	'{' statement_list '}' {
		auto seq = new Sequence_Ast(yylineno);
		for (const auto &child_ast: *$2) {
			seq->ast_push_back(child_ast);
		}
		$$ = seq;
	}
;

%%

void yyerror(string msg) {
	cout << "cs316: Error: Line: " << yylineno << ": " << msg << endl;
}
