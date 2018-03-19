#pragma once

#include "antlr4-runtime.h"
#include "PLDCOMPBaseVisitor.h"
#include "Instruction.h"
#include "Declaration.h"
#include "Fonction.h"
#include "Programme.h"
#include <typeinfo>

#include <list>

using namespace std;

class Programme;

class Visitor : public PLDCOMPBaseVisitor {

    antlrcpp::Any visitAdd(PLDCOMPParser::AddContext *ctx) override {
        return (Symbole) ADD;
    }

    antlrcpp::Any visitMoins(PLDCOMPParser::MoinsContext *ctx) override {
        return (Symbole) MOINS;
    }

    antlrcpp::Any visitMult(PLDCOMPParser::MultContext *ctx) override {
        return (Symbole) MULT;
    }

    antlrcpp::Any visitDiv(PLDCOMPParser::DivContext *ctx) override {
        return (Symbole) DIV;
    }

    antlrcpp::Any visitMod(PLDCOMPParser::ModContext *ctx) override {
        return (Symbole) MOD;
    }

    antlrcpp::Any visitPow(PLDCOMPParser::PowContext *ctx) override {
        return (Symbole) POW;
    }

    antlrcpp::Any visitAnd(PLDCOMPParser::AndContext *ctx) override {
        return (Symbole) AND;
    }

    antlrcpp::Any visitOr(PLDCOMPParser::OrContext *ctx) override {
        return (Symbole) OR;
    }

    antlrcpp::Any visitEqual(PLDCOMPParser::EqualContext *ctx) override {
        return (Symbole) EQUAL;
    }

    antlrcpp::Any visitInfs(PLDCOMPParser::InfsContext *ctx) override {
        return (Symbole) INFS;
    }

    antlrcpp::Any visitInf(PLDCOMPParser::InfContext *ctx) override {
        return (Symbole) INF;
    }

    antlrcpp::Any visitSups(PLDCOMPParser::SupsContext *ctx) override {
        return (Symbole) SUPS;
    }

    antlrcpp::Any visitSup(PLDCOMPParser::SupContext *ctx) override {
        return (Symbole) SUP;
    }

    antlrcpp::Any visitDecg(PLDCOMPParser::DecgContext *ctx) override {
        return (Symbole) DECG;
    }

    antlrcpp::Any visitDecd(PLDCOMPParser::DecdContext *ctx) override {
        return (Symbole) DECD;
    }

    antlrcpp::Any visitEqualb(PLDCOMPParser::EqualbContext *ctx) override {
        return (Symbole) EQUALB;
    }

    antlrcpp::Any visitDiff(PLDCOMPParser::DiffContext *ctx) override {
        return (Symbole) DIFF;
    }

    antlrcpp::Any visitAndb(PLDCOMPParser::AndbContext *ctx) override {
        return (Symbole) ANDB;
    }

    antlrcpp::Any visitOrb(PLDCOMPParser::OrbContext *ctx) override {
        return (Symbole) ORB;
    }

    antlrcpp::Any visitAddeq(PLDCOMPParser::AddeqContext *ctx) override {
        return (Symbole) ADDEQ;
    }

    antlrcpp::Any visitMoinseq(PLDCOMPParser::MoinseqContext *ctx) override {
        return (Symbole) MOINSEQ;
    }

    antlrcpp::Any visitMulteq(PLDCOMPParser::MulteqContext *ctx) override {
        return (Symbole) MULTEQ;
    }

    antlrcpp::Any visitDiveq(PLDCOMPParser::DiveqContext *ctx) override {
        return (Symbole) DIVEQ;
    }

    antlrcpp::Any visitModeq(PLDCOMPParser::ModeqContext *ctx) override {
        return (Symbole) MODEQ;
    }

    antlrcpp::Any visitAndeq(PLDCOMPParser::AndeqContext *ctx) override {
        return (Symbole) ANDEQ;
    }

    antlrcpp::Any visitOreq(PLDCOMPParser::OreqContext *ctx) override {
        return (Symbole) OREQ;
    }

    antlrcpp::Any visitXoreq(PLDCOMPParser::XoreqContext *ctx) override {
        return (Symbole) XOREQ;
    }

    antlrcpp::Any visitExpLvalue(PLDCOMPParser::ExpLvalueContext *ctx) override {
        Variable * var = (Variable *) visit(ctx->lvalue());
        return (Expression *) var;
    }

