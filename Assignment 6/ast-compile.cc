#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

bool rel_op_switch;

// =============================================================================

void compile_error(string msg, int lineno) {
    cout << "cs316: Error: File: " << "" << " Line: " << lineno << ": " << msg << endl;
    exit(1);
}

// ============ Ast ============================================================

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register) {

}


// ============ Assignment_Ast =================================================

Code_For_Ast & Assignment_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());
    auto store_code = this->lhs->create_store_stmt(rhs_code.get_reg());
    icode_stmt_list.splice(icode_stmt_list.end(), store_code.get_icode_list());
    
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, NULL));
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Name_Ast =======================================================

Code_For_Ast & Name_Ast::compile() {
    // TODO: Check what are the other register related compile functions in symbol_entry are for?

    Register_Descriptor * reg;
    Move_IC_Stmt * load_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        load_stmt = new Move_IC_Stmt(load, new Mem_Addr_Opd(*this->variable_symbol_entry), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        load_stmt = new Move_IC_Stmt(load_d, new Mem_Addr_Opd(*this->variable_symbol_entry), new Register_Addr_Opd(reg));
    }

    auto code = new Code_For_Ast(); code->append_ics(*load_stmt); code->set_reg(reg);
    return *code;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register) {
    Move_IC_Stmt * store_stmt;
    
    auto type = this->get_data_type();
    if (type == int_data_type) {
        store_stmt = new Move_IC_Stmt(store, new Register_Addr_Opd(store_register), new Mem_Addr_Opd(*this->variable_symbol_entry));
    }
    else if (type == double_data_type) {
        store_stmt = new Move_IC_Stmt(store_d, new Register_Addr_Opd(store_register), new Mem_Addr_Opd(*this->variable_symbol_entry));
    }

    auto code = new Code_For_Ast(); code->append_ics(*store_stmt);
    return *code;
}


// ============ Number_Ast =====================================================

template <class T>
Code_For_Ast & Number_Ast<T>::compile() {
    Register_Descriptor * reg;
    Move_IC_Stmt * imm_load_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        imm_load_stmt = new Move_IC_Stmt(imm_load, new Const_Opd<int>(this->constant), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        imm_load_stmt = new Move_IC_Stmt(imm_load_d, new Const_Opd<double>(this->constant), new Register_Addr_Opd(reg));
    }
    
    auto code = new Code_For_Ast(); code->append_ics(*imm_load_stmt); code->set_reg(reg);
    return *code;
}

template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Plus_Ast =======================================================

