#include "icode.hh"

template class Const_Opd<double>;
template class Const_Opd<int>;

#define ICODE_ALIGN_SPACE "\t"
#define ICODE_SPACE "    \t"

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
    auto ref_offset = this->symbol_entry->get_ref_offset();
    Spim_Register spim_reg;
    if (ref_offset == fp_ref) {
        spim_reg = fp;
    }
    else if (ref_offset == sp_ref) {
        spim_reg = sp;
    }
    this->symbol_entry->set_register(machine_desc_object.spim_register_table[spim_reg]);
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer) {
    file_buffer << this->symbol_entry->get_variable_name();
}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer) {
    auto scope = this->symbol_entry->get_symbol_scope();
    if (scope == global) {
        file_buffer << this->symbol_entry->get_variable_name();
    }
    else if (scope == formal || scope == local) {
        file_buffer << this->symbol_entry->get_start_offset();
        file_buffer << "($" << this->symbol_entry->get_register()->get_name() << ")";
    }
}

Mem_Addr_Opd & Mem_Addr_Opd::operator=(const Mem_Addr_Opd & rhs) {
    if (this != &rhs) {
        *this->symbol_entry = *rhs.symbol_entry;
    }
    return *this;
}


// ============ Register_Addr_Opd ==============================================

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd) {
    this->register_description = (rd)? rd : new Register_Descriptor(none, "dummy", int_num, int_reg);
}

Register_Descriptor * Register_Addr_Opd::get_reg() {
    return this->register_description;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer) {
    file_buffer << this->register_description->get_name();
}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer) {
    file_buffer << "$" << this->register_description->get_name();

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
    file_buffer << this->num;
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


// ============ Print_IC_Stmt ===================================================

Print_IC_Stmt::Print_IC_Stmt() {}

void Print_IC_Stmt::print_icode(ostream & file_buffer) {
    file_buffer << ICODE_ALIGN_SPACE << machine_desc_object.spim_instruction_table[print]->get_name() << endl;
}

void Print_IC_Stmt::print_assembly(ostream & file_buffer) {
    file_buffer << ICODE_ALIGN_SPACE << machine_desc_object.spim_instruction_table[print]->get_mnemonic() << endl;
}


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
    auto ic_format = this->get_inst_op_of_ics().get_ic_format();
    if (ic_format == i_r_op_o1) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
        this->result->print_ics_opd(file_buffer);
        file_buffer << " <- "; 
        this->opd1->print_ics_opd(file_buffer);
        file_buffer << endl;
    }
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer) {
    auto asm_format = this->get_inst_op_of_ics().get_assembly_format();
    if (asm_format == a_op_r_o1) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " ";  this->result->print_asm_opd(file_buffer);
        file_buffer << ", "; this->opd1->print_asm_opd(file_buffer);
        file_buffer << endl;
    }
    else if (asm_format == a_op_o1_r) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " "; this->opd1->print_asm_opd(file_buffer);
        file_buffer << ", ";  this->result->print_asm_opd(file_buffer);
        file_buffer << endl;
    }
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
    auto ic_format = this->get_inst_op_of_ics().get_ic_format();
    if (ic_format == i_r_o1_op_o2) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
        this->result->print_ics_opd(file_buffer);
        file_buffer << " <- "; 
        this->opd1->print_ics_opd(file_buffer);
        file_buffer << " , ";
        this->opd2->print_ics_opd(file_buffer);
        file_buffer << endl;
    }
    else if (ic_format == i_o1_op_o2) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
        this->opd1->print_ics_opd(file_buffer);
        file_buffer << " , ";
        this->opd2->print_ics_opd(file_buffer);
        file_buffer << endl;
    }
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer) {
    auto asm_format = this->get_inst_op_of_ics().get_assembly_format();
    if (asm_format == a_op_r_o1_o2) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " ";  this->result->print_asm_opd(file_buffer);
        file_buffer << ", "; this->opd1->print_asm_opd(file_buffer);
        file_buffer << ", "; this->opd2->print_asm_opd(file_buffer);
        file_buffer << endl;
    }
    else if (asm_format == a_op_o1_o2) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " "; this->opd1->print_asm_opd(file_buffer);
        file_buffer << ", "; this->opd2->print_asm_opd(file_buffer);
        file_buffer << endl; 
    }
}


