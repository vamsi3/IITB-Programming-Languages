#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

// =============================================================================

void error(string msg, int lineno) {
    cout << "cs316: Error: File: " << "" << " Line: " << lineno << ": " << msg << endl;
}

// =================== Ast =====================================================

int Ast::labelCounter;

Ast::Ast() {
    this->node_data_type = void_data_type;
    this->ast_num_child = zero_arity;
    this->lineno = 0;
}

Ast::~Ast() {

}

Data_Type Ast::get_data_type() {
    return this->node_data_type;
}

void Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Ast::is_value_zero() {
    return false;
}

bool Ast::check_ast() {
    return true;
}

Symbol_Table_Entry & Ast::get_symbol_entry() {
    // empty
}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer) {
    // empty
}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env) {
    // empty
}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result) {
    // empty
}


// =================== Assignment_Ast ==========================================

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line) {
    this->lhs = temp_lhs;
    this->rhs = temp_rhs;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = void_data_type;
}

bool Assignment_Ast::check_ast() {
    auto ret = true;
    if (this->lhs->get_data_type() != this->rhs->get_data_type()) ret = false;
    if (!ret) error("Assignment statement data type not compatible", this->lineno);
    return ret;
}

void Assignment_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_SPACE << "Asgn:";
    file_buffer << endl << AST_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== Name_Ast ================================================

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line) {
    this->variable_symbol_entry = &var_entry;
    this->lineno = line;
    this->ast_num_child = zero_arity;
    this->node_data_type = var_entry.get_data_type();
}

Data_Type Name_Ast::get_data_type() {
    return this->node_data_type;
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry() {
    return *this->variable_symbol_entry;
}

void Name_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

void Name_Ast::print(ostream & file_buffer) {
    file_buffer << "Name : " << this->variable_symbol_entry->get_variable_name();
}


// =================== Number_Ast ==============================================

template <class T>
Number_Ast<T>::Number_Ast(T number, Data_Type constant_data_type, int line) {
    this->constant = number;
    this->lineno = line;
    this->ast_num_child = zero_arity;
    this->node_data_type = constant_data_type;
}

template <class T>
Number_Ast<T>::~Number_Ast() {

}

template <class T>
Data_Type Number_Ast<T>::get_data_type() {
    return this->node_data_type;
}

template <class T>
void Number_Ast<T>::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

template <class T>
bool Number_Ast<T>::is_value_zero() {
    return this->constant == 0;
}

template <class T>
void Number_Ast<T>::print(ostream & file_buffer) {
    file_buffer << "Num : " << this->constant;
}


// =================== Arithmetic_Expr_Ast =====================================

Data_Type Arithmetic_Expr_Ast::get_data_type() {
    return this->node_data_type;
}

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Arithmetic_Expr_Ast::check_ast() {
    auto ret = true;
    if (this->ast_num_child == binary_arity && this->lhs->get_data_type() != this->rhs->get_data_type()) ret = false;
    if (!ret) error("Arithmetic statement data type not compatible", this->lineno);
    return ret;
}


// =================== Plus_Ast ================================================

Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line) {
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void Plus_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_NODE_SPACE << "Arith: PLUS";
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== Minus_Ast ===============================================

Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line) {
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void Minus_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_NODE_SPACE << "Arith: MINUS";
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== Divide_Ast ==============================================

Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line) {
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void Divide_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_NODE_SPACE << "Arith: DIV";
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== Mult_Ast ================================================

Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line) {
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void Mult_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_NODE_SPACE << "Arith: MULT";
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== UMinus_Ast ==============================================

UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line) {
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = unary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void UMinus_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_NODE_SPACE << "Arith: UMINUS";
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
}


// ============= Conditional_Expression_Ast ====================================

Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* cond, Ast* l, Ast* r, int line) {
    this->cond = cond;
    this->lhs = l;
    this->rhs = r;
    this->lineno = line;
    this->ast_num_child = ternary_arity;
    this->node_data_type = this->lhs->get_data_type();
}