Code_For_Ast & Plus_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_code = this->lhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());

    Register_Descriptor * reg;
    Compute_IC_Stmt * add_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        add_stmt = new Compute_IC_Stmt(add, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        add_stmt = new Compute_IC_Stmt(add_d, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(add_stmt);
    
    lhs_code.get_reg()->reset_register_occupied();
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Minus_Ast ======================================================

Code_For_Ast & Minus_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_code = this->lhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());

    Register_Descriptor * reg;
    Compute_IC_Stmt * sub_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        sub_stmt = new Compute_IC_Stmt(sub, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        sub_stmt = new Compute_IC_Stmt(sub_d, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(sub_stmt);
    
    lhs_code.get_reg()->reset_register_occupied();
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Divide_Ast =====================================================

Code_For_Ast & Divide_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_code = this->lhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());

    Register_Descriptor * reg;
    Compute_IC_Stmt * div_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        div_stmt = new Compute_IC_Stmt(divd, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        div_stmt = new Compute_IC_Stmt(div_d, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(div_stmt);
    
    lhs_code.get_reg()->reset_register_occupied();
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Mult_Ast =======================================================

Code_For_Ast & Mult_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_code = this->lhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());

    Register_Descriptor * reg;
    Compute_IC_Stmt * mul_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        mul_stmt = new Compute_IC_Stmt(mult, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        mul_stmt = new Compute_IC_Stmt(mult_d, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(mul_stmt);
    
    lhs_code.get_reg()->reset_register_occupied();
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ UMinus_Ast =====================================================

Code_For_Ast & UMinus_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_code = this->lhs->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());

    Register_Descriptor * reg;
    Move_IC_Stmt * uminus_stmt;

    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        uminus_stmt = new Move_IC_Stmt(uminus, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        uminus_stmt = new Move_IC_Stmt(uminus_d, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(uminus_stmt);
    
    lhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


// ============ Conditional_Expression_Ast =====================================

Code_For_Ast & Conditional_Expression_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    
    auto cond_code = this->cond->compile();
    auto lhs_code = this->lhs->compile();
    auto rhs_code = this->rhs->compile();
    auto zero_reg = machine_desc_object.spim_register_table[zero];

    Register_Descriptor * reg;
    auto type = this->lhs->get_data_type(); // NOTE: we expect lhs and rhs to have same datatype, constraint from check_ast
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
    }
    
    icode_stmt_list.splice(icode_stmt_list.end(), cond_code.get_icode_list());

    auto else_label = this->get_new_label();
    Tgt_Op branch_op;
    if (cond_code.get_reg()->get_register() == none) branch_op = (rel_op_switch)? bc1t : bc1f;
    else branch_op = beq;
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(branch_op, new Register_Addr_Opd(cond_code.get_reg()), new Register_Addr_Opd(zero_reg), else_label));

    icode_stmt_list.splice(icode_stmt_list.end(), lhs_code.get_icode_list());

    icode_stmt_list.push_back(new Compute_IC_Stmt(or_t, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(zero_reg), new Register_Addr_Opd(reg))); 

    auto if_label = this->get_new_label();
    icode_stmt_list.push_back(new Label_IC_Stmt(j, if_label));

    icode_stmt_list.push_back(new Label_IC_Stmt(label, else_label));

    icode_stmt_list.splice(icode_stmt_list.end(), rhs_code.get_icode_list());

    icode_stmt_list.push_back(new Compute_IC_Stmt(or_t, new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(zero_reg), new Register_Addr_Opd(reg))); 

    icode_stmt_list.push_back(new Label_IC_Stmt(label, if_label));

    cond_code.get_reg()->reset_register_occupied();
    lhs_code.get_reg()->reset_register_occupied();
    rhs_code.get_reg()->reset_register_occupied();
    zero_reg->reset_register_occupied();

    return *(new Code_For_Ast(icode_stmt_list, reg));
}


// ============ Print_Ast ======================================================

Code_For_Ast & Print_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto type = this->var->get_data_type();
    auto v0_reg = machine_desc_object.spim_register_table[v0];

    if (type == int_data_type) {
        icode_stmt_list.push_back(new Move_IC_Stmt(imm_load, new Const_Opd<int>(1), new Register_Addr_Opd(v0_reg)));
    }
    else if (type == double_data_type) {
        icode_stmt_list.push_back(new Move_IC_Stmt(imm_load, new Const_Opd<int>(3), new Register_Addr_Opd(v0_reg)));
    }

    auto var_code = this->var->compile();
    auto arg_load_stmt = var_code.get_icode_list().back();
    
    Register_Descriptor * print_reg;
    if (type == int_data_type) {
        print_reg = machine_desc_object.spim_register_table[a0];
    }
    else if (type == double_data_type) {
        print_reg = machine_desc_object.spim_register_table[f12];
    }
    arg_load_stmt->set_result(new Register_Addr_Opd(print_reg));
    var_code.get_reg()->reset_register_occupied();
    icode_stmt_list.push_back(arg_load_stmt);
    
    icode_stmt_list.push_back(new Print_IC_Stmt());

    print_reg->reset_register_occupied();
    v0_reg->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, NULL));
}


// ============ Relational_Expr_Ast ============================================

Code_For_Ast & Relational_Expr_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    
    auto lhs_condition_code = this->lhs_condition->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), lhs_condition_code.get_icode_list());
    auto rhs_condition_code = this->rhs_condition->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_condition_code.get_icode_list());

    Register_Descriptor * reg = NULL;
    Tgt_Op op;
    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        Tgt_Op target_op[6] = {sle, slt, sgt, sge, seq, sne};
        op = target_op[this->rel_op];
    }
    else if (type == double_data_type) {
        Tgt_Op target_op[6] = {sle_d, slt_d, sgt_d, sge_d, seq_d, sne_d};
        op = target_op[this->rel_op];
        rel_op_switch = (op == sge_d || op == sgt_d || op == sne_d);
    }

    icode_stmt_list.push_back(new Compute_IC_Stmt(op, new Register_Addr_Opd(lhs_condition_code.get_reg()), new Register_Addr_Opd(rhs_condition_code.get_reg()), new Register_Addr_Opd(reg)));
    lhs_condition_code.get_reg()->reset_register_occupied();
    rhs_condition_code.get_reg()->reset_register_occupied();

    return *(new Code_For_Ast(icode_stmt_list, reg));
}


// ============ Logical_Expr_Ast ===============================================