    antlrcpp::Any visitNegation(PLDCOMPParser::NegationContext *ctx) override {
        return (Expression *) new ExprUnaire((Expression*) visit(ctx->exp()), (Symbole) NEGATION);
    }

    antlrcpp::Any visitInvert(PLDCOMPParser::InvertContext *ctx) override {
        return (Expression *) new ExprUnaire((Expression *) visit(ctx->exp()), (Symbole) INVERT);
    }

    antlrcpp::Any visitPpexp(PLDCOMPParser::PpexpContext *ctx) override {
        Variable * var = (Variable *) visit(ctx->lvalue());
        return (Expression *) new ExprUnaire((Expression *) var, (Symbole) PPEXP);
    }

    antlrcpp::Any visitAppelGetchar(PLDCOMPParser::AppelGetcharContext *ctx) override {
        list<Expression> * l = new list<Expression>();
        return (Expression *) new AppelDeFonction("getchar", l);
    }

    antlrcpp::Any visitConstanteNombre(PLDCOMPParser::ConstanteNombreContext *ctx) override {
        return (Expression *) new Nombre((int) stoi(ctx->NOMBRE()->getText()));
    }

    antlrcpp::Any visitParenthese(PLDCOMPParser::ParentheseContext *ctx) override {
        return (Expression *) new ExprUnaire((Expression *) visit(ctx->exp()), (Symbole) PAR);
    }

    antlrcpp::Any visitNon(PLDCOMPParser::NonContext *ctx) override {
        return (Expression *) new ExprUnaire((Expression *) visit(ctx->exp()), (Symbole) NON);
    }

    antlrcpp::Any visitConstanteCaractere(PLDCOMPParser::ConstanteCaractereContext *ctx) override {
        return (Expression *) new Caractere((char) ctx->CHAR()->getText()[0]);
    }

    antlrcpp::Any visitAppelDeFonction(PLDCOMPParser::AppelDeFonctionContext *ctx) override {
        list<Expression> * l = new list<Expression>();
        auto liste = ctx->exp();

        for(auto i=liste.begin();i!=liste.end();i++) {
            Expression * expression = (Expression *) visit(*i);
            l->push_back((Expression) *expression);
        }
        return (Expression *) new AppelDeFonction((string) ctx->NOMVAR()->getText(), l);
    }

    antlrcpp::Any visitMmexp(PLDCOMPParser::MmexpContext *ctx) override {
        Variable * var = (Variable *) visit(ctx->lvalue());
        return (Expression *) new ExprUnaire((Expression *) var, (Symbole) MMEXP);
    }

    antlrcpp::Any visitAffectation(PLDCOMPParser::AffectationContext *ctx) override {
        return (Expression *) new Affectation((Variable *) visit(ctx->lvalue()), (Expression *) visit(ctx->exp()));
    }

    antlrcpp::Any visitOperateurBinaire(PLDCOMPParser::OperateurBinaireContext *ctx) override {
        return (Expression *) new ExprBin ((Expression *) visit(ctx->exp(0)), (Expression *) visit(ctx->exp(1)), (Symbole) visit(ctx->op()));
    }

    antlrcpp::Any visitAppelPutchar(PLDCOMPParser::AppelPutcharContext *ctx) override {
        list<Expression> * l = new list<Expression>();
        l->push_back((Expression) Caractere((char) ctx->CHAR()->getText()[0]));
        return (Expression *) new AppelDeFonction("putchar", l);
    }

    antlrcpp::Any visitExppp(PLDCOMPParser::ExpppContext *ctx) override {
        Variable * var = (Variable *) visit(ctx->lvalue());
        return (Expression *) new ExprUnaire((Expression *) var, (Symbole) EXPPP);
    }

    antlrcpp::Any visitExpmm(PLDCOMPParser::ExpmmContext *ctx) override {
        Variable * var = (Variable *) visit(ctx->lvalue());
        return (Expression *) new ExprUnaire((Expression *) var, (Symbole) EXPMM);
    }

    antlrcpp::Any visitVariable(PLDCOMPParser::VariableContext *ctx) override {
        return (Variable *) new VariableSimple((string) ctx->NOMVAR()->getText());
    }

    antlrcpp::Any visitTableau(PLDCOMPParser::TableauContext *ctx) override {
        return (Variable *) new Tableau((string) ctx->NOMVAR()->getText(), (Expression *) visit(ctx->exp()));
    }

