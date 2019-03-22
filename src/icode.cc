#include "icode.hh"

template class Const_Opd<double>;
template class Const_Opd<int>;

///////////////////////// Instruction Descriptor ///////////////////////////////////


// ============ Instruction_Descriptor =========================================

Instruction_Descriptor::Instruction_Descriptor(Tgt_Op op, string name, string mnn, string ics, Icode_Format icf, Assembly_Format af) {

}

Instruction_Descriptor::Instruction_Descriptor() {

}



///////////////////////////// Icode statement operand ///////////////////////////////////


// ============ Ics_Opd ========================================================

Register_Descriptor * Ics_Opd::get_reg() {

}


// ============ Mem_Addr_Opd ===================================================

Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se) {

}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer) {

}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer) {

}

Mem_Addr_Opd & Mem_Addr_Opd::operator=(const Mem_Addr_Opd & rhs) {

}


// ============ Register_Addr_Opd ==============================================

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd) {

}

Register_Descriptor * Register_Addr_Opd::get_reg() {

}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer) {

}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer) {

}

Register_Addr_Opd & Register_Addr_Opd::operator=(const Register_Addr_Opd & rhs) {

}


// ============ Const_Opd ======================================================

template <class T>
Const_Opd<T>::Const_Opd(T num) {

}

template <class T>
void Const_Opd<T>::print_ics_opd(ostream & file_buffer) {

}

template <class T>
void Const_Opd<T>::print_asm_opd(ostream & file_buffer) {

}

template <class T>
Const_Opd<T> & Const_Opd<T>::operator=(const Const_Opd<T> & rhs) {

}



///////////////////////////////// Intermediate code statements //////////////////////////


// ============ Icode_Stmt =====================================================

Instruction_Descriptor & Icode_Stmt::get_op() {

}

Ics_Opd * Icode_Stmt::get_opd1() {

}

Ics_Opd * Icode_Stmt::get_opd2() {

}

Ics_Opd * Icode_Stmt::get_result() {

}

void Icode_Stmt::set_opd1(Ics_Opd * io) {

}

void Icode_Stmt::set_opd2(Ics_Opd * io) {

}

void Icode_Stmt::set_result(Ics_Opd * io) {

}


// ============ Move_IC_Stmt ===================================================

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * result) {

}

Move_IC_Stmt & Move_IC_Stmt::operator=(const Move_IC_Stmt & rhs) {

}

Instruction_Descriptor & Move_IC_Stmt::get_inst_op_of_ics() {

}

Ics_Opd * Move_IC_Stmt::get_opd1() {

}

void Move_IC_Stmt::set_opd1(Ics_Opd * io) {

}

Ics_Opd * Move_IC_Stmt::get_result() {

}

void Move_IC_Stmt::set_result(Ics_Opd * io) {

}

void Move_IC_Stmt::print_icode(ostream & file_buffer) {

}

void Move_IC_Stmt::print_assembly(ostream & file_buffer) {

}


// ============ Compute_IC_Stmt ================================================

Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * opd2, Ics_Opd * result) {

}

Compute_IC_Stmt & Compute_IC_Stmt::operator=(const Compute_IC_Stmt & rhs) {

}

Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics() {

}

Ics_Opd * Compute_IC_Stmt::get_opd1() {

}

void Compute_IC_Stmt::set_opd1(Ics_Opd * io) {

}

Ics_Opd * Compute_IC_Stmt::get_opd2() {

}

void Compute_IC_Stmt::set_opd2(Ics_Opd * io) {

}

Ics_Opd * Compute_IC_Stmt::get_result() {

}

void Compute_IC_Stmt::set_result(Ics_Opd * io) {

}

void Compute_IC_Stmt::print_icode(ostream & file_buffer) {

}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer) {

}


// ============ Control_Flow_IC_Stmt ===========================================

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, string label) {

}

Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs) {

}

Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics() {

}

Ics_Opd * Control_Flow_IC_Stmt::get_opd1() {

}

void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io) {

}

string Control_Flow_IC_Stmt::get_label() {

}

void Control_Flow_IC_Stmt::set_label(string label) {

}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer) {

}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer) {

}


// ============ Label_IC_Stmt ==================================================

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string label) {

}

Label_IC_Stmt & Label_IC_Stmt::operator=(const Label_IC_Stmt & rhs) {

}

Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics() {

}

string Label_IC_Stmt::get_label() {

}

void Label_IC_Stmt::set_label(string label) {

}

void Label_IC_Stmt::print_icode(ostream & file_buffer) {

}

void Label_IC_Stmt::print_assembly(ostream & file_buffer) {

}



//////////////////////// Intermediate code for Ast statements ////////////////////////


// ============ Code_For_Ast ===================================================

Code_For_Ast::Code_For_Ast() {

}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg) {

}

void Code_For_Ast::append_ics(Icode_Stmt & ics) {

}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list() {

}

Register_Descriptor * Code_For_Ast::get_reg() {

}

void Code_For_Ast::set_reg(Register_Descriptor * reg) {

}

Code_For_Ast & Code_For_Ast::operator=(const Code_For_Ast & rhs) {

}
