#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "antlr4-runtime.h"
#include "PLDCOMPLexer.h"
#include "PLDCOMPParser.h"
#include "PLDCOMPBaseVisitor.h"

#include "Visitor.h"
#include "Programme.h"
#include "ConstructionIR.h"

using namespace antlr4;
using namespace std;

string baseURL = "./Tests/FrontEndTests/";
string backEndTestUrl = "./Tests/BackEndTests/";

vector<string> lexErrorFiles = {
    baseURL + "LexError/01_LexError_InvalidCharInStream.c",
    baseURL + "LexError/02_LexError_InvalidCharInStreamWithinProgram.c"
};

vector<string> semanticErrorFiles = {
    baseURL + "SemanticError/01_MissingVarDeclaration.c",
    baseURL + "SemanticError/02_MissingFuncDeclaration.c"
};

vector<string> syntaxErrorFiles = {
    baseURL + "SyntaxError/01_SyntaxError_TwoOperators.c",
    baseURL + "SyntaxError/02_SyntaxError_TwoOperands.c",
    baseURL + "SyntaxError/03_SyntaxError_MissingSemicolon.c",
    baseURL + "SyntaxError/04_SyntaxError_MissingPar.c",
    baseURL + "SyntaxError/05_SyntaxError_TooManyClosingPar.c"
};

vector<string> validProgramsFiles = {
    baseURL + "validPrograms/01_SimpleDeclaration.c",
    baseURL + "validPrograms/02_IncludeStdint.c",
    baseURL + "validPrograms/03_OperatorPlus.c",
    baseURL + "validPrograms/04_OperatorMinus.c",
    baseURL + "validPrograms/05_OperatorDiv.c",
    baseURL + "validPrograms/06_OperatorMult.c",
    baseURL + "validPrograms/07_OperatorInf.c",
    baseURL + "validPrograms/08_OperatorSup.c",
    baseURL + "validPrograms/09_OperatorLeq.c",
    baseURL + "validPrograms/10_OperatorGeq.c",
    baseURL + "validPrograms/11_OperatorEqu.c",
    baseURL + "validPrograms/12_OperatorDiff.c",
    baseURL + "validPrograms/13_OperatorMod.c",
    baseURL + "validPrograms/14_OperatorAnd.c",
    baseURL + "validPrograms/15_OperatorOr.c",
    baseURL + "validPrograms/16_OperatorBOr.c",
    baseURL + "validPrograms/17_OperatorBAnd.c",
    baseURL + "validPrograms/18_OperatorNeg.c",
    baseURL + "validPrograms/19_OperatorLeftShift.c",
    baseURL + "validPrograms/20_OperatorRightShift.c",
    baseURL + "validPrograms/21_OperatorIncPost.c",
    baseURL + "validPrograms/22_OperatorIncPre.c",
    baseURL + "validPrograms/23_OperatorDecPost.c",
    baseURL + "validPrograms/24_OperatorDecPre.c",
    baseURL + "validPrograms/25_OperatorNot.c",
    baseURL + "validPrograms/26_OperatorXor.c",
    baseURL + "validPrograms/27_OperatorComp.c",
    baseURL + "validPrograms/28_OperatorPlusAssign.c",
    baseURL + "validPrograms/29_OperatorMinusAssign.c",
    baseURL + "validPrograms/30_OperatorMultAssign.c",
    baseURL + "validPrograms/31_OperatorDivAssign.c",
    baseURL + "validPrograms/32_OperatorModAssign.c",
    baseURL + "validPrograms/33_OperatorBitAndAssign.c",
    baseURL + "validPrograms/34_OperatorBitOrAssign.c",
    baseURL + "validPrograms/35_OperatorBitXorAssign.c",
    baseURL + "validPrograms/36_OperatorComma.c",
    baseURL + "validPrograms/37_Par.c",
    baseURL + "validPrograms/38_ArithmeticExpression.c",
    baseURL + "validPrograms/39_ArithmeticExpressionWithPar.c",
    baseURL + "validPrograms/40_If.c",
    baseURL + "validPrograms/41_IfElse.c",
    baseURL + "validPrograms/42_While.c",
    baseURL + "validPrograms/44_IfElseIf.c",
    baseURL + "validPrograms/46_ArrayDec.c",
    baseURL + "validPrograms/47_ArrayUse.c",
    // baseURL + "validPrograms/49_ArrayFibo.c",      // On ne gère pas les "for"
    baseURL + "validPrograms/50_CharConst.c",
    baseURL + "validPrograms/51_CharConstSpecial.c",
    baseURL + "validPrograms/52_Int64Dec.c",
    baseURL + "validPrograms/53_FunctionCallPutChar.c",
    baseURL + "validPrograms/54_FunctionCallCustom.c",
    baseURL + "validPrograms/55_Return.c",
    // baseURL + "validPrograms/56_ArrayAsParam.c",   // On ne gère pas les "for"
    baseURL + "validPrograms/57_VarInitialization.c",
    baseURL + "validPrograms/58_MultipleVarDeclarations.c",
    baseURL + "validPrograms/59_MixedDeclarationsInitializations.c",
};