    antlrcpp::Any visitIfStatement(PLDCOMPParser::IfStatementContext *ctx) override {
        return (Instruction *) visit(ctx->if_statement());
    }

    antlrcpp::Any visitWhileStatement(PLDCOMPParser::WhileStatementContext *ctx) override {
        return (Instruction *) visit(ctx->while_statement());
    }

    antlrcpp::Any visitConstanteNb(PLDCOMPParser::ConstanteNbContext *ctx) override {
        return (Expression *) new Nombre((int) stoi(ctx->NOMBRE()->getText()));
    }

    antlrcpp::Any visitConstanteCar(PLDCOMPParser::ConstanteCarContext *ctx) override {
        return (Expression *) new Caractere((char) ctx->CHAR()->getText()[0]);
    }

    antlrcpp::Any visitType_variable(PLDCOMPParser::Type_variableContext *ctx) override {
        string type = ctx->getText();
        if (type=="char")
        return (Type) CHAR;
        else if (type=="int32_t")
        return (Type) INT32;
        else if (type=="int64_t")
        return (Type) INT64;
        else
        return false; // TODO: cas d'erreur
    }

    antlrcpp::Any visitType_function(PLDCOMPParser::Type_functionContext *ctx) override {
        string type = ctx->getText();

        if (type=="char")
        return (Type) CHAR;
        else if (type=="int32_t")
        return (Type) INT32;
        else if (type=="int64_t")
        return (Type) INT64;
        else if (type=="void")
        return (Type) VOID;
        else
        return false;
    }

    antlrcpp::Any visitIf(PLDCOMPParser::IfContext *ctx) override {
        return (Instruction *) new If((Expression *) visit(ctx->exp()), (Instruction *) visit(ctx->instruction()));
    }

    antlrcpp::Any visitIfElse(PLDCOMPParser::IfElseContext *ctx) override {
        return (Instruction *) new IfElse((Expression *) visit(ctx->exp()), (Instruction *) visit(ctx->instruction(0)), (Instruction *) visit(ctx->instruction(1)));
    }

    antlrcpp::Any visitWhile(PLDCOMPParser::WhileContext *ctx) override {
        return (Instruction *) new While((Expression *) visit(ctx->exp()), (Instruction *) visit(ctx->instruction()));
    }

    antlrcpp::Any visitTableauNombre(PLDCOMPParser::TableauNombreContext *ctx) override {
        list<Nombre> * l = new list<Nombre>();

        for(int i=0;/*TODO: condition d'arret ?*/;i++) {
            l->push_back((Nombre) Nombre((int) stoi(ctx->NOMBRE(i)->getText())));
        }
        return (list<Nombre> *) l;
    }

    antlrcpp::Any visitTableauCaractere(PLDCOMPParser::TableauCaractereContext *ctx) override {
        list<Caractere> * l = new list<Caractere>();

        for(int i=0;/*TODO: condition d'arret ?*/;i++) {
            l->push_back((Caractere) Caractere((char) ctx->CHAR(i)->getText()[0]));
        }
        return (list<Caractere> *) l;

    }

    antlrcpp::Any visitDeclarationConstante(PLDCOMPParser::DeclarationConstanteContext *ctx) override {
        Type type = visit(ctx->type_variable());
        if (type==CHAR) {
            return (Declaration) Declaration(type, new VariableSimple((string) ctx->NOMVAR()->getText(), (Caractere) Caractere((char) visit(ctx->constante()))));
        }
        else if (type==INT32 || type==INT64) {
            return (Declaration) Declaration(type, new VariableSimple((string) ctx->NOMVAR()->getText(), (Nombre) Nombre((int) visit(ctx->constante()))));
        }
        else {
            return NULL; //TODO : réfléchir à ça : cas d'erreur
        }
    }

    antlrcpp::Any visitDeclaration(PLDCOMPParser::DeclarationContext *ctx) override {
        return (Declaration) Declaration((Type) visit(ctx->type_variable()), new VariableSimple((string) ctx->NOMVAR()->getText()));
    }

    antlrcpp::Any visitDeclarationTableau(PLDCOMPParser::DeclarationTableauContext *ctx) override {
        return (Declaration) DeclarationTableau((Type) visit(ctx->type_variable()), new Tableau((string) ctx->NOMVAR()->getText()), (int) stoi(ctx->NOMBRE()->getText()));
    }