// ============ Control_Flow_IC_Stmt ===========================================

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * o2, string label, int size) {
    this->op_desc = *machine_desc_object.spim_instruction_table[op];
    this->opd1 = o1;
    this->opd2 = o2;
    this->offset = label;
    this->actual_param_size = size;
}

Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs) {
    if (this != &rhs) {
        this->op_desc = rhs.op_desc;
        *this->opd1 = *rhs.opd1;
        this->offset = rhs.offset;
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

Ics_Opd * Control_Flow_IC_Stmt::get_opd2() {
    return this->opd2;
}

void Control_Flow_IC_Stmt::set_opd2(Ics_Opd * io) {
    this->opd2 = io;
}

string Control_Flow_IC_Stmt::get_Offset() {
    return this->offset;
}

void Control_Flow_IC_Stmt::set_Offset(string label) {
    this->offset = label;
}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer) {
    auto ic_format = this->get_inst_op_of_ics().get_ic_format();
    if (ic_format == i_op_st) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
        file_buffer << " " << this->offset;
        file_buffer << endl;
    }
    else if (ic_format == i_op_o1_o2_st) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name() << ":" << ICODE_SPACE;
        this->opd1->print_ics_opd(file_buffer); file_buffer << " , "; this->opd2->print_ics_opd(file_buffer);
        file_buffer << " : ";
        file_buffer << "goto " << this->offset;
        file_buffer << endl;
    }
}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer) {
    auto asm_format = this->get_inst_op_of_ics().get_assembly_format();
    if (asm_format == a_op_o1_o2_st) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " "; this->opd1->print_asm_opd(file_buffer);
        file_buffer << ", "; this->opd2->print_asm_opd(file_buffer);
        file_buffer << ", " << this->offset;
        file_buffer << endl;
    }
    else if (asm_format == a_op_st) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic();
        file_buffer << " " << this->offset;
        file_buffer << endl;
    }
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
    auto op_type = this->op_desc.get_op();
    if (op_type == j) {
        file_buffer << ICODE_ALIGN_SPACE << "goto " << this->label;
    }
    else if (op_type == jal) {
        file_buffer << ICODE_ALIGN_SPACE << "call " << this->label;
    }
    else if (op_type == ret_inst) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_name();
    }
    else {
        file_buffer << endl << this->label << ":";
    }
    file_buffer << endl;
}

void Label_IC_Stmt::print_assembly(ostream & file_buffer) {
    auto op_type = this->op_desc.get_op();
    if (op_type == j) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic() << " " << this->label;
    }
    else if (op_type == jal) {
        file_buffer << ICODE_ALIGN_SPACE << this->op_desc.get_mnemonic() << " " << this->label;
    }
    else if (op_type == ret_inst) {
        file_buffer << ICODE_ALIGN_SPACE << "j " << this->label;
    }
    else {
        file_buffer << endl << this->label << ":";
    }
    file_buffer << endl;
}



//////////////////////// Intermediate code for Ast statements ////////////////////////


// ============ Code_For_Ast ===================================================

Code_For_Ast::Code_For_Ast() {
    this->ics_list = list<Icode_Stmt *>();
    this->result_register = new Register_Descriptor(none, "dummy", int_num, int_reg);
}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg) {
    this->ics_list = ic_l;
    this->result_register = (reg)? reg : new Register_Descriptor(none, "dummy", int_num, int_reg);
}

void Code_For_Ast::append_ics(Icode_Stmt & ics) {
    this->ics_list.push_back(&ics);
}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list() {
    return this->ics_list;
}

void Code_For_Ast::set_icode_list(list<Icode_Stmt *> * ic_list_new) {
    this->ics_list = *ic_list_new;
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