void Conditional_Expression_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_SPACE << "Cond:";
    file_buffer << endl << AST_NODE_SPACE << "IF_ELSE";
    this->cond->print(file_buffer);
    file_buffer << endl << AST_NODE_SPACE << "LHS ("; this->lhs->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_NODE_SPACE << "RHS ("; this->rhs->print(file_buffer); file_buffer << ")";
}


// =================== Print_Ast ===============================================

Print_Ast::Print_Ast(Ast *v, int line) {
    this->var = v;
}

void Print_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_SPACE << "Print :";
    file_buffer << endl << AST_SUB_NODE_SPACE << "("; this->var->print(file_buffer); file_buffer << ")";
}


// ==================== Relational_Expr_Ast ====================================

Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line) {
    this->rel_op = rop;
    this->lhs_condition = lhs;
    this->rhs_condition = rhs;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = this->lhs_condition->get_data_type();
}

Data_Type Relational_Expr_Ast::get_data_type() {
    return this->node_data_type; 
}

void Relational_Expr_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Relational_Expr_Ast::check_ast() {
    auto ret = true;
    if (this->lhs_condition->get_data_type() != this->rhs_condition->get_data_type()) ret = false;
    if (!ret) error("Relational statement data type not compatible", this->lineno);
    return ret;
}

void Relational_Expr_Ast::print(ostream & file_buffer) {
    string relational_operators[] = {"LE", "LT", "GT", "GE", "EQ", "NE"};
    file_buffer << endl << AST_NODE_SPACE << "Condition: " << relational_operators[this->rel_op];
    file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs_condition->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs_condition->print(file_buffer); file_buffer << ")";
}


// ==================== Logical_Expr_Ast =======================================

Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line) {
    this->bool_op = bop;
    this->lhs_op = lhs;
    this->rhs_op = rhs;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = int_data_type;
}   

Data_Type Logical_Expr_Ast::get_data_type() {
    return this->node_data_type; 
}

void Logical_Expr_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Logical_Expr_Ast::check_ast() {
    return true;
}

void Logical_Expr_Ast::print(ostream & file_buffer) {
    string logical_operators[] = {"NOT", "OR", "AND"};
    file_buffer << endl << AST_NODE_SPACE << "Condition: " << logical_operators[this->bool_op];
    if (this->lhs_op) {
        file_buffer << endl << AST_SUB_NODE_SPACE << "LHS ("; this->lhs_op->print(file_buffer); file_buffer << ")";
    }
    file_buffer << endl << AST_SUB_NODE_SPACE << "RHS ("; this->rhs_op->print(file_buffer); file_buffer << ")";
}


// =================== Selection_Statement_Ast =================================

Selection_Statement_Ast::Selection_Statement_Ast(Ast * cond,Ast* then_part, Ast* else_part, int line) {
    this->cond = cond;
    this->then_part = then_part;
    this->else_part = else_part;
    this->lineno = line;
    this->ast_num_child = ternary_arity;
    this->node_data_type = void_data_type;
}

Data_Type Selection_Statement_Ast::get_data_type() {
    return this->node_data_type;
}

void Selection_Statement_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Selection_Statement_Ast::check_ast() {
    return true;
}

void Selection_Statement_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_SPACE << "IF : ";
    file_buffer << endl << AST_SPACE << "CONDITION ("; this->cond->print(file_buffer); file_buffer << ")";
    file_buffer << endl << AST_SPACE << "THEN ("; this->then_part->print(file_buffer); file_buffer << ")";
    if (this->else_part) {
        file_buffer << endl << AST_SPACE << "ELSE ("; this->else_part->print(file_buffer); file_buffer << ")";
    }
}


// =================== Iteration_Statement_Ast =================================

Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * cond, Ast* body, int line, bool do_form) {
    this->cond = cond;
    this->body = body;
    this->is_do_form = do_form;
    this->lineno = line;
    this->ast_num_child = binary_arity;
    this->node_data_type = void_data_type;
}

