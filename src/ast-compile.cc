#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

// ============ Ast ============================================================

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register) {

}

// ============ Assignment_Ast =================================================

Code_For_Ast & Assignment_Ast::compile() {
    auto rhs_code = this->rhs->compile();
    auto store_code = this->lhs->create_store_stmt(rhs_code.get_reg());
    auto icode_stmt_list = list<Icode_Stmt *>();
    icode_stmt_list.merge(rhs_code.get_icode_list());
    icode_stmt_list.merge(store_code.get_icode_list());
    rhs_code.get_reg()->reset_register_occupied();
    return *(new Code_For_Ast(icode_stmt_list, NULL));
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Name_Ast =======================================================

Code_For_Ast & Name_Ast::compile() {
    auto reg = machine_desc_object.get_new_register<int_reg>();
    auto load_stmt = new Move_IC_Stmt(load, new Mem_Addr_Opd(*this->variable_symbol_entry), new Register_Addr_Opd(reg));
    auto code = new Code_For_Ast(); code->append_ics(*load_stmt); code->set_reg(reg);
    return *code;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register) {
    auto store_stmt = new Move_IC_Stmt(store, new Register_Addr_Opd(store_register), new Mem_Addr_Opd(*this->variable_symbol_entry));
    auto code = new Code_For_Ast(); code->append_ics(*store_stmt);
    return *code;
}

// ============ Number_Ast =====================================================

template <class T>
Code_For_Ast & Number_Ast<T>::compile() {
    auto reg = machine_desc_object.get_new_register<int_reg>();
    auto imm_load_stmt = new Move_IC_Stmt(imm_load, new Const_Opd<int>(this->constant), new Register_Addr_Opd(reg));
    auto code = new Code_For_Ast(); code->append_ics(*imm_load_stmt); code->set_reg(reg);
    return *code;
}

template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Plus_Ast =======================================================

Code_For_Ast & Plus_Ast::compile() {

}

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Minus_Ast ======================================================

Code_For_Ast & Minus_Ast::compile() {

}

Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Divide_Ast =====================================================

Code_For_Ast & Divide_Ast::compile() {

}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Mult_Ast =======================================================

Code_For_Ast & Mult_Ast::compile() {

}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ UMinus_Ast =====================================================

Code_For_Ast & UMinus_Ast::compile() {

}

Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Conditional_Expression_Ast =====================================

Code_For_Ast & Conditional_Expression_Ast::compile() {

}

// ============ Return_Ast =====================================================

Code_For_Ast & Return_Ast::compile() {

}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Relational_Expr_Ast ============================================

Code_For_Ast & Relational_Expr_Ast::compile() {

}

// ============ Logical_Expr_Ast ============================================

Code_For_Ast & Logical_Expr_Ast::compile() {

}

// ============ Selection_Statement_Ast ============================================

Code_For_Ast & Selection_Statement_Ast::compile() {

}

// ============ Iteration_Statement_Ast ============================================

Code_For_Ast & Iteration_Statement_Ast::compile() {

}

// ============ Sequence_Ast ============================================

Code_For_Ast & Sequence_Ast::compile() {
    for (const auto &ast: this->statement_list) {
        auto code = ast->compile();
        this->sa_icode_list.merge(code.get_icode_list());
    }
    return *(new Code_For_Ast(this->sa_icode_list, NULL));
}

void Sequence_Ast::print_assembly(ostream & file_buffer) {
    file_buffer << "[Sequence_Ast][print_assembly]" << endl;
    for (const auto &icode_stmt: this->sa_icode_list) {
        icode_stmt->print_assembly(file_buffer);
    }
}

void Sequence_Ast::print_icode(ostream & file_buffer) {
    file_buffer << "[Sequence_Ast][print_icode]" << endl;
    for (const auto &icode_stmt: this->sa_icode_list) {
        icode_stmt->print_icode(file_buffer);
    }
}
