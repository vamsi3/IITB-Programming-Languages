#include "local-environment.hh"


// ==================== Local_Environment ======================

Local_Environment::Local_Environment() {

}

Local_Environment::~Local_Environment() {

}

void Local_Environment::print(ostream & file_buffer) {
    for (const auto &entry: this->variable_table) {
        auto variable_name = entry.first;
        auto result = entry.second;

        if (!result->is_variable_defined()) {
            file_buffer << VAR_SPACE << entry.first << " : " << "undefined" << endl;
        }
        else {
            Result_Enum result_type = entry.second->get_result_enum();
            if (result_type == int_result) {
                file_buffer << VAR_SPACE << variable_name << " : " << result->get_int_value() << endl;
            }
            else if (result_type == double_result) {
                file_buffer << VAR_SPACE << variable_name << " : " << result->get_double_value() << endl;
            }
        }

    }
}

bool Local_Environment::is_variable_defined(string name) {
    return this->does_variable_exist(name) && this->get_variable_value(name)->is_variable_defined();
}

Eval_Result * Local_Environment::get_variable_value(string name) {
    return this->variable_table.at(name);
}

void Local_Environment::put_variable_value(Eval_Result & value, string name) {
    this->variable_table[name] = &value;
}

bool Local_Environment::does_variable_exist(string name) {
    return this->variable_table.find(name) != this->variable_table.end();
}


// ==================== Symbol_Table ======================


#include "symbol-table.hh"

void Symbol_Table::create(Local_Environment & local_global_variables_table) {
    for (const auto &entry: this->variable_table) {
        auto variable_name = entry->get_variable_name();
        auto variable_data_type = entry->get_data_type();

        Eval_Result* result;
        if (variable_data_type == int_data_type) {
            result = new Eval_Result_Value_Int;
        }
        else if (variable_data_type == double_data_type) {
            result = new Eval_Result_Value_Double;
        }

        if (entry->get_symbol_scope() == global) {
            result->set_variable_status(true);
            result->set_value(0);
        }
        local_global_variables_table.put_variable_value(*result, variable_name);
    }
}


// ==================== Eval_Result ======================

int Eval_Result::get_int_value() {
    return 0;
}

void Eval_Result::set_value(int value) {

}

double Eval_Result::get_double_value() {
    return 0.0;
}

void Eval_Result::set_value(double value) {

}

bool Eval_Result::is_variable_defined() {
    return false;
}

void Eval_Result::set_variable_status(bool def) {

}


// ==================== Eval_Result_Value ======================

void Eval_Result_Value::set_value(int value) {

}

void Eval_Result_Value::set_value(double value) {

}

int Eval_Result_Value::get_int_value() {
    return 0;
}

double Eval_Result_Value::get_double_value() {
    return 0.0;
}

// ==================== Eval_Result_Value_Int ======================

Eval_Result_Value_Int::Eval_Result_Value_Int() {
    this->set_result_enum(int_result);
    this->set_variable_status(false);
    this->set_value(0);
}

Eval_Result_Value_Int::~Eval_Result_Value_Int() {

}

void Eval_Result_Value_Int::set_value(int number) {
    this->value = number;
}

void Eval_Result_Value_Int::set_value(double number) {
    this->value = number;
}

int Eval_Result_Value_Int::get_int_value() {
    return this->value;
}

void Eval_Result_Value_Int::set_variable_status(bool def) {
    this->defined = def;
}

bool Eval_Result_Value_Int::is_variable_defined() {
    return this->defined;
}

void Eval_Result_Value_Int::set_result_enum(Result_Enum res) {
    this->result_type = res;
}

Result_Enum Eval_Result_Value_Int::get_result_enum() {
    return this->result_type;
}


// ==================== Eval_Result_Value_Double ======================

Eval_Result_Value_Double::Eval_Result_Value_Double() {
    this->set_result_enum(double_result);
    this->set_variable_status(false);
    this->set_value(0.0);
}

Eval_Result_Value_Double::~Eval_Result_Value_Double() {

}

void Eval_Result_Value_Double::set_value(int number) {
    this->value = number;
}

void Eval_Result_Value_Double::set_value(double number) {
    this->value = number;
}

double Eval_Result_Value_Double::get_double_value() {
    return this->value;
}

void Eval_Result_Value_Double::set_variable_status(bool def) {
    this->defined = def;
}

bool Eval_Result_Value_Double::is_variable_defined() {
    return this->defined;
}

void Eval_Result_Value_Double::set_result_enum(Result_Enum res) {
    this->result_type = res;
}

Result_Enum Eval_Result_Value_Double::get_result_enum() {
    return this->result_type;
}