vector<string> backEndFiles = {
    backEndTestUrl + "1_decls",
    backEndTestUrl + "1_empty",
    backEndTestUrl + "2_putchar",
    backEndTestUrl + "3_variables",
    backEndTestUrl + "4-VarConstAddCall",
    backEndTestUrl + "5-IfThenElse",
    backEndTestUrl + "6-While",
    backEndTestUrl + "7-testWhileAndVariables",
    backEndTestUrl + "8-Return",
    backEndTestUrl + "9-lvalueGenerale",
    backEndTestUrl + "10-appel6Argument",
    backEndTestUrl + "11-checkPriority",
    backEndTestUrl + "12-testParenthese",
    backEndTestUrl + "13-factorielleRecursive"
};

tree::ParseTree * treeInitialization (string cppCode) {
    ANTLRInputStream input (cppCode);
    PLDCOMPLexer lexer (&input);
    CommonTokenStream token (&lexer);
    PLDCOMPParser parser (&token);
    tree::ParseTree * tree = parser.programme();
    return tree;
}

void lexErrorTests () {
    cout << endl << "\033[1;32m[ TESTS DU LEXER ]\033[0m\n" << endl;
    for (int i=0 ; i<lexErrorFiles.size() ; i++) {
        cout << "\033[4;36mFichier :" << lexErrorFiles[i] << "\033[0m\n";

        ifstream file(lexErrorFiles[i]);
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

        ANTLRInputStream input (content);
        PLDCOMPLexer lexer (&input);
        CommonTokenStream token (&lexer);
        PLDCOMPParser parser (&token);
        tree::ParseTree * tree = parser.programme();

        Visitor visitor;
        Programme * prog = (Programme *) visitor.visit(tree);

        prog->resolutionPortee();
        // prog->affiche();
        // cout << endl;
    }
}

void semanticErrorTests () {
    cout << endl << "\033[1;32m[ TESTS SÉMANTIQUES ]\033[0m\n" << endl;
    for (int i=0 ; i<semanticErrorFiles.size() ; i++) {
        cout << "\033[4;36mFichier :" << semanticErrorFiles[i] << "\033[0m\n";

        ifstream file(semanticErrorFiles[i]);
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        ANTLRInputStream input (content);
        PLDCOMPLexer lexer (&input);
        CommonTokenStream token (&lexer);
        PLDCOMPParser parser (&token);
        tree::ParseTree * tree = parser.programme();

        Visitor visitor;
        Programme * prog = (Programme *) visitor.visit(tree);

        // prog->affiche();
        prog->resolutionPortee();
        // cout << endl;
    }
}

void syntaxErrorTests () {
    cout << endl << "\033[1;32m[ TESTS DE SYNTAXE ]\033[0m\n" << endl;
    for (int i=0 ; i<syntaxErrorFiles.size() ; i++) {
        cout << "\033[4;36mFichier :" << syntaxErrorFiles[i] << "\033[0m\n";

        ifstream file(syntaxErrorFiles[i]);
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        ANTLRInputStream input (content);
        PLDCOMPLexer lexer (&input);
        CommonTokenStream token (&lexer);
        PLDCOMPParser parser (&token);
        tree::ParseTree * tree = parser.programme();

        Visitor visitor;
        Programme * prog = (Programme *) visitor.visit(tree);

        prog->resolutionPortee();
        // prog->affiche();
        // cout << endl;

    }
}

void validProgramsTests () {
    cout << endl << "\033[1;32m[ TESTS DE CODES VALIDES ]\033[0m\n" << endl;
    for (int i=0 ; i<validProgramsFiles.size() ; i++) {
        cout << "\033[4;36mFichier :" << validProgramsFiles[i] << "\033[0m\n";

        ifstream file(validProgramsFiles[i]);
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        ANTLRInputStream input (content);
        PLDCOMPLexer lexer (&input);
        CommonTokenStream token (&lexer);
        PLDCOMPParser parser (&token);
        tree::ParseTree * tree = parser.programme();

        Visitor visitor;
        Programme * prog = (Programme *) visitor.visit(tree);

        // prog->affiche();
        prog->resolutionPortee();
        // cout << endl;
    }
}

void backEndTests() {
    cout << endl << "\033[1;32m[ BACK END TESTS ]\033[0m\n" << endl;
    for (int i=0 ; i<backEndFiles.size() ; i++) {
        cout << "\033[4;36mFichier :" << backEndFiles[i] << "\033[0m\n";

        ifstream file(backEndFiles[i] + ".c");
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        ANTLRInputStream input (content);
        PLDCOMPLexer lexer (&input);
        CommonTokenStream token (&lexer);
        PLDCOMPParser parser (&token);
        tree::ParseTree * tree = parser.programme();
        ConstructionIR constr;

        Visitor visitor;
        Programme * prog = (Programme *) visitor.visit(tree);
        // prog->resolutionPortee();

        constr.analyseProgramme(prog, backEndFiles[i]);

        cout << endl;

    }
}

int main () {
    // Partie pour tester en Input
    /*ANTLRInputStream input ("#include<inttypes.h>\r\nvoid main(void) {\r\nchar a;\r\na='M';\r\nputchar(a);\r\nputchar('O');\r\nputchar('K');\r\nputchar(' ');\r\n}");
    PLDCOMPLexer lexer (&input);
    CommonTokenStream token (&lexer);
    PLDCOMPParser parser (&token);
    ConstructionIR constr;

    tree::ParseTree * tree = parser.programme();
    Visitor visitor;

    Programme * prog = (Programme *) visitor.visit(tree);

    prog->affiche();
    prog->resolutionPortee();
    constr.analyseProgramme(prog);*/

    lexErrorTests();
    syntaxErrorTests();
    validProgramsTests();
    semanticErrorTests();
    backEndTests();

    return 0;
}
