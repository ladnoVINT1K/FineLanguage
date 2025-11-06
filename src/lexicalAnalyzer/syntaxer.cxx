#include "syntaxer.h"
#include <iostream>

Syntaxer::Syntaxer(Lexer& lexer) : lexer_(lexer) {
	curr_ = lexer.get_lexem();
}
void Syntaxer::NewToken() {
	curr_ = lexer_.get_lexem();
}

bool Syntaxer::match(const string& value) {
	return (value.empty() or curr_.second == value);
}

bool Syntaxer::matchType(Types type) {
	return (curr_.first == type);
}

void Syntaxer::expect(const string& value) {
	if (!value.empty() and curr_.second != value) {
		throw value;
	}
	NewToken();
}

void Syntaxer::expectType(Types type) {
	if (curr_.first != type) {
		throw type;
	}
	NewToken();
}

bool Syntaxer::syntax() {
	Prog();
	std::cout << "successful";
	return true;
}

void Syntaxer::Prog() {
	if (curr_.first != Types::END) {
		Declarations();
	}
}

void Syntaxer::Declarations() {
	while (!matchType(Types::END)) {
		Declaration();
		expect(";");
	}
}
 
void Syntaxer::Declaration() {
	if (match("def")) {
		Func();
	} else {
		Var();
	}
}

void Syntaxer::Var() {
	Type();
	expectType(Types::Identificator);
	Init();
}

void Syntaxer::Type() {
	if (match("massive")) {
		NewToken();
		expect("<");
		Type();
		expect(">");
	} else if (match("char") or match("int")
		or match("float") or match("let")) {
		NewToken();
	} else {
		throw curr_.first;
	}
}

void Syntaxer::Init() {
	if (match(";")) return;
	expect("=");
	if (match("{")) {
		list();
	} else {
		Expr();
	}
}

void Syntaxer::Func() {
	expect("def");
	TypeF();
	expectType(Types::Identificator);
	expect("(");
	Params();
	expect(")");
	expect("{");
	FuncR();
	ReturnState();
	expect(";");
	expect("}");
}

void Syntaxer::TypeF() {
	if (match("void")) {
		NewToken();
	} else {
		Type();
	}
}

void Syntaxer::Params() {
	if (match("void")) {
		NewToken();
	} else {
		Param();
	}
}

void Syntaxer::Param() {
	Var();
	while (match(",")) {
		NewToken();
		Var();
	}
}

void Syntaxer::FuncR() {
	if (!match("return")) {
		State();
		FuncR();
	}
}

void Syntaxer::State() {
	if (match("if")) {
		IfState();
	} else if (match("for")) {
		ForState();
	} else if (match("while")) {
		WhileState();
	} else if (match("input")) {
		cin();
	} else if (match("return")) {
		ReturnState();
	} else if (match("output")) {
		cout();
	} else if (match("char") or match("int")
		or match("float") or match("let") or match("massive")) {
		Var();
	} else {
		Expr();
	}
	expect(";");
}

void Syntaxer::IfState() {
	expect("if");
	expect("(");
	Expr();
	expect(")");
	expect("{");
	State();
	expect("}");
	IfStateTail();
}

void Syntaxer::IfStateTail() {
	if (match(";")) {
		NewToken();
	} else {
		expect("else");
		expect("{");
		State();
		expect("}");
	}
}

void Syntaxer::ForState() {
	expect("for");
	expect("(");
	ForStateTail();
}

void Syntaxer::ForStateTail() {
	if (match(";")) {
		NewToken();
	} else {
		A();
		expect(";");
	}
	Expr();
	expect(";");
	Expr();
	expect(")");
	expect("{");
	State();
	expect("}");
}

void Syntaxer::A() {
	if (match("char") or match("int")
		or match("float") or match("let") 
		or match("massive")) {
		Var();
	} else {
		Expr();
	}
}

void Syntaxer::WhileState() {
	expect("while");
	expect("(");
	Expr();
	expect(")");
	expect("{");
	State();
	expect("}");
}

void Syntaxer::ReturnState() {
	expect("return");
	if (!match(";")) {
		Expr();
	}
}

void Syntaxer::Expr() {
	E1();
	while (match(",")) {
		NewToken();
		E1();
	}
}

void Syntaxer::E1() {
	E2();
	while (match("+=") or match("-=") or match("*=") 
		or match("/=") or match("%=")) {
		NewToken();
		E2();
	}
}

void Syntaxer::E2() {
	E3();
	while (match("or") or match("|")) {
		NewToken();
		E3();
	}
}

void Syntaxer::E3() {
	E4();
	while (match("and") or match("&")) {
		NewToken();
		E4();
	}
}

void Syntaxer::E4() {
	E5();
	while (match("<") or match(">") or match("==") 
		or match("!=") or match("<=") or match(">=")) {
		NewToken();
		E5();
	}
}

void Syntaxer::E5() {
	E6();
	while (match("+") or match("-")) {
		NewToken();
		E6();
	}
}

void Syntaxer::E6() {
	E7();
	while (match("*") or match("/") or match("%")) {
		NewToken();
		E7();
	}
}

void Syntaxer::E7() {
	if (match("!") or match("not") or match("-")) {
		NewToken();
		E7();
	} else {
		E8();
	}
}

void Syntaxer::E8() {
	if (match("(")) {
		NewToken();
		Expr();
		expect(")");
	} else if (matchType(Types::Identificator)) {
		NewToken();
		CI();
	} else {
		expectType(Types::Literal);
	}
}

void Syntaxer::CI() {
	if (match("(")) {
		Call();
	} else {
		Iden();
	}
}

void Syntaxer::Call() {
	expect("(");
	CallTail();
}

void Syntaxer::CallTail() {
	if (!match(")")) {
		Args();
	}
	expect(")");
}

void Syntaxer::Args() {
	Expr();
	while (match(",")) {
		NewToken();
		Expr();
	}
}

void Syntaxer::Iden() {
	while (match("[")) {
		NewToken();
		Expr();
		expect("]");
	}
}

void Syntaxer::list() {
	expect("{");
	while (!match("}")) {
		Expr();
	}
	expect("}");
}

void Syntaxer::cin() {
	expect("input");
	expect("(");
	expectType(Types::Identificator);
	Iden();
	expect(")");
}

void Syntaxer::cout() {
	expect("output");
	expect("(");
	Expr();
	expect(")");
}