    antlrcpp::Any visitDeclarationTableauConstante(PLDCOMPParser::DeclarationTableauConstanteContext *ctx) override {
        Type type = (Type) visit(ctx->type_variable());
        if (type==CHAR) {
            return (Declaration) DeclarationTableau(type, new Tableau((string) ctx->NOMVAR()->getText(), (list<Caractere>*) visit(ctx->val())), (int) stoi(ctx->NOMBRE()->getText()));
        }
        else if (type==INT32 || type==INT64) {
            return (Declaration) DeclarationTableau(type, new Tableau((string) ctx->NOMVAR()->getText(), (list<Nombre>*) visit(ctx->val())), (int) stoi(ctx->NOMBRE()->getText()));
        }
        else {
            return NULL; //TODO : réfléchir à ça : cas d'erreur
        }
    }

    antlrcpp::Any visitVoid(PLDCOMPParser::VoidContext *ctx) override {
        list<Parametre> * param = new list<Parametre>();
        return (list<Parametre>* ) param;
    }

    antlrcpp::Any visitParametres(PLDCOMPParser::ParametresContext *ctx) override {
        list<Parametre> * l = new list<Parametre>();
        auto liste = ctx->type_variable();
        int cpt = 0;

        for(auto i=liste.begin();i!=liste.end();i++) {
            l->push_back((Parametre) Parametre((Type) visit(*i), (string) ctx->NOMVAR(cpt)->getText()));
            cpt++;
        }
        return (list<Parametre> *) l;
    }

    antlrcpp::Any visitDeclarationFonctionParams(PLDCOMPParser::DeclarationFonctionParamsContext *ctx) override {
        return (Fonction) Fonction((Type) visit(ctx->type_function()), (string) ctx->NOMVAR()->getText(), (list<Parametre> *) visit(ctx->param()), (list<Declaration> *) visit(ctx->declaration_variables()), (Bloc *) visit(ctx->bloc()));
    }

    antlrcpp::Any visitDeclarationFonction(PLDCOMPParser::DeclarationFonctionContext *ctx) override {
        list<Parametre> * param = new list<Parametre>();
        return (Fonction) Fonction((Type) visit(ctx->type_function()), (string) ctx->NOMVAR()->getText(), (list<Parametre> *) param, (list<Declaration> *) visit(ctx->declaration_variables()), (Bloc *) visit(ctx->bloc()));
    }

    antlrcpp::Any visitDeclarationVariables(PLDCOMPParser::DeclarationVariablesContext *ctx) override {
    list<Declaration> * l = new list<Declaration>();
        auto liste = ctx->declaration_type();

        for(auto i=liste.begin();i!=liste.end();i++) {
            l->push_back((Declaration) visit(*i));
        }

        return (list<Declaration> *) l;
    }

    antlrcpp::Any visitBloc(PLDCOMPParser::BlocContext *ctx) override {
        list<Instruction> * l = new list<Instruction>();
        auto liste = ctx->instruction();

        for(auto i=liste.begin();i!=liste.end();i++) {
            Instruction * instruction = (Instruction *) visit(*i);
            l->push_back((Instruction) *instruction);
        }
        return (Bloc *) new Bloc(l);
    }

    antlrcpp::Any visitBlocInstruction(PLDCOMPParser::BlocInstructionContext *ctx) override {
        return (Instruction *) visit(ctx->bloc());
    }

    antlrcpp::Any visitBreakInstruction(PLDCOMPParser::BreakInstructionContext *ctx) override {
        return (Instruction *) new Break();
    }

    antlrcpp::Any visitStructureInstruction(PLDCOMPParser::StructureInstructionContext *ctx) override {
        return (Instruction *) visit(ctx->structure());
    }

    antlrcpp::Any visitReturnInstruction(PLDCOMPParser::ReturnInstructionContext *ctx) override {
        return (Instruction *) new Return((Expression *) visit(ctx->exp()));
    }

    antlrcpp::Any visitExpInstruction(PLDCOMPParser::ExpInstructionContext *ctx) override {
        Expression * expression = (Expression *) visit(ctx->exp());
        return (Instruction *) expression;
    }

    antlrcpp::Any visitProgramme(PLDCOMPParser::ProgrammeContext *ctx) override {
        list<Fonction> * l = new list<Fonction>();
        auto liste = ctx->fonction();

        for(auto i=liste.begin();i!=liste.end();i++) {
            l->push_back((Fonction) visit(*i));
        }
        return (Programme *) new Programme((list<Declaration> *) visit(ctx->declaration_variables()), (list<Fonction> *) l);
    }


};
