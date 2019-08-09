#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;


void eval_error(string msg, int lineno) {
    cout << "cs316: Error: File: " << "" << " Line: " << lineno << ": " << msg << endl;
    exit(1);
}


// ============ Name_Ast =======================================================

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer) {
    string variable_name = this->variable_symbol_entry->get_variable_name();
    file_buffer << VAR_SPACE <<  variable_name << " : ";

    Eval_Result* result;
    result = &this->get_value_of_evaluation(eval_env);

    auto result_type = result->get_result_enum();
    if (result_type == int_result) {
        file_buffer << result->get_int_value();
    }
    else if (result_type == double_result) {
        file_buffer << result->get_double_value();
    }

    file_buffer << endl;
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env) {
    string variable_name = this->variable_symbol_entry->get_variable_name();
    Eval_Result* result;
    if (eval_env.does_variable_exist(variable_name)) {
        result = eval_env.get_variable_value(variable_name);
    }
    else if (interpreter_global_table.does_variable_exist(variable_name)) {
        result = interpreter_global_table.get_variable_value(variable_name);
    }
    else {
        cout << "[ast-eval.cc][Name_Ast::get_value_of_evaluation] This shouldn't happen!!!" << endl;
    }

    if (!result->is_variable_defined()) {
        eval_error("Variable should be defined before its use", this->lineno);
    }

    Eval_Result* result_deepcopy;
    auto result_type = result->get_result_enum();
    if (result_type == int_result) {
        auto result_int = new Eval_Result_Value_Int;
        result_int->set_variable_status(true);
        result_int->set_value(result->get_int_value());
        result_deepcopy = result_int;
    }
    else if (result_type == double_result) {
        auto result_double = new Eval_Result_Value_Double;
        result_double->set_variable_status(true);
        result_double->set_value(result->get_double_value());
        result_deepcopy = result_double;
    }
    return *result_deepcopy;
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result) {
    string variable_name = this->variable_symbol_entry->get_variable_name();
    if (eval_env.does_variable_exist(variable_name)) {
        eval_env.put_variable_value(result, variable_name);
    }
    else if (interpreter_global_table.does_variable_exist(variable_name)) {
        interpreter_global_table.put_variable_value(result, variable_name);
    }
    else {
        cout << "[ast-eval.cc][Name_Ast::set_value_of_evaluation] This shouldn't happen!!!" << endl;
    }
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    return this->get_value_of_evaluation(eval_env);
}

// =============================================================================


