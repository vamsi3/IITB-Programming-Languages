#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

// ============ Ast ============================================================

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register) {

}

// ============ Assignment_Ast =================================================

Code_For_Ast & Assignment_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());
    auto store_code = this->lhs->create_store_stmt(rhs_code.get_reg());
    icode_stmt_list.merge(store_code.get_icode_list());
    
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, NULL));
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Name_Ast =======================================================

Code_For_Ast & Name_Ast::compile() {
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
    icode_stmt_list.merge(lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());

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
    icode_stmt_list.merge(lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());

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
    icode_stmt_list.merge(lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());

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
    icode_stmt_list.merge(lhs_code.get_icode_list());
    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());

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
    icode_stmt_list.merge(lhs_code.get_icode_list());

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
    // TODO: resolve inconsistency with sclp given
    auto cond_code = this->cond->compile();
    auto zero_reg = machine_desc_object.spim_register_table[zero];

    auto icode_stmt_list = list<Icode_Stmt *>();
    icode_stmt_list.merge(cond_code.get_icode_list());

    auto else_label = this->get_new_label();
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(beq, new Register_Addr_Opd(cond_code.get_reg()), else_label));
    cond_code.get_reg()->reset_register_occupied();

    auto lhs_code = this->lhs->compile();
    icode_stmt_list.merge(lhs_code.get_icode_list());

    Register_Descriptor * reg;
    auto type = this->lhs->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
    }
    else if (type == double_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
    }

    icode_stmt_list.push_back(new Compute_IC_Stmt(or_t, new Register_Addr_Opd(lhs_code.get_reg()), new Register_Addr_Opd(zero_reg), new Register_Addr_Opd(reg))); 
    lhs_code.get_reg()->reset_register_occupied();

    auto if_label = this->get_new_label();
    icode_stmt_list.push_back(new Label_IC_Stmt(j, if_label));

    icode_stmt_list.push_back(new Label_IC_Stmt(label, else_label));

    auto rhs_code = this->rhs->compile();
    icode_stmt_list.merge(rhs_code.get_icode_list());

    icode_stmt_list.push_back(new Compute_IC_Stmt(or_t, new Register_Addr_Opd(rhs_code.get_reg()), new Register_Addr_Opd(zero_reg), new Register_Addr_Opd(reg))); 
    rhs_code.get_reg()->reset_register_occupied();
    zero_reg->reset_register_occupied();

    icode_stmt_list.push_back(new Label_IC_Stmt(label, if_label));

    return *(new Code_For_Ast(icode_stmt_list, reg));
}

// ============ Return_Ast =====================================================

Code_For_Ast & Return_Ast::compile() {
    cout << "[Return_Ast][compile]" << endl;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Relational_Expr_Ast ============================================

Code_For_Ast & Relational_Expr_Ast::compile() {
    auto icode_stmt_list = list<Icode_Stmt *>();
    auto lhs_condition_code = this->lhs_condition->compile();
    icode_stmt_list.merge(lhs_condition_code.get_icode_list());
    auto rhs_condition_code = this->rhs_condition->compile();
    icode_stmt_list.merge(rhs_condition_code.get_icode_list());

    Register_Descriptor * reg;
    Tgt_Op * target_op;
    auto type = this->get_data_type();
    if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<int_reg>();
        target_op = new Tgt_Op[6]{sle, slt, sgt, sge, seq, sne};
    }
    else if (type == int_data_type) {
        reg = machine_desc_object.get_new_register<float_reg>();
        target_op = new Tgt_Op[6]{sle_d, slt_d, sgt_d, sge_d, seq_d, sne_d};
    }

    auto rel_stmt = new Compute_IC_Stmt(target_op[this->rel_op], new Register_Addr_Opd(lhs_condition_code.get_reg()), new Register_Addr_Opd(rhs_condition_code.get_reg()), new Register_Addr_Opd(reg));
    icode_stmt_list.push_back(rel_stmt);
    
    delete target_op;
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
    if (lhs_op_code_pointer) icode_stmt_list.merge(lhs_op_code_pointer->get_icode_list());
    icode_stmt_list.merge(rhs_op_code.get_icode_list());

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
    icode_stmt_list.merge(cond_code.get_icode_list());

    auto else_label = this->get_new_label();
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(beq, new Register_Addr_Opd(cond_code.get_reg()), else_label));
    cond_code.get_reg()->reset_register_occupied();

    auto then_code = this->then_part->compile();
    icode_stmt_list.merge(then_code.get_icode_list());
    then_code.get_reg()->reset_register_occupied();

    string if_label;
    if (this->else_part) {
        if_label = this->get_new_label();
        icode_stmt_list.push_back(new Label_IC_Stmt(j, if_label));
    }

    icode_stmt_list.push_back(new Label_IC_Stmt(label, else_label));
    
    if (this->else_part) {
        auto else_code = this->else_part->compile();
        icode_stmt_list.merge(else_code.get_icode_list());
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
    icode_stmt_list.merge(body_code.get_icode_list());
    body_code.get_reg()->reset_register_occupied();

    icode_stmt_list.push_back(new Label_IC_Stmt(label, cond_label));

    auto cond_code = this->cond->compile();
    icode_stmt_list.merge(cond_code.get_icode_list());
    icode_stmt_list.push_back(new Control_Flow_IC_Stmt(bne, new Register_Addr_Opd(cond_code.get_reg()), body_label));
    cond_code.get_reg()->reset_register_occupied();

    return *(new Code_For_Ast(icode_stmt_list, NULL));
}

// ============ Sequence_Ast ===================================================

Code_For_Ast & Sequence_Ast::compile() {
    for (const auto &ast: this->statement_list) {
        auto code = ast->compile();
        this->sa_icode_list.merge(code.get_icode_list());
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
