#include "ast.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

// ============ Ast ============================================================

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register) {

}

// ============ Assignment_Ast =================================================

Code_For_Ast & Assignment_Ast::compile() {

}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

// ============ Name_Ast =======================================================

Code_For_Ast & Name_Ast::compile() {

}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register) {

}

// ============ Number_Ast =====================================================

template <class T>
Code_For_Ast & Number_Ast<T>::compile() {

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

}

void Sequence_Ast::print_assembly(ostream & file_buffer) {

}

void Sequence_Ast::print_icode(ostream & file_buffer) {

}