Code_For_Ast & Logical_Expr_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();

    Code_For_Ast * lhs_op_code_pointer = NULL;
    Register_Descriptor * one_reg = NULL;
    if (this->bool_op == _logical_not) {
        one_reg = machine_desc_object.get_new_register<int_reg>();
        icode_stmt_list.push_back(new Move_IC_Stmt(imm_load, new Const_Opd<int>(1), new Register_Addr_Opd(one_reg)));
    }
    else {
        lhs_op_code_pointer = &this->lhs_op->compile();
    }

    auto rhs_op_code = this->rhs_op->compile();
    if (lhs_op_code_pointer) icode_stmt_list.splice(icode_stmt_list.end(), lhs_op_code_pointer->get_icode_list());
    icode_stmt_list.splice(icode_stmt_list.end(), rhs_op_code.get_icode_list());

    Compute_IC_Stmt * logical_stmt;
    Tgt_Op target_op[] = {not_t, or_t, and_t};
    auto reg = machine_desc_object.get_new_register<int_reg>();
    if (this->bool_op == _logical_not) {
        logical_stmt = new Compute_IC_Stmt(target_op[this->bool_op], new Register_Addr_Opd(rhs_op_code.get_reg()), new Register_Addr_Opd(one_reg), new Register_Addr_Opd(reg));
    }
    else {
        logical_stmt = new Compute_IC_Stmt(target_op[this->bool_op], new Register_Addr_Opd(lhs_op_code_pointer->get_reg()), new Register_Addr_Opd(rhs_op_code.get_reg()), new Register_Addr_Opd(reg));
    }
    icode_stmt_list.push_back(logical_stmt);

    if (one_reg) one_reg->reset_register_occupied();
    if (lhs_op_code_pointer) lhs_op_code_pointer->get_reg()->reset_register_occupied();
    rhs_op_code.get_reg()->reset_register_occupied();
    
    return *(new Code_For_Ast(icode_stmt_list, reg));
}


// ============ Selection_Statement_Ast ========================================

Code_For_Ast & Selection_Statement_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    
    auto cond_code = this->cond->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), cond_code.get_icode_list());

    auto else_label = this->get_new_label();

    Tgt_Op branch_op;
    if (cond_code.get_reg()->get_register() == none) branch_op = (rel_op_switch)? bc1t : bc1f;
    else branch_op = beq;
    auto zero_reg = machine_desc_object.spim_register_table[zero];
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(branch_op, new Register_Addr_Opd(cond_code.get_reg()), new Register_Addr_Opd(zero_reg), else_label));
    zero_reg->reset_register_occupied();
    cond_code.get_reg()->reset_register_occupied();

    auto then_code = this->then_part->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), then_code.get_icode_list());
    then_code.get_reg()->reset_register_occupied();

    string if_label;
    if (this->else_part) {
        if_label = this->get_new_label();
        icode_stmt_list.push_back(new Label_IC_Stmt(j, if_label));
    }

    icode_stmt_list.push_back(new Label_IC_Stmt(label, else_label));
    
    if (this->else_part) {
        auto else_code = this->else_part->compile();
        icode_stmt_list.splice(icode_stmt_list.end(), else_code.get_icode_list());
        else_code.get_reg()->reset_register_occupied();
        icode_stmt_list.push_back(new Label_IC_Stmt(label, if_label));
    }

    return *(new Code_For_Ast(icode_stmt_list, NULL));
}


// ============ Iteration_Statement_Ast ========================================

Code_For_Ast & Iteration_Statement_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();

    auto body_label = this->get_new_label();
    auto cond_label = this->get_new_label();
    
    if (!this->is_do_form) {
        icode_stmt_list.push_back(new Label_IC_Stmt(j, cond_label));
    }

    icode_stmt_list.push_back(new Label_IC_Stmt(label, body_label));
    auto body_code = this->body->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), body_code.get_icode_list());
    body_code.get_reg()->reset_register_occupied();

    icode_stmt_list.push_back(new Label_IC_Stmt(label, cond_label));

    auto cond_code = this->cond->compile();
    icode_stmt_list.splice(icode_stmt_list.end(), cond_code.get_icode_list());

    Tgt_Op branch_op;
    if (cond_code.get_reg()->get_register() == none) branch_op = (rel_op_switch)? bc1f : bc1t;
    else branch_op = bne;
    auto zero_reg = machine_desc_object.spim_register_table[zero];
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(branch_op, new Register_Addr_Opd(cond_code.get_reg()), new Register_Addr_Opd(zero_reg), body_label));

    zero_reg->reset_register_occupied();
    cond_code.get_reg()->reset_register_occupied();

    return *(new Code_For_Ast(icode_stmt_list, NULL));
}


// ============ Sequence_Ast ===================================================

Code_For_Ast & Sequence_Ast::compile() {
    for (const auto &ast: this->statement_list) {
        auto code = ast->compile();
        this->sa_icode_list.splice(this->sa_icode_list.end(), code.get_icode_list());
        code.get_reg()->reset_register_occupied();
    }
    return *(new Code_For_Ast(this->sa_icode_list, NULL));
}

