%{
	#include <iostream>
	#include <string>
	using namespace std;

	extern int yylineno;

	extern "C" void yyerror(string msg);
	extern int yylex(void);

	Symbol_Table* local_symbol_table;
	Symbol_Table* formal_symbol_table;
	string proc_name;
	bool ast_error = false;
	bool in_decl = true;
%}

%union {
	int 	integer_value;
	double  double_value;
	string  *string_value;

	list<Ast *> * ast_list;
	Ast * ast;
	Call_Ast * call_ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	list<Symbol_Table_Entry *> * symbol_list;
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
%token					RETURN

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
%right "uminus"



%type	<ast_list>		statement_list optional_statement_list call_param_list optional_call_param_list
%type	<ast>			variable constant expression conditional_statement assignment_statement return_statement
%type   <ast> 			sequence while_statement do_while_statement if_statement if_else_statement
%type 	<ast> 			statement_list_basic print_statement statement_list_basic1
%type   <call_ast>		function_call
%type	<symbol_table>	integer_variable_list float_variable_list declaration variable_declaration 
%type 	<symbol_table> 	optional_variable_declaration_list optional_variable_function_declaration_list
%type 	<symbol_table>	optional_fun_param_list
%type   <symbol_entry>	fun_param_declaration
%type   <symbol_list>	fun_param_list
%type	<procedure>		function_signature

%start program


%%

program:
	optional_variable_function_declaration_list
	procedure_definition_list {
		if(!program_object.is_procedure_exists("main")) {
			yyerror("main not defined");
			exit(1);
		}
	}
;

procedure_definition_list:
	procedure_definition
|	procedure_definition_list procedure_definition
;

procedure_definition:
	function_signature
	'{' optional_variable_declaration_list {
			local_symbol_table = $3;
			$1->set_local_list( *$3);
		}
		optional_statement_list '}' {
			$1->set_ast_list( *$5);
			$1->set_proc_is_defined();
		}
;


function_signature:
	VOID NAME '(' optional_fun_param_list ')' {
			if ( *$2 != "main") {
				$2->push_back('_');
			}
			formal_symbol_table = $4;
			$$ = new Procedure(void_data_type, *$2, yylineno);
			$$->set_formal_param_list( *$4);
			proc_name = *$2;
			program_object.set_proc_to_map(proc_name, $$);
		}
|	INTEGER NAME '(' optional_fun_param_list ')' {
			if ( *$2 != "main") {
				$2->push_back('_');
			}
			formal_symbol_table = $4;
			$$ = new Procedure(int_data_type, *$2, yylineno);
			$$->set_formal_param_list( *$4);
			proc_name = *$2;
			program_object.set_proc_to_map(proc_name, $$);
		}
|	FLOAT NAME '(' optional_fun_param_list ')' {
			if ( *$2 != "main") {
				$2->push_back('_');
			}
			formal_symbol_table = $4;
			$$ = new Procedure(double_data_type, *$2, yylineno);
			$$->set_formal_param_list( *$4);
			proc_name = *$2;
			program_object.set_proc_to_map(proc_name, $$);
		}
;

fun_param_list:
	fun_param_declaration { $$ = new list<Symbol_Table_Entry *>; $$->push_front($1); }
|	fun_param_declaration ',' fun_param_list {
		$$ = $3;
		if ($1->get_variable_name() != "") {
			$$->push_front($1);
		}
	}
;

fun_param_declaration:
	INTEGER NAME {
		$2->push_back('_');
		$$ = new Symbol_Table_Entry( *$2, int_data_type, yylineno);
		$$->set_symbol_scope(formal);
	}
|	FLOAT NAME {
		$2->push_back('_');
		$$ = new Symbol_Table_Entry( *$2, double_data_type, yylineno);
		$$->set_symbol_scope(formal);
	}
|	INTEGER {
		if (!in_decl) {
			yyerror("Cannot parse the input program");
			exit(1);
		}
		$$ = new Symbol_Table_Entry( *(new string("")), int_data_type, yylineno);
		$$->set_symbol_scope(formal);
	}
|	FLOAT {
		if (!in_decl) {
			yyerror("Cannot parse the input program");
			exit(1);
		}
		$$ = new Symbol_Table_Entry( *(new string("")), double_data_type, yylineno);
		$$->set_symbol_scope(formal);
	}
;

/* Declarations */

optional_variable_function_declaration_list:
	/* empty */ {
		$$ = new Symbol_Table();
		$$->set_table_scope(global);
		program_object.set_global_table( *$$);
	}
|	optional_variable_function_declaration_list variable_declaration {
		$$ = $1;
		$$->append_list( *$2, yylineno);
		program_object.set_global_table( *$$);
	}
|	optional_variable_function_declaration_list function_declaration {
		$$ = $1;
	}
;

function_declaration:
	function_signature ';'
;


optional_variable_declaration_list:
	/* empty */ {
		$$ = new Symbol_Table();
		$$->set_table_scope(local);
	}
|	optional_variable_declaration_list variable_declaration {
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
		variable->set_symbol_scope(local);
		
		$$ = new Symbol_Table();
		$$->set_table_scope(local);
		$$->push_symbol(variable);
	}
|	integer_variable_list ',' NAME {
		$3->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$3, int_data_type, yylineno);
		variable->set_symbol_scope(local);

		$$ = $1;
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(local);
		temp_table->push_symbol(variable);
		$$->append_list( *temp_table, yylineno);
	}
