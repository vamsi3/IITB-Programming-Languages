#include "icode.hh"

template class Const_Opd<double>;
template class Const_Opd<int>;

#define ICODE_ALIGN_SPACE "        "
#define ICODE_SPACE "          "

///////////////////////// Instruction Descriptor ///////////////////////////////////


// ============ Instruction_Descriptor =========================================

Instruction_Descriptor::Instruction_Descriptor(Tgt_Op op, string name, string mnn, string ics, Icode_Format icf, Assembly_Format af) {
    this->inst_op = op;
    this->mnemonic = mnn;
    this->ic_symbol = ics;
    this->name = name;
    this->ic_format = icf;
    this->assem_format = af;
}

Instruction_Descriptor::Instruction_Descriptor() {

}

Tgt_Op Instruction_Descriptor::get_op() {
    return this->inst_op;
}

string Instruction_Descriptor::get_name() {
    return this->name;
}

string Instruction_Descriptor::get_mnemonic() {
    return this->mnemonic;
}

string Instruction_Descriptor::get_ic_symbol() {
    return this->ic_symbol;
}

Icode_Format Instruction_Descriptor::get_ic_format() {
    return this->ic_format;
}

Assembly_Format Instruction_Descriptor::get_assembly_format() {
    return this->assem_format;
}



///////////////////////////// Icode statement operand ///////////////////////////////////


// ============ Ics_Opd ========================================================

Register_Descriptor * Ics_Opd::get_reg() {}


// ============ Mem_Addr_Opd ===================================================

Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se) {
    this->symbol_entry = &se;
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer) {
    file_buffer << this->symbol_entry->get_variable_name();
}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer) {
    file_buffer << "[Mem_Addr_Opd][print_asm_opd]" << endl;
}

Mem_Addr_Opd & Mem_Addr_Opd::operator=(const Mem_Addr_Opd & rhs) {
    if (this != &rhs) {
        *this->symbol_entry = *rhs.symbol_entry;
    }
    return *this;
}


// ============ Register_Addr_Opd ==============================================

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd) {
    this->register_description = rd;
}

Register_Descriptor * Register_Addr_Opd::get_reg() {
    return this->register_description;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer) {
    file_buffer << this->register_description->get_name();

}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer) {
    file_buffer << "[Register_Addr_Opd][print_asm_opd]" << endl;

}

Register_Addr_Opd & Register_Addr_Opd::operator=(const Register_Addr_Opd & rhs) {
    if (this != &rhs) {
        *this->register_description = *rhs.register_description;
    }
    return *this;
}


// ============ Const_Opd ======================================================

template <class T>
Const_Opd<T>::Const_Opd(T num) {
    this->num = num;
}

template <class T>
void Const_Opd<T>::print_ics_opd(ostream & file_buffer) {
    file_buffer << this->num;
}

template <class T>
void Const_Opd<T>::print_asm_opd(ostream & file_buffer) {
    file_buffer << "[Const_Opd][print_asm_opd]" << endl;
}

template <class T>
Const_Opd<T> & Const_Opd<T>::operator=(const Const_Opd<T> & rhs) {
    if (this != &rhs) {
        this->num = rhs.num;
    }
    return *this;
}



///////////////////////////////// Intermediate code statements //////////////////////////


// ============ Icode_Stmt =====================================================

Instruction_Descriptor & Icode_Stmt::get_op() {
    return this->op_desc;
}

Ics_Opd * Icode_Stmt::get_opd1() {}

Ics_Opd * Icode_Stmt::get_opd2() {}

Ics_Opd * Icode_Stmt::get_result() {}

void Icode_Stmt::set_opd1(Ics_Opd * io) {}

void Icode_Stmt::set_opd2(Ics_Opd * io) {}

void Icode_Stmt::set_result(Ics_Opd * io) {}


// ============ Move_IC_Stmt ===================================================

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * result) {
    this->op_desc = *machine_desc_object.spim_instruction_table[inst_op];
    this->opd1 = opd1;
    this->result = result;
}

Move_IC_Stmt & Move_IC_Stmt::operator=(const Move_IC_Stmt & rhs) {
    if (this != &rhs) {
        this->op_desc = rhs.op_desc;
        *this->opd1 = *rhs.opd1;
        *this->result = *rhs.result;
    }
    return *this;
}

Instruction_Descriptor & Move_IC_Stmt::get_inst_op_of_ics() {
    return this->op_desc;
}

Ics_Opd * Move_IC_Stmt::get_opd1() {
    return this->opd1;
}

void Move_IC_Stmt::set_opd1(Ics_Opd * io) {
    this->opd1 = io;
}

Ics_Opd * Move_IC_Stmt::get_result() {
    return this->result;
}

void Move_IC_Stmt::set_result(Ics_Opd * io) {
    this->result = io;
}