void Sequence_Ast::print_assembly(ostream & file_buffer) {
    for (const auto &icode_stmt: this->sa_icode_list) {
        icode_stmt->print_assembly(file_buffer);
    }
}

void Sequence_Ast::print_icode(ostream & file_buffer) {
    for (const auto &icode_stmt: this->sa_icode_list) {
        icode_stmt->print_icode(file_buffer);
    }
}


// ============ Call_Ast =======================================================

Code_For_Ast & Call_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto procedure_prototype = program_object.get_procedure_prototype(this->procedure_name); procedure_prototype->set_proc_is_called();
    int offset = 0;
    int position = 0;
    int count = this->actual_param_list.size();
    for (auto it = this->actual_param_list.rbegin(); it != this->actual_param_list.rend(); it++) {
        auto param = *it;
        position += 1;

        auto param_code = param->compile();
        icode_stmt_list.splice(icode_stmt_list.end(), param_code.get_icode_list());
        
        auto formal_param_name = procedure_prototype->get_variable_in_formal_list(count+1-position);
        auto entry = &procedure_prototype->get_formal_param_entry(formal_param_name);
        auto name = entry->get_variable_name();
        auto type = entry->get_data_type();
        auto entry_clone = new Symbol_Table_Entry(name, type, entry->get_lineno(), sp_ref);
        entry_clone->set_symbol_scope(entry->get_symbol_scope());
        entry_clone->set_start_offset(offset);

        Tgt_Op store_op;
        if (type == int_data_type) {
            offset -= 4;
            store_op = store;
        } else if (type== double_data_type) {
            offset -= 8;
            store_op = store_d;
        }

        icode_stmt_list.push_back(new Move_IC_Stmt(store_op, new Register_Addr_Opd(param_code.get_reg()), new Mem_Addr_Opd(*entry_clone)));
        param_code.get_reg()->reset_register_occupied();
    }
    auto reg_sp = machine_desc_object.spim_register_table[sp];
    icode_stmt_list.push_back(new Compute_IC_Stmt(sub, new Register_Addr_Opd(reg_sp), new Const_Opd<int>(-offset), new Register_Addr_Opd(reg_sp)));
    icode_stmt_list.push_back(new Label_IC_Stmt(jal, this->procedure_name));
    icode_stmt_list.push_back(new Compute_IC_Stmt(add, new Register_Addr_Opd(reg_sp), new Const_Opd<int>(-offset), new Register_Addr_Opd(reg_sp)));

    auto type = this->get_data_type();

    if (type == void_data_type) {
        return *(new Code_For_Ast(icode_stmt_list, NULL));
    }

    Tgt_Op mov_op;
    Register_Descriptor * reg;
    if (type == int_data_type) {
        this->return_value_reg = machine_desc_object.spim_register_table[v1];
        reg = machine_desc_object.get_new_register<int_reg>();
        mov_op = mov;
    }
    else if (type == double_data_type) {
        this->return_value_reg = machine_desc_object.spim_register_table[f0];
        reg = machine_desc_object.get_new_register<float_reg>();
        mov_op = move_d;
    }
    icode_stmt_list.push_back(new Move_IC_Stmt(mov_op, new Register_Addr_Opd(this->return_value_reg), new Register_Addr_Opd(reg)));
    this->return_value_reg->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, reg));
}

Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}


// ============ Return_Ast =====================================================

Code_For_Ast & Return_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto type = this->get_data_type();

    if (type == void_data_type) {
        icode_stmt_list.push_back(new Label_IC_Stmt(ret_inst, "epilogue_" + this->proc_name));
        return *(new Code_For_Ast(icode_stmt_list, NULL));
    }
    else {
        auto return_value_code = this->return_value->compile();
        icode_stmt_list.splice(icode_stmt_list.end(), return_value_code.get_icode_list());

        Tgt_Op mov_op;
        Register_Descriptor * ret_reg;
        if (type == int_data_type) {
            ret_reg = machine_desc_object.spim_register_table[v1];
            mov_op = mov;
        }
        else if (type == double_data_type) {
            ret_reg = machine_desc_object.spim_register_table[f0];
            mov_op = move_d;
        }
        ret_reg->set_register_occupied();
        
        icode_stmt_list.push_back(new Move_IC_Stmt(mov_op, new Register_Addr_Opd(return_value_code.get_reg()), new Register_Addr_Opd(ret_reg)));
        return_value_code.get_reg()->reset_register_occupied();

        icode_stmt_list.push_back(new Label_IC_Stmt(ret_inst, "epilogue_" + this->proc_name));
        return *(new Code_For_Ast(icode_stmt_list, ret_reg));
    }
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}