Data_Type Iteration_Statement_Ast::get_data_type() {
    return this->node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt) {
    this->node_data_type = dt;
}

bool Iteration_Statement_Ast::check_ast() {
    return true;
}

void Iteration_Statement_Ast::print(ostream & file_buffer) {
    if (this->is_do_form) {
        file_buffer << endl << AST_SPACE << "DO ("; this->body->print(file_buffer); file_buffer << ")";        
        file_buffer << endl << AST_SPACE << "WHILE CONDITION ("; this->cond->print(file_buffer); file_buffer << ")";
    }
    else {
        file_buffer << endl << AST_SPACE << "WHILE : ";
        file_buffer << endl << AST_SPACE << "CONDITION ("; this->cond->print(file_buffer); file_buffer << ")";
        file_buffer << endl << AST_SPACE << "BODY ("; this->body->print(file_buffer); file_buffer << ')';
    }
}


// =================== Sequence_Ast ============================================

Sequence_Ast::Sequence_Ast(int line) {
    this->lineno = line;
    this->ast_num_child = zero_arity;
    this->node_data_type = void_data_type;
}

void Sequence_Ast::ast_push_back(Ast *ast) {
    this->statement_list.push_back(ast);
}

void Sequence_Ast::print(ostream & file_buffer) {
    for (const auto &child_ast: this->statement_list) {
        file_buffer << endl;
        child_ast->print(file_buffer);
    }
}


// =================== Call_Ast ================================================

Call_Ast::Call_Ast(string name, int line) {
    this->procedure_name = name;
    this->lineno = line;
    this->ast_num_child = zero_arity;
    auto procedure_prototype = program_object.get_procedure_prototype(this->procedure_name);
    this->node_data_type = procedure_prototype->get_return_type();
}

Data_Type Call_Ast::get_data_type() {
    return this->node_data_type;
}

void Call_Ast::set_register(Register_Descriptor * reg) {
    this->return_value_reg = reg;
}

void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list) {
    if (this->actual_param_list.size() != formal_param_list.get_table().size()) {
        error("Actual and formal parameter count do not match", this->lineno);
        exit(1);
    }

    int position = 0;
    for (const auto &param: this->actual_param_list) {
        position += 1;
        if (formal_param_list.get_symbol_table_entry_by_index(position).get_data_type() != param->get_data_type()) {
            error("Actual and formal parameters data types are not matching", this->lineno);
            exit(1);
        }
    }
}

void Call_Ast::set_actual_param_list(list<Ast *> & param_list) {
    this->actual_param_list = param_list;
    this->actual_param_list.reverse();
}

void Call_Ast::print(ostream & file_buffer) {
    file_buffer << endl << AST_SPACE << "FN CALL: " << this->procedure_name;
    file_buffer << "(";
    for (const auto &ast: this->actual_param_list) {
        file_buffer << endl << AST_NODE_SPACE;
        ast->print(file_buffer);
    }
    file_buffer << ")";
}


// =================== Return_Ast ==============================================

Return_Ast::Return_Ast(Ast * ret_val, string name, int line) {
    this->return_value = ret_val;
    this->proc_name = name;
    this->lineno = line;
    this->ast_num_child = unary_arity;
    if (this->return_value) {
        this->node_data_type = this->return_value->get_data_type();
    }
    else {
        this->node_data_type = void_data_type;
    }
    auto procedure_prototype = program_object.get_procedure_prototype(this->proc_name);
    auto type = procedure_prototype->get_return_type();
    if (type != this->node_data_type) {
        error("Return type not matching", this->lineno);
        exit(1);
    }
}

Data_Type Return_Ast::get_data_type() {
    return this->node_data_type;
}

void Return_Ast::print(ostream & file_buffer) {
    file_buffer << AST_SPACE << "RETURN "; this->return_value->print(file_buffer) ; file_buffer << endl;
}
