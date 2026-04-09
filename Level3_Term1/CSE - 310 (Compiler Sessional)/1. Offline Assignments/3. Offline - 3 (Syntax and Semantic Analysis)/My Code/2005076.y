%{

#include "2005076_parserFunctions.cpp"

int yyparse(void);
int yylex(void);
extern FILE* yyin;

void syntax_error(string error){
	log_out<<"Error at line : " << line_number <<" : "<< "syntax error\n";
}

// void yyerror(char *s)
// {
// 	//write your code
// }

void yyerror(const string& s) {
	syntaxError_line = line_number;
	log_out<< "Error at line no " << syntaxError_line << " : syntax error\n";
}
string stored_fReturnType;



%}

//%error-verbose

%union{
    SymbolInfo* symbolInfo;
}

/* %destructor{
	free_symbol($$);
	//cout<<$$->getName() + " deleted in y file\n";
}<symbolInfo> */


%token <symbolInfo>IF ELSE FOR WHILE RETURN INT FLOAT VOID CONST_INT CONST_FLOAT
%token <symbolInfo> ADDOP RELOP ASSIGNOP INCOP MULOP LOGICOP DECOP NOT
%token <symbolInfo> LPAREN RPAREN LCURL RCURL COMMA SEMICOLON LTHIRD RTHIRD ID PRINTLN

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%type<symbolInfo> start unit program var_declaration argument_list logic_expression statement statements func_declaration func_definition type_specifier compound_statement declaration_list
%type<symbolInfo> left_curl expression term rel_expression unary_expression simple_expression variable factor arguments parameter_list expression_statement




%%

start : program
	{
		//write your code in this block in all the similar blocks below
		log_CFG_rule("start", "program");
		$$ = new SymbolInfo("start", "start");
		$$->add_branch($1);
		$$->grammar_rule = "start : program";
		$$->print_inParseTree(parseTree, 0);
		free_symbol($$);
	}
	;

program : program unit {
		log_CFG_rule("program", "program unit");
		$$ = new SymbolInfo("program", "program");
		$$->add_branch($1);
		$$->add_branch($2);
		$$->grammar_rule = "program : program unit";
	}
	| unit{
		log_CFG_rule("program", "unit");
		$$ = new SymbolInfo("program", "program");
		$$->add_branch($1);
		$$->grammar_rule = "program : unit";
	}
	;


	