template <class T>
Eval_Result & Number_Ast<T>::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    Eval_Result* result;
    string type = typeid(T).name();
    if (type == "i") {
        auto result_int = new Eval_Result_Value_Int;
        result_int->set_value(this->constant);
        result = result_int;
    }
    else if (type == "d") {
        auto result_double = new Eval_Result_Value_Double;
        result_double->set_value(this->constant);
        result = result_double;
    }
    return *result;
}

Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    this->print(file_buffer);
    file_buffer << endl;

    auto rhs_result = &this->rhs->evaluate(eval_env, file_buffer);
    rhs_result->set_variable_status(true);
    this->lhs->set_value_of_evaluation(eval_env, *rhs_result);

    this->lhs->print_value(eval_env, file_buffer);
    file_buffer << endl;
}

Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto lhs_result = &this->lhs->evaluate(eval_env, file_buffer), rhs_result = &this->rhs->evaluate(eval_env, file_buffer);
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        int lhs_value = lhs_result->get_int_value(), rhs_value = rhs_result->get_int_value();
        lhs_result->set_value(lhs_value + rhs_value);
    }
    else if (result_type == double_result) {
        double lhs_value = lhs_result->get_double_value(), rhs_value = rhs_result->get_double_value();
        lhs_result->set_value(lhs_value + rhs_value);
    }
    return *lhs_result;
}

Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto lhs_result = &this->lhs->evaluate(eval_env, file_buffer), rhs_result = &this->rhs->evaluate(eval_env, file_buffer);
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        int lhs_value = lhs_result->get_int_value(), rhs_value = rhs_result->get_int_value();
        lhs_result->set_value(lhs_value - rhs_value);
    }
    else if (result_type == double_result) {
        double lhs_value = lhs_result->get_double_value(), rhs_value = rhs_result->get_double_value();
        lhs_result->set_value(lhs_value - rhs_value);
    }
    return *lhs_result;
}

Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto lhs_result = &this->lhs->evaluate(eval_env, file_buffer), rhs_result = &this->rhs->evaluate(eval_env, file_buffer);
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        int lhs_value = lhs_result->get_int_value(), rhs_value = rhs_result->get_int_value();
        if (rhs_value == 0) {
            eval_error("Divide by 0", this->lineno);
        }
        lhs_result->set_value(lhs_value / rhs_value);
    }
    else if (result_type == double_result) {
        double lhs_value = lhs_result->get_double_value(), rhs_value = rhs_result->get_double_value();
        if (rhs_value == 0) {
            eval_error("Divide by 0", this->lineno);
        }
        lhs_result->set_value(lhs_value / rhs_value);
    }
    return *lhs_result;
}

Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto lhs_result = &this->lhs->evaluate(eval_env, file_buffer), rhs_result = &this->rhs->evaluate(eval_env, file_buffer);
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        int lhs_value = lhs_result->get_int_value(), rhs_value = rhs_result->get_int_value();
        lhs_result->set_value(lhs_value * rhs_value);
    }
    else if (result_type == double_result) {
        double lhs_value = lhs_result->get_double_value(), rhs_value = rhs_result->get_double_value();
        lhs_result->set_value(lhs_value * rhs_value);
    }
    return *lhs_result;
}

Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto lhs_result = &this->lhs->evaluate(eval_env, file_buffer);
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        int lhs_value = lhs_result->get_int_value();
        lhs_result->set_value(-lhs_value);
    }
    else if (result_type == double_result) {
        double lhs_value = lhs_result->get_double_value();
        lhs_result->set_value(-lhs_value);
    }
    return *lhs_result;
}

Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto cond_value = this->cond->evaluate(eval_env, file_buffer).get_int_value();
    return (cond_value == 1)? this->lhs->evaluate(eval_env, file_buffer): this->rhs->evaluate(eval_env, file_buffer);
}

Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto result = new Eval_Result_Value_Int;
    result->set_value(0);
    auto lhs_result = &this->lhs_condition->evaluate(eval_env, file_buffer);
    auto rhs_result = &this->rhs_condition->evaluate(eval_env, file_buffer);
    
    int compare_values = 0;
    auto result_type = lhs_result->get_result_enum();
    if (result_type == int_result) {
        auto lhs_value = lhs_result->get_int_value();
        auto rhs_value = rhs_result->get_int_value();
        if (lhs_value < rhs_value) compare_values = -1;
        else if (lhs_value > rhs_value) compare_values = 1;
    }
    else if (result_type == double_result) {
        auto lhs_value = lhs_result->get_double_value();
        auto rhs_value = rhs_result->get_double_value();
        if (lhs_value < rhs_value) compare_values = -1;
        else if (lhs_value > rhs_value) compare_values = 1;
    }

    if (this->rel_op == less_equalto && compare_values <= 0) result->set_value(1);
    else if (this->rel_op == less_than && compare_values < 0) result->set_value(1);
    else if (this->rel_op == greater_than && compare_values > 0) result->set_value(1);
    else if (this->rel_op == greater_equalto && compare_values >= 0) result->set_value(1);
    else if (this->rel_op == equalto && compare_values == 0) result->set_value(1);
    else if (this->rel_op == not_equalto && compare_values != 0) result->set_value(1);

    return *result;
}

Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto result = new Eval_Result_Value_Int;
    result->set_value(0);

    auto rhs_value = this->rhs_op->evaluate(eval_env, file_buffer).get_int_value();
    if (this->bool_op == _logical_not) result->set_value(!rhs_value);
    else {
        auto lhs_value = this->lhs_op->evaluate(eval_env, file_buffer).get_int_value();
        if (this->bool_op == _logical_or) result->set_value(lhs_value || rhs_value);
        else if (this->bool_op == _logical_and) result->set_value(lhs_value && rhs_value);
    }
    return *result;
}

Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    auto cond_result = &this->cond->evaluate(eval_env, file_buffer);
    auto cond_value = cond_result->get_int_value();

    if (cond_value == 1) {
        this->then_part->evaluate(eval_env, file_buffer);
    }
    else if (this->else_part) {
        this->else_part->evaluate(eval_env, file_buffer);
    }
}

Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    int cond_value;
    if (this->is_do_form) {
        while (1) {
            this->body->evaluate(eval_env, file_buffer);
            cond_value = this->cond->evaluate(eval_env, file_buffer).get_int_value();
            if (cond_value == 0) break;
        }
    }
    else {
        while (1) {
            cond_value = this->cond->evaluate(eval_env, file_buffer).get_int_value();
            if (cond_value == 0) break;
            this->body->evaluate(eval_env, file_buffer);
        }
    }
}

Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    for (const auto &statement: this->statement_list) {
        statement->evaluate(eval_env, file_buffer);
    }
}

Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    // empty
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
    // empty
}