void Move_IC_Stmt::print_icode(ostream & file_buffer) {
    file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
    this->result->print_ics_opd(file_buffer);
    file_buffer << " <- "; 
    this->opd1->print_ics_opd(file_buffer);
    file_buffer << endl;
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer) {
    file_buffer << "[Move_IC_Stmt][print_icode] " << this->op_desc.get_mnemonic() << endl;
}


// ============ Compute_IC_Stmt ================================================

Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * opd2, Ics_Opd * result) {
    this->op_desc = *machine_desc_object.spim_instruction_table[inst_op];
    this->opd1 = opd1;
    this->opd2 = opd2;
    this->result = result;
}

Compute_IC_Stmt & Compute_IC_Stmt::operator=(const Compute_IC_Stmt & rhs) {
    if (this != &rhs) {
        this->op_desc = rhs.op_desc;
        *this->opd1 = *rhs.opd1;
        *this->opd2 = *rhs.opd2;
        *this->result = *rhs.result;
    }
    return *this;
}

Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics() {
    return this->op_desc;
}

Ics_Opd * Compute_IC_Stmt::get_opd1() {
    return this->opd1;
}

void Compute_IC_Stmt::set_opd1(Ics_Opd * io) {
    this->opd1 = io;
}

Ics_Opd * Compute_IC_Stmt::get_opd2() {
    return this->opd2;
}

void Compute_IC_Stmt::set_opd2(Ics_Opd * io) {
    this->opd2 = io;
}

Ics_Opd * Compute_IC_Stmt::get_result() {
    return this->result;
}

void Compute_IC_Stmt::set_result(Ics_Opd * io) {
    this->result = io;
}

void Compute_IC_Stmt::print_icode(ostream & file_buffer) {
    file_buffer << "[Compute_IC_Stmt][print_icode] " << this->op_desc.get_name() << endl;
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer) {
    file_buffer << "[Compute_IC_Stmt][print_assembly] " << this->op_desc.get_mnemonic() << endl;
}


// ============ Control_Flow_IC_Stmt ===========================================

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, string label) {
    this->op_desc = *machine_desc_object.spim_instruction_table[inst_op];
    this->opd1 = opd1;
    this->label = label;
}

Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs) {
    if (this != &rhs) {
        this->op_desc = rhs.op_desc;
        *this->opd1 = *rhs.opd1;
        this->label = rhs.label;
    }
    return *this;
}

Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics() {
    return this->op_desc;
}

Ics_Opd * Control_Flow_IC_Stmt::get_opd1() {
    return this->opd1;
}

void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io) {
    this->opd1 = io;
}

string Control_Flow_IC_Stmt::get_label() {
    return this->label;
}

void Control_Flow_IC_Stmt::set_label(string label) {
    this->label = label;
}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer) {
    file_buffer << "[Control_Flow_IC_Stmt][print_icode] " << this->op_desc.get_name() << endl;
}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer) {
    file_buffer << "[Control_Flow_IC_Stmt][print_assembly] " << this->op_desc.get_mnemonic() << endl;
}


// ============ Label_IC_Stmt ==================================================

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string label) {
    this->op_desc = *machine_desc_object.spim_instruction_table[inst_op];
    this->label = label;
}

Label_IC_Stmt & Label_IC_Stmt::operator=(const Label_IC_Stmt & rhs) {
    if (this != &rhs) {
        this->op_desc = rhs.op_desc;
        this->label = rhs.label;
    }
    return *this;
}

Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics() {
    return this->op_desc;
}

string Label_IC_Stmt::get_label() {
    return this->label;
}

void Label_IC_Stmt::set_label(string label) {
    this->label = label;
}

void Label_IC_Stmt::print_icode(ostream & file_buffer) {
    file_buffer << "[Label_IC_Stmt][print_icode] " << this->op_desc.get_name() << endl;
}

void Label_IC_Stmt::print_assembly(ostream & file_buffer) {
    file_buffer << "[Label_IC_Stmt][print_assembly] " << this->op_desc.get_mnemonic() << endl;
}



//////////////////////// Intermediate code for Ast statements ////////////////////////


// ============ Code_For_Ast ===================================================

Code_For_Ast::Code_For_Ast() {
    this->ics_list = list<Icode_Stmt *>();
    this->result_register = new Register_Descriptor(none, "dummy", int_num, int_reg);
}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg) {
    this->ics_list = ic_l;
    if (reg) {
        this->result_register = reg;
    }
    else {
        this->result_register = new Register_Descriptor(none, "dummy", int_num, int_reg);
    }
}

void Code_For_Ast::append_ics(Icode_Stmt & ics) {
    this->ics_list.push_back(&ics);
}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list() {
    return this->ics_list;
}

Register_Descriptor * Code_For_Ast::get_reg() {
    return this->result_register;
}

void Code_For_Ast::set_reg(Register_Descriptor * reg) {
    this->result_register = reg;
}

Code_For_Ast & Code_For_Ast::operator=(const Code_For_Ast & rhs) {
    if (this != &rhs) {
        this->ics_list = rhs.ics_list;
        *this->result_register = *rhs.result_register;
    }
    return *this;
}