unit : var_declaration{
		log_CFG_rule("unit", "var_declaration");
		$$ = new SymbolInfo("unit", "unit");
		$$->add_branch($1);
		$$->grammar_rule = "unit : var_declaration";
	}
    | func_declaration{
		log_CFG_rule("unit", "func_declaration");
		$$ = new SymbolInfo("unit", "unit");
		$$->add_branch($1);
		$$->grammar_rule = "unit : func_declaration";
	}
    | func_definition{
		log_CFG_rule("unit", "func_definition");
		$$ = new SymbolInfo("unit", "unit");
		$$->add_branch($1);
		$$->grammar_rule = "unit : func_definition";
	}
	| error{
		$$ = new SymbolInfo("unit", "unit");
		cout<<"Error occured\n";
	}
    ;


     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{
		log_CFG_rule("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = new SymbolInfo("func_declaration", "func_declaration");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5); $$->add_branch($6);
		$$->grammar_rule = "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
		function_token($2->getName(),"DECLARATION", $1->getType(), $4->parameter_list);
		stored_fParam.clear();


	}
	| type_specifier ID LPAREN RPAREN SEMICOLON{
		log_CFG_rule("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
		$$ = new SymbolInfo("func_declaration", "func_declaration");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5);
		$$->grammar_rule = "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
		function_token($2->getName(),"DECLARATION", $1->getType(), {});
		stored_fParam.clear();
	}
	;


		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
	function_token($2->getName(),"DEFINITION", $1->getType(), $4->parameter_list);
	stored_fReturnType = $1->type_specifier;
}
	compound_statement{
		log_CFG_rule("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new SymbolInfo("func_definition", "func_definition");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5); $$->add_branch($7);
		$$->grammar_rule = "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";


	}
	| type_specifier ID LPAREN RPAREN {
		function_token($2->getName(),"DEFINITION", $1->getType(), {});
		stored_fReturnType = $1->type_specifier;
	}
	compound_statement{
		log_CFG_rule("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new SymbolInfo("func_definition", "func_definition");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($6);
		$$->grammar_rule = "func_definition : type_specifier ID LPAREN RPAREN compound_statement";
	}
 	;				



parameter_list  : parameter_list COMMA type_specifier ID{
		log_CFG_rule("parameter_list", "parameter_list COMMA type_specifier ID");
		$$ = new SymbolInfo("null", "parameter_list");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "parameter_list : parameter_list COMMA type_specifier ID";

		$$->set_ParamList($1->parameter_list);
		Parameter extraParam($4->getName(), $3->type_specifier);
		$$->add_param(extraParam);
		stored_fParam = $$->parameter_list;

		if( $3->type_specifier == "VOID"){
			print_error("Variable or field \'"+$4->getName()+"\' declared void", "none", line_number);
		}

		
	}
	| parameter_list COMMA type_specifier{
		log_CFG_rule("parameter_list", "parameter_list COMMA type_specifier ID");
		$$ = new SymbolInfo("parameter_list", "parameter_list");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "parameter_list : parameter_list COMMA type_specifier";

		$$->set_ParamList($1->parameter_list);
		Parameter extraParam("null", $3->type_specifier);
		$$->add_param(extraParam);
		stored_fParam = $$->parameter_list;

		if( $3->type_specifier == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
 	| type_specifier ID{
		log_CFG_rule("parameter_list", "type_specifier ID");
		$$ = new SymbolInfo("parameter_list", "parameter_list");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "parameter_list : type_specifier ID";

		Parameter extraParam($2->getName(), $1->type_specifier);
		$$->add_param(extraParam);
		stored_fParam = $$->parameter_list;

		if( $1->type_specifier == "VOID"){
			print_error("Variable or field \'"+$2->getName()+"\' declared void", "none", line_number);
		}
	}
	| type_specifier{
		log_CFG_rule("parameter_list", "type_specifier");
		$$ = new SymbolInfo("parameter_list", "parameter_list");
		$$->add_branch($1);
		$$->grammar_rule = "parameter_list : type_specifier";

		Parameter extraParam("none", $1->type_specifier);
		$$->add_param(extraParam);
		stored_fParam = $$->parameter_list;

		if( $1->type_specifier == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
 	;

 		
compound_statement : left_curl statements RCURL{
		log_CFG_rule("compound_statement", "LCURL statements RCURL");
		$$ = new SymbolInfo("compound_statement", "compound_statement");
		
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "compound_statement : LCURL statements RCURL";

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();

	}
 	| left_curl RCURL{
		log_CFG_rule("compound_statement", "LCURL RCURL");
		$$ = new SymbolInfo("compound_statement", "compound_statement");
		
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "compound_statement : LCURL RCURL";

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();
	}
 	;


var_declaration : type_specifier declaration_list SEMICOLON{
		log_CFG_rule("var_declaration", "type_specifier declaration_list SEMICOLON");
		$$ = new SymbolInfo("var_declaration", "var_declaration");

		$$->type_specifier = $1->type_specifier;
		symbol_tokens($1->type_specifier, $2->parameter_list);

		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "var_declaration : type_specifier declaration_list SEMICOLON";
	}
 	;

 		 
type_specifier	: INT{
		log_CFG_rule("type_specifier", "INT");
		$$ = new SymbolInfo("null", "type_specifier");
		$$->type_specifier = "INT";
		$$->add_branch($1);
		$$->grammar_rule = "type_specifier : INT";
	}
 	| FLOAT{
		log_CFG_rule("type_specifier", "FLOAT");
		$$ = new SymbolInfo("null", "type_specifier");
		$$->type_specifier = "FLOAT";
		$$->add_branch($1);
		$$->grammar_rule = "type_specifier : FLOAT";
	}
 	| VOID{
		log_CFG_rule("type_specifier", "VOID");
		$$ = new SymbolInfo("null", "type_specifier");
		$$->type_specifier = "VOID";
		$$->add_branch($1);
		$$->grammar_rule = "type_specifier : VOID";
	}
 	;
 		


declaration_list : declaration_list COMMA ID{
		log_CFG_rule("declaration_list", "declaration_list COMMA ID");
		$$ = new SymbolInfo("null", "declaration_list");
		$$->add_branch($1); $$->add_branch($2);
		$$->add_branch($3);
		$$->grammar_rule = "declaration_list : declaration_list COMMA ID";

		$$->set_ParamList($1->parameter_list);
		Parameter extraParam($3->getName(), "none");
		$$->add_param(extraParam);
	}
 	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD{
		log_CFG_rule("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		$$ = new SymbolInfo("null", "declaration_list");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->add_branch($5); $$->add_branch($6);
		$$->grammar_rule = "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";

		$$->set_ParamList($1->parameter_list);
		Parameter extraParam($3->getName(), "ID");
		extraParam.array_type = true;
		$$->add_param(extraParam);
	}
 	| ID{
		log_CFG_rule("declaration_list", "ID");
		$$ = new SymbolInfo("declaration_list", "declaration_list");
		$$->add_branch($1);
		$$->grammar_rule = "declaration_list : ID";

		Parameter extraParam($1->getName(), "ID");
		$$->add_param(extraParam);
	}
 	| ID LTHIRD CONST_INT RTHIRD{
		log_CFG_rule("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
		$$ = new SymbolInfo("declaration_list", "declaration_list");
		$$->add_branch($1); $$->add_branch($2);
		$$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "declaration_list : ID LSQUARE CONST_INT RSQUARE";

		Parameter extraParam($1->getName(), "ID");
		extraParam.array_type = true;
		$$->add_param(extraParam);
	}
 	;
 		  

statements : statement{
		log_CFG_rule("statements", "statement");
		$$ = new SymbolInfo("null", "statements");
		$$->add_branch($1);
		$$->grammar_rule = "statements : statement";
	}
	| statements statement{
		log_CFG_rule("statements", "statements statement");
		$$ = new SymbolInfo("null", "statements");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "statements : statements statement";
	}
	;
	   

statement : var_declaration{
		log_CFG_rule("statement", "var_declaration");
		$$ = new SymbolInfo($1->getName(), "statement");
		$$->type_specifier = $1->type_specifier;
		$$->add_branch($1);
		$$->grammar_rule = "statement : var_declaration";
	}
	| expression_statement{
		log_CFG_rule("statement", "expression_statement");
		$$ = new SymbolInfo($1->getName(), "statement");
		$$->add_branch($1);
		$$->grammar_rule = "statement : expression_statement";
		$$->type_specifier = $1->type_specifier;
	}
	| compound_statement{
		log_CFG_rule("statement", "compound_statement");
		$$ = new SymbolInfo($1->getName(), "statement");
		$$->add_branch($1);
		$$->grammar_rule = "statement : compound_statement";
		$$->type_specifier = $1->type_specifier;
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement{
		log_CFG_rule("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5); $$->add_branch($6); $$->add_branch($7); 
		$$->grammar_rule = "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement";
	}
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE{
		log_CFG_rule("statement", "IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); 
		$$->add_branch($4); $$->add_branch($5);
		$$->grammar_rule = "statement : IF LPAREN expression RPAREN statement";
	}
	| IF LPAREN expression RPAREN statement ELSE statement{
		log_CFG_rule("statement", "IF LPAREN expression RPAREN statement ELSE statement");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->add_branch($5); $$->add_branch($6); $$->add_branch($7);
		$$->grammar_rule = "statement : IF LPAREN expression RPAREN statement ELSE statement";
	}
	| WHILE LPAREN expression RPAREN statement{
		log_CFG_rule("statement", "WHILE LPAREN expression RPAREN statement");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->add_branch($4); $$->add_branch($5);
		$$->grammar_rule = "statement : WHILE LPAREN expression RPAREN statement";
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON{
		log_CFG_rule("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->add_branch($4); $$->add_branch($5);
		$$->grammar_rule = "statement : PRINTLN LPAREN ID RPAREN SEMICOLON";

		if(symbol_table->lookUp($3->getName()) == nullptr){
			print_error("Undeclared variable", $3->getName(), line_number);
		}
	}
	| RETURN expression SEMICOLON{
		log_CFG_rule("statement", "RETURN expression SEMICOLON");
		$$ = new SymbolInfo("statement", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "statement : RETURN expression SEMICOLON";

		if($2->type_specifier == "FLOAT" && stored_fReturnType == "INT"){
			print_error("Warning: possible loss of data in assignment of FLOAT to INT", "none", line_number);
		}
		else if(stored_fReturnType == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
	;
	  

expression_statement : SEMICOLON{
		log_CFG_rule("expression_statement", "SEMICOLON");
		$$ = new SymbolInfo("expression_statement", "expression_statement");
		$$->add_branch($1);
		$$->grammar_rule = "expression_statement : SEMICOLON";
	}	
	| expression SEMICOLON{
		log_CFG_rule("expression_statement", "expression SEMICOLON");
		$$ = new SymbolInfo("expression_statement", "expression_statement");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "expression_statement : expression SEMICOLON";
		$$->type_specifier = $1->type_specifier;
	}
	;

	  
variable : ID {
		log_CFG_rule("variable", "ID");
		$$ = new SymbolInfo($1->getName(), "VARIABLE");
		$$->type_specifier = $1->type_specifier;
		$$->add_branch($1);
		$$->grammar_rule = "variable : ID";

		SymbolInfo* temp = symbol_table ->lookUp($1->getName());
		if(temp != nullptr){
			$$->isArray = temp->isArray;
			$$->type_specifier = temp->type_specifier;
		}
		else{
			print_error("Undeclared variable", $1->getName(), line_number);
		}
	}		
	| ID LTHIRD expression RTHIRD {
		log_CFG_rule("variable", "ID LSQUARE expression RSQUARE");
		$$ = new SymbolInfo($1->getName(), "VARIABLE");
		$$->type_specifier = $1->type_specifier;
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "variable : ID LSQUARE expression RSQUARE";

		SymbolInfo* temp = symbol_table->lookUp($1->getName());
		if(temp == nullptr){
			print_error("Undeclared variable", $1->getName(), line_number);
		}
		else if(temp->isArray == false){
			print_error("\'" + $1->getName() + "\' is not an array", "none", line_number);
		}
		else if($3->type_specifier != "INT"){
			print_error("Array subscript is not an integer", $1->getName(), line_number);
		}
		else{
			$$->isArray = temp->isArray;
			$$->type_specifier = temp->type_specifier;
		}
		$$->isArray = true;

	}
	;
	 

 expression : logic_expression{
		log_CFG_rule("expression", "logic_expression");
		$$ = new SymbolInfo("expression", "expression");

		$$->add_branch($1);
		$$->grammar_rule = "expression : logic_expression";

 	}
	| variable ASSIGNOP logic_expression{
		log_CFG_rule("expression", "variable ASSIGNOP logic_expression");
		$$ = new SymbolInfo("expression", "expression");

		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "expression : variable ASSIGNOP logic_expression";

		if($1->type_specifier == "INT"){
			if($3->type_specifier == "FLOAT"){
				print_error("Warning: possible loss of data in assignment of FLOAT to INT", "none", line_number);
			}
			$$->type_specifier = "INT";
		}
		else if($1->type_specifier == "VOID" || $3->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($1->type_specifier == "error_type" || $3->type_specifier == "error_type"){
			$$->type_specifier = "error_type";
		}
		else {
			$$->type_specifier = "FLOAT";
		}
	}	
	;


logic_expression : rel_expression {
		log_CFG_rule("logic_expression", "rel_expression");
		$$ = new SymbolInfo($1->getName(), "logic_expression");
		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;

		$$->add_branch($1);
		$$->grammar_rule = "logic_expression : rel_expression";
	}
	| rel_expression LOGICOP rel_expression{
		log_CFG_rule("logic_expression", "rel_expression LOGICOP rel_expression");
		$$ = new SymbolInfo($1->getName(), "logic_expression");

		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "logic_expression : rel_expression LOGICOP rel_expression";

		if($1->type_specifier == "FLOAT" || $3->type_specifier == "FLOAT"){
			print_error("Warning: Operands of bitwise operation should be integers", "none", line_number);
			$$->type_specifier = "INT";
		}
		else if($1->type_specifier == "VOID" || $3->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($1->type_specifier == "error_type" || $3->type_specifier == "error_type"){
			$$->type_specifier = "error_type";
		}
		else {
			$$->type_specifier = "INT";
		}
	}
	;


rel_expression	: simple_expression{
		log_CFG_rule("rel_expression", "simple_expression");
		$$ = new SymbolInfo($1->getName(), "rel_expression");

		$$->add_branch($1);
		$$->grammar_rule = "rel_expression : simple_expression";
		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;
	}
	| simple_expression RELOP simple_expression	{
		log_CFG_rule("rel_expression", "simple_expression RELOP simple_expression");
		$$ = new SymbolInfo("", "rel_expression");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "rel_expression : simple_expression RELOP simple_expression";

		if($1->type_specifier == "VOID" || $3->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
	}
	;


simple_expression : term {
		log_CFG_rule("simple_expression", "term");
		$$ = new SymbolInfo($1->getName(), "simple_expression");
		$$->add_branch($1);
		$$->grammar_rule = "simple_expression : term";

		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;
	}
	| simple_expression ADDOP term {
		log_CFG_rule("simple_expression", "simple_expression ADDOP term");
		$$ = new SymbolInfo($1->getName(), "simple_expression");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "simple_expression : simple_expression ADDOP term";

		if($1->type_specifier == "VOID" || $3->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
		}
		$$->type_specifier = casting($1->type_specifier, $3->type_specifier);
	}
	;
	 
					
term :	unary_expression{
		log_CFG_rule("term", "unary_expression");
		$$ = new SymbolInfo($1->getName(), "term");
		$$->add_branch($1);
		$$->grammar_rule = "term : unary_expression";

		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;
	}
    |  term MULOP unary_expression{
		log_CFG_rule("term", "term MULOP unary_expression");
		$$ = new SymbolInfo($1->getName(), "term");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "term : term MULOP unary_expression";

		if($1->type_specifier == "VOID" || $3->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($1->type_specifier == "error_type" || $3->type_specifier == "error_type"){
			$$->type_specifier = "error_type";
		}
		else if($2->getName() == "%"){
			if($1->type_specifier == "FLOAT" || $3->type_specifier == "FLOAT"){
				print_error("Operands of modulus must be integers", "none", line_number);
				$$->type_specifier = "error_type";
			}
			else if($3->getName() == "0"){
				print_error("Warning: division by zero", "none", line_number);
				$$->type_specifier = "error_type";
			}
			else{
				$$->type_specifier = "INT";
			}
		}
		else if($2->getName() == "/"){
			if($3->getName() == "0"){
				print_error("Warning: division by zero", "none", line_number);
				$$->type_specifier = "error_type";
			}
			else{
				$$->type_specifier = casting($1->type_specifier, $3->type_specifier);
			}
		}
		else if($2->getName() == "*"){
			$$->type_specifier = casting($1->type_specifier, $3->type_specifier);
		}

	}
    ;


unary_expression : ADDOP unary_expression{
		log_CFG_rule("unary_expression", "ADDOP unary_expression");
		$$ = new SymbolInfo("", "unary_expression");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "unary_expression : ADDOP unary_expression";

		if($2->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else{
			$$->type_specifier = $2->type_specifier;
		}
	}
	| NOT unary_expression{
		log_CFG_rule("unary_expression", "NOT unary_expression");
		$$ = new SymbolInfo("", "unary_expression");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "unary_expression : NOT unary_expression";

		$$->type_specifier = "INT";
		if($2->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($2->type_specifier == "FLOAT"){
			print_error("Operands of bitwise operation should be integers", "none", line_number);
		}

	}
	| factor{
		log_CFG_rule("unary_expression", "factor");
		$$ = new SymbolInfo($1->getName(), "unary_expression");

		$$->add_branch($1);
		$$->grammar_rule = "unary_expression : factor";
		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;
	}
	;
	

factor	: variable{
		log_CFG_rule("factor", "variable");
		$$ = new SymbolInfo($1->getName(), "factor");
		$$->add_branch($1);
		$$->grammar_rule = "factor : variable";

		$$->type_specifier = $1->type_specifier;
		$$->isArray = $1->isArray;
	}
	| ID LPAREN argument_list RPAREN{
		log_CFG_rule("factor", "ID LPAREN argument_list RPAREN");
		$$ = new SymbolInfo("", "factor");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "factor : ID LPAREN argument_list RPAREN";

		SymbolInfo* temp = symbol_table->lookUp($1->getName());
		if(temp == nullptr){
			print_error("Undeclared function", $1->getName(), line_number);
		}
		else if(temp->func_decType == "null"){
			string str = "\'" + $1->getName()+ "\' is not a function";
			print_error(str, "none", line_number);
		}
		else if(temp->parameter_list.size() > $3->parameter_list.size()){
			print_error("Too few arguments to function", $1->getName(), line_number);
		}
		else if(temp->parameter_list.size() < $3->parameter_list.size()){
			print_error("Too many arguments to function", $1->getName(), line_number);
		}
		else{
			for(int k=0; k<temp->parameter_list.size(); k++){
				if(temp->parameter_list[k].dataType != $3->parameter_list[k].dataType || temp->parameter_list[k].array_type != $3->parameter_list[k].array_type){
					string print = to_string(k + 1);
					print += " of \'" + $1->getName() + "\'";
					print_error("Type mismatch for argument", print, line_number);
				}
			}
			$$->type_specifier = temp->type_specifier;
		}
	}
	| LPAREN expression RPAREN{
		log_CFG_rule("factor", "LPAREN expression RPAREN");
		$$ = new SymbolInfo($2->getName(), "factor");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "factor : LPAREN expression RPAREN";

		$$->type_specifier = $2->type_specifier;
	}
	| CONST_INT{
		log_CFG_rule("factor", "CONST_INT");
		$$ = new SymbolInfo($1->getName(), "factor");
		$$->add_branch($1);
		$$->grammar_rule = "factor : CONST_INT";
		$$->type_specifier = "INT";
	} 
	| CONST_FLOAT{
		log_CFG_rule("factor", "CONST_FLOAT");
		$$ = new SymbolInfo($1->getName(), "factor");
		$$->add_branch($1);
		$$->grammar_rule = "factor : CONST_FLOAT";
		$$->type_specifier = "FLOAT";
	}
	| variable INCOP{
		log_CFG_rule("factor", "variable INCOP");
		$$ = new SymbolInfo("", "factor");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "factor : variable INCOP";

		if($1->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($1->type_specifier == "error_type"){
			$$->type_specifier = "error_type";
		}
		else{
			$$->type_specifier = $1->type_specifier;
		}
	}
	| variable DECOP{
		log_CFG_rule("factor", "variable DECOP");
		$$ = new SymbolInfo("", "factor");
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "factor : variable DECOP";

		if($1->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			$$->type_specifier = "error_type";
		}
		else if($1->type_specifier == "error_type"){
			$$->type_specifier = "error_type";
		}
		else{
			$$->type_specifier = $1->type_specifier;
		}
	}
	;


	
argument_list : arguments{
		log_CFG_rule("argument_list", "arguments");
		$$ = new SymbolInfo("", "argument_list");
		$$->add_branch($1);
		$$->grammar_rule = "argument_list : arguments";

		$$->set_ParamList($1->parameter_list);
	}
	| {
		log_CFG_rule("argument_list", "");
		$$ = new SymbolInfo("null", "argument_list");
		$$->grammar_rule = "argument_list : ";
		$$->startLine = line_number;
		$$->endLine = line_number;
	}
	;
	
arguments : arguments COMMA logic_expression{
		log_CFG_rule("arguments", "arguments COMMA logic_expression");
		$$ = new SymbolInfo("null", "arguments");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "arguments : arguments COMMA logic_expression";

		$$->set_ParamList($1->parameter_list);
		Parameter extraParam($3->getName(), $3->type_specifier);
		extraParam.array_type = $3->isArray;
		$$->add_param(extraParam);
	}
	| logic_expression{
		log_CFG_rule("arguments", "logic_expression");
		$$ = new SymbolInfo("null", "arguments");
		$$->add_branch($1);
		$$->grammar_rule = "arguments : logic_expression";

		Parameter extraParam($1->getName(), $1->type_specifier);
		extraParam.array_type = $1->isArray;
		$$->add_param(extraParam);
	}
	;

left_curl : LCURL{
		$$ = $1;
		symbol_table -> enterScope();

		for(Parameter param : stored_fParam){
			if(param.param_name == "") continue;
			SymbolInfo* extra = new SymbolInfo(param.param_name, "ID");
			extra->isArray = param.array_type;
			extra->type_specifier = param.dataType;

			bool temp = symbol_table->insert(extra);
			if(temp == false){
				print_error("Redefinition of parameter", extra->getName(), line_number);
				free_symbol(extra);
				break;
			}
		}
		stored_fParam.clear();
	}
 

 

%%
int main(int argc,char *argv[])
{
	FILE *fp;

	if (argc < 2) {
		cout << "Enter Input File\n";
		exit(1);
	}

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}


	yyin=fp;
	yyparse();
	
	end_parse();

	fclose(yyin);
	
	return 0;
}