;

float_variable_list:
	NAME {
		$1->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$1, double_data_type, yylineno);
		variable->set_symbol_scope(local);
		
		$$ = new Symbol_Table();
		$$->set_table_scope(local);
		$$->push_symbol(variable);
	}
|	float_variable_list ',' NAME {
		$3->push_back('_');
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *$3, double_data_type, yylineno);
		variable->set_symbol_scope(local);

		$$ = $1;
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(local);
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
|  	return_statement { $$=$1; }
| 	function_call ';' { $$=$1; }
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

return_statement:
	RETURN ';' {$$ = new Return_Ast(NULL,proc_name,yylineno);}
|	RETURN expression ';' {$$ = new Return_Ast($2,proc_name,yylineno);}
;

assignment_statement:
	variable ASSIGN expression ';' {
		$$ = new Assignment_Ast($1, $3, yylineno);
		if (!$$->check_ast()) ast_error = true;
	}
|	variable ASSIGN function_call ';' {
		$$ = new Assignment_Ast($1, $3, yylineno);
		if (!$$->check_ast()) ast_error = true;
	}
;

function_call:
	NAME '(' optional_call_param_list ')' {
		$1->push_back('_');
		if(!program_object.is_procedure_exists( *$1)) {
			yyerror("no function exists");
			exit(1);
		}
		$$ = new Call_Ast( *$1, yylineno);
		$$->set_actual_param_list( *$3);
	    $$->check_actual_formal_param(program_object.get_procedure_prototype( *$1)->get_formal_param_list());
	}
;

optional_call_param_list:
	/* empty */ {$$ = new list<Ast *>();}
|	call_param_list { $$ = $1;}

call_param_list:
	expression {
		$$ = new list<Ast *>();
		$$->push_front($1);
	}
|	call_param_list ',' expression {
		$$ = $1;
		$$->push_front($3);
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
|	'-' expression %prec "uminus" { $$ = new UMinus_Ast($2, NULL, yylineno); if (!$$->check_ast()) ast_error = true; }
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
		else if (formal_symbol_table->variable_in_symbol_list_check( *$1)) {
			$$ = new Name_Ast( *$1, formal_symbol_table->get_symbol_table_entry( *$1), yylineno);	
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

optional_fun_param_list:
	/* empty */ {
		$$ = new Symbol_Table();
		$$->set_table_scope(formal);
	}
|	fun_param_list {
		$$ = new Symbol_Table();
		$$->set_table_scope(formal);
		for (auto &entry: *$1) {
			if ($$->variable_in_symbol_list_check(entry->get_variable_name())) {
				yyerror("Variable is declared twice");
				exit(1);
			}
			$$->push_symbol(entry);
		}
	}
;


%%

void yyerror(string msg) {
	cout << "cs316: Error: Line: " << yylineno << ": " << msg << endl;
}
