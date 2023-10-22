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
        return "@" + to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "local") {
        return "@LCL\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "argument") {
        return "@ARG\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "this") {
        return "@THIS\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "that") {
        return "@THAT\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "temp") {
        return to_string(offset) + "\nD=A+5\n@SP\nA=M\nM=D\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "pointer") {
        if (offset == 0) {
            return "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        } else if (offset == 1) {
            return "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        }
    }

    return "";
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
if (segment == "local") {
        return "@LCL\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "argument") {
        return "@ARG\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "this") {
        return "@THIS\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "that") {
        return "@THAT\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "temp") {
        return "@5\nD=A\n@" + to_string(offset + 5) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "pointer") {
        if (offset == 0) {
            return "@THIS\n@SP\nM=M-1\nA=M\nD=M\n@THIS\nM=D\n";
        } else if (offset == 1) {
            return "@THAT\n@SP\nM=M-1\nA=M\nD=M\n@THAT\nM=D\n";
        }
    }

    return "";
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add() {
    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=M+D\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub() {
    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=M-D\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg() {
    return "@SP\nM=M-1\nA=M\nM=-M\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
    static int eqCounter = 0;
    string eqLabel = "EQ_TRUE_" + to_string(eqCounter);
    string eqEndLabel = "EQ_END_" + to_string(eqCounter);
    eqCounter++;

    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nD=D-M\n@" + eqLabel + "\nD;JEQ\n@SP\nA=M\nM=0\n@" + eqEndLabel + "\n0;JMP\n(" + eqLabel + ")\n@SP\nA=M\nM=-1\n(" + eqEndLabel + ")\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt() {
    static int gtCounter = 0;
    string gtLabel = "GT_TRUE_" + to_string(gtCounter);
    string gtEndLabel = "GT_END_" + to_string(gtCounter);
    gtCounter++;

    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nD=M-D\n@" + gtLabel + "\nD;JGT\n@SP\nA=M\nM=0\n@" + gtEndLabel + "\n0;JMP\n(" + gtLabel + ")\n@SP\nA=M\nM=-1\n(" + gtEndLabel + ")\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt() {
    static int ltCounter = 0;
    string ltLabel = "LT_TRUE_" + to_string(ltCounter);
    string ltEndLabel = "LT_END_" + to_string(ltCounter);
    ltCounter++;

    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nD=M-D\n@" + ltLabel + "\nD;JLT\n@SP\nA=M\nM=0\n@" + ltEndLabel + "\n0;JMP\n(" + ltLabel + ")\n@SP\nA=M\nM=-1\n(" + ltEndLabel + ")\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and() {
    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D&M\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or() {
    return "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D|M\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not() {
    return "@SP\nM=M-1\nA=M\nM=!M\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label) {
    return "(" + label + ")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label) {
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label) {
    return "@SP\nM=M-1\nA=M\nD=M\n@" + label + "\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars) {
    string functionLabel = function_name + "$" + to_string(n_vars);
    string code = "(" + functionLabel + ")\n";
    for (int i = 0; i < n_vars; i++) {
        code += "@0\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    return code;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args) {
    static int callCounter = 0;
    string returnLabel = "RETURN_LABEL_" + to_string(callCounter);
    callCounter++;

    string code = "@" + returnLabel + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    code += "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

    // Reposition ARG for the called function.
    code += "@SP\nD=M\n@" + to_string(n_args + 5) + "\nD=D-A\n@ARG\nM=D\n";

    // Reposition LCL for the called function.
    code += "@SP\nD=M\n@LCL\nM=D\n";

    // Jump to the function label.
    code += "@" + function_name + "\n0;JMP\n";

    // Define the return label.
    code += "(" + returnLabel + ")\n";

    return code;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return() {
    string code = "@5\nD=A\n@LCL\nA=M-D\nD=M\n@R13\nM=D\n";

    code += "@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n";

    code += "@ARG\nD=M+1\n@SP\nM=D\n";

    code += "@LCL\nD=M\n@THAT\nM=D\n";
    code += "@LCL\nD=M\n@THIS\nM=D\n";
    code += "@LCL\nD=M\n@ARG\nM=D\n";
    code += "@LCL\nD=M\n@LCL\nM=D\n";

    code += "@R13\nA=M\n0;JMP\n";

    return code;
}