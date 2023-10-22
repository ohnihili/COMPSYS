#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset) {
    if (segment == "constant") {
        // For constant values, push the value onto the stack.
        return "@" + to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "local") {
        // Handle the local segment.
        return "@LCL\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "argument") {
        // Handle the argument segment.
        return "@ARG\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "this") {
        // Handle the this segment.
        return "@THIS\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "that") {
        // Handle the that segment.
        return "@THAT\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "temp") {
        // Handle the temp segment.
        return "@5\nD=A\n@" + to_string(offset + 5) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "pointer") {
        // Handle the pointer segment.
        if (offset == 0) {
            return "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        } else if (offset == 1) {
            return "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        }
    }
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
    return "";
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}