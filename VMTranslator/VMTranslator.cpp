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
    if (segment == "static"){
        return "@" + to_string(16 + offset) + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

    } else if (segment == "constant") {
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
        return "@R5\nD=A\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

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
    if (segment == "static") {
        return "@SP\nM=M-1\nA=M\nD=M\n@" + to_string(16 + offset) + "\nM=D\n";
    } else if (segment == "local") {
        return "@LCL\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "argument") {
        return "@ARG\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "this") {
        return "@THIS\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "that") {
        return "@THAT\nD=M\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
    } else if (segment == "temp") {
        return "@R5\nD=A\n@" + to_string(offset) + "\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";
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
    string assemblyCode;
    
    assemblyCode += "(" + function_name + ")\n";
 
    for (int i = 0; i < n_vars; i++) {
        assemblyCode += "@0\n";
        assemblyCode += "D=0\n";
        assemblyCode += "@SP\n"; 
        assemblyCode += "A=M\n";
        assemblyCode += "M=D\n";
        assemblyCode += "@SP\n"; 
        assemblyCode += "M=M+1\n";
    }

    return assemblyCode;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args) {
 string assemblyCode;
 static int return_label_count = 0;

    string return_label = "RETURN_LABEL_" + to_string(return_label_count);
    return_label_count++;

    assemblyCode += "@" + return_label + "\n";
    assemblyCode += "D=A\n";
    assemblyCode += "@SP\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=M+1\n";


    assemblyCode += "@LCL\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@SP\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=M+1\n";

    assemblyCode += "@ARG\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@SP\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=M+1\n";


    assemblyCode += "@THIS\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@SP\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=M+1\n";


    assemblyCode += "@THAT\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@SP\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=M+1\n";


    assemblyCode += "@SP\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@" + to_string(n_args + 5) + "\n";
    assemblyCode += "D=D-A\n";
    assemblyCode += "@ARG\n";
    assemblyCode += "M=D\n";

    assemblyCode += "@SP\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@LCL\n";
    assemblyCode += "M=D\n";

    assemblyCode += "@" + function_name + "\n";
    assemblyCode += "0;JMP\n";


    assemblyCode += "(" + return_label + ")\n";

    return assemblyCode;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return() {
    string assemblyCode;

    assemblyCode += "@LCL\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@FRAME\n";
    assemblyCode += "M=D\n";

    assemblyCode += "@5\n";
    assemblyCode += "A=D-A\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@RET\n";
    assemblyCode += "M=D\n";

    assemblyCode += "@SP\n";
    assemblyCode += "A=M-1\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@ARG\n";
    assemblyCode += "A=M\n";
    assemblyCode += "M=D\n";


    assemblyCode += "@ARG\n";
    assemblyCode += "D=M+1\n";
    assemblyCode += "@SP\n";
    assemblyCode += "M=D\n";


    assemblyCode += "@FRAME\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@THAT\n";
    assemblyCode += "M=D\n";


    assemblyCode += "@FRAME\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@THIS\n";
    assemblyCode += "M=D\n";


    assemblyCode += "@FRAME\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@ARG\n";
    assemblyCode += "M=D\n";


    assemblyCode += "@FRAME\n";
    assemblyCode += "D=M\n";
    assemblyCode += "@LCL\n";
    assemblyCode += "M=D\n";

    assemblyCode += "@RET\n";
    assemblyCode += "A=M\n";
    assemblyCode += "0;JMP\n";

    return assemblyCode;
}