%{
#include <sstream>
#include "2005076_parserFunctions.cpp"

int yyparse(void);
int yylex(void);
extern FILE* yyin;

ofstream assem_code;
int stack_offset;

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
string current_function;

SymbolInfo* function_params = new SymbolInfo();



%}

//%error-verbose

%union{
    SymbolInfo* symbolInfo;
}

%destructor{
	free_symbol($$);
	//cout<<$$->getName() + " deleted in y file\n";
}<symbolInfo> 


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
		//$$->print_inParseTree(parseTree, 0);
		//free_symbol($$);

		traverse($$);

		cout<<"after traverse\n";
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
		$$ = new SymbolInfo("func_declaration1", "func_declaration");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5); $$->add_branch($6);
		$$->grammar_rule = "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
		function_token($2->getName(),"DECLARATION", $1->getType(), $4->parameter_list);
		stored_fParam.clear();

	}
	| type_specifier ID LPAREN RPAREN SEMICOLON{
		log_CFG_rule("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
		$$ = new SymbolInfo("func_declaration2", "func_declaration");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5);
		$$->grammar_rule = "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
		function_token($2->getName(),"DECLARATION", $1->getType(), {});
		stored_fParam.clear();
	}
	;


		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
		stored_fReturnType = $1->type_specifier;
		//function_token($2->getName(),"DEFINITION", $1->getType(), $4->parameter_list);
		$2->type_specifier = $1->type_specifier;
		$2->parameter_list = function_params->parameter_list;
		$2->is_function = true;
		current_function = $2->getName();
		symbol_table->insert($2);

		stored_fParam.clear();
	}
	compound_statement{
		log_CFG_rule("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new SymbolInfo($2->getName(), "func_definition");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4); 
		$$->add_branch($5); $$->add_branch($7);
		$$->grammar_rule = "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";


	}
	| type_specifier ID LPAREN RPAREN {
		stored_fReturnType = $1->type_specifier;
		//function_token($2->getName(),"DEFINITION", $1->getType(), {});
		$2->type_specifier = $1->type_specifier;
		$2->parameter_list = function_params->parameter_list;
		$2->is_function = true;
		current_function = $2->getName();
		symbol_table->insert($2);

		stored_fParam.clear();
	}
	compound_statement{
		log_CFG_rule("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new SymbolInfo($2->getName(), "func_definition");
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

		$$->parameter_list = $1->parameter_list;
		Parameter extraParam($4->getName(), $3->type_specifier);
		$$->add_param(extraParam);
		$4->type_specifier = $3->type_specifier;
		function_params->parameter_list = $$->parameter_list;

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

		$$->parameter_list = $1->parameter_list;
		Parameter extraParam("ID", $3->type_specifier);
		$$->add_param(extraParam);
		function_params->parameter_list = $$->parameter_list;

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
		function_params->parameter_list = $$->parameter_list;

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
		function_params->parameter_list = $$->parameter_list;

		stored_fParam = $$->parameter_list;
		if( $1->type_specifier == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
 	;

 		
compound_statement : left_curl statements RCURL{
		log_CFG_rule("compound_statement", "LCURL statements RCURL");
		$$ = new SymbolInfo("comp_statement1", "compound_statement");
		
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "compound_statement : LCURL statements RCURL";
		$$->offset = symbol_table->currentScope->stack_offset;

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();

	}
 	| left_curl RCURL{
		log_CFG_rule("compound_statement", "LCURL RCURL");
		$$ = new SymbolInfo("compound_statement", "compound_statement");
		
		$$->add_branch($1); $$->add_branch($2);
		$$->grammar_rule = "compound_statement : LCURL RCURL";
		$$->offset = symbol_table->currentScope->stack_offset;

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();
	}
 	;


var_declaration : type_specifier declaration_list SEMICOLON{
		log_CFG_rule("var_declaration", "type_specifier declaration_list SEMICOLON");
		$$ = new SymbolInfo("var_dec", "var_declaration");

		$$->type_specifier = $1->type_specifier;
		//symbol_tokens($1->type_specifier, $2->parameter_list);

		$$->add_branch($1); 
		$$->add_branch($2); 
		$$->add_branch($3);
		$$->grammar_rule = "var_declaration : type_specifier declaration_list SEMICOLON";

		if(symbol_table->currentScope->get_scopeID()=="1"){
			$$->is_global = true;
		}
		else $$->is_global = false;
		for(SymbolInfo* si : $2->dec_List){
			si->type_specifier = $1->type_specifier;
			symbol_table->insert(si);
			if(symbol_table->currentScope->get_scopeID() == "1"){
				global_variables.push_back(si);
				si->offset = 0;
				si->is_global = true;
			}
			else{
				stack_offset = symbol_table->currentScope->stack_offset;
				si->is_global = false;
				if(si->isArray) symbol_table->currentScope->stack_offset = stack_offset - 2*si->array_size;
				else symbol_table->currentScope->stack_offset = stack_offset - 2;
				si->offset = symbol_table->currentScope->stack_offset;
			}
		}
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

		$$->dec_List = $1->dec_List;
		$$->dec_List.push_back($3);
	}
 	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD{
		log_CFG_rule("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		$$ = new SymbolInfo("null", "declaration_list");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->add_branch($5); $$->add_branch($6);
		$$->grammar_rule = "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";

		$$->dec_List = $1->dec_List;
		$3->isArray = true;
		string str = $5->getName();
		istringstream istr(str);
		int k;
		istr>>k;
		$3->array_size = k;
		$$->dec_List.push_back($3);

	}
 	| ID{
		log_CFG_rule("declaration_list", "ID");
		$$ = new SymbolInfo("dec_list3", "declaration_list");
		$$->add_branch($1);
		$$->grammar_rule = "declaration_list : ID";

		$$->dec_List.push_back($1);
	}
 	| ID LTHIRD CONST_INT RTHIRD{
		log_CFG_rule("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
		$$ = new SymbolInfo("declaration_list", "declaration_list");
		$$->add_branch($1); $$->add_branch($2);
		$$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "declaration_list : ID LSQUARE CONST_INT RSQUARE";

		$1->isArray = true;
		string str = $3->getName();

		istringstream istr(str);
		int k;
		istr >> k;
		$1->array_size = k;
		$$->dec_List.push_back($1);
	}
 	;
 		  

statements : statement{
		log_CFG_rule("statements", "statement");
		$$ = new SymbolInfo("statements1", "statements");
		$$->add_branch($1);
		$$->grammar_rule = "statements : statement";
	}
	| statements statement{
		log_CFG_rule("statements", "statements statement");
		$$ = new SymbolInfo("statements2", "statements");
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
		$$ = new SymbolInfo("statement_println", "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->add_branch($4); $$->add_branch($5);
		$$->grammar_rule = "statement : PRINTLN LPAREN ID RPAREN SEMICOLON";

		auto temp = symbol_table->lookUp($3->getName());
		$$->offset = temp->offset;
		$$->is_global = temp->is_global;
	}
	| RETURN expression SEMICOLON{
		log_CFG_rule("statement", "RETURN expression SEMICOLON");
		$$ = new SymbolInfo($1->getName(), "statement");
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "statement : RETURN expression SEMICOLON";

		$1->setName(current_function);
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
		$$ = new SymbolInfo("expr_stmnt1", "expression_statement");
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
			$$->offset = temp->offset;
			$$->is_global = temp->is_global;
		}
		
	}		
	| ID LTHIRD expression RTHIRD {
		log_CFG_rule("variable", "ID LSQUARE expression RSQUARE");
		$$ = new SymbolInfo($1->getName(), "VARIABLE");
		$$->type_specifier = $1->type_specifier;
		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3); $$->add_branch($4);
		$$->grammar_rule = "variable : ID LSQUARE expression RSQUARE";

		SymbolInfo* temp = symbol_table->lookUp($1->getName());
		if(temp != nullptr){
			temp->isArray = true;
			$$->isArray = temp->isArray;
			$$->offset = temp->offset;
			$$->is_global = temp->is_global;
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
		$$ = new SymbolInfo("expression2", "expression");

		$$->add_branch($1); $$->add_branch($2); $$->add_branch($3);
		$$->grammar_rule = "expression : variable ASSIGNOP logic_expression";
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

		$$->type_specifier = "INT";
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
		$$->type_specifier = temp->type_specifier;

		//$1->parameter_list = $3->parameter_list;
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
		$$ = new SymbolInfo($1->getName(), "argument_list");
		$$->add_branch($1);
		$$->grammar_rule = "argument_list : arguments";

		$$->parameter_list = $1->parameter_list;
		$$->offset = $1->offset;
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

		$$->parameter_list = $1->parameter_list;
		Parameter extraParam($3->getName(), $3->type_specifier);
		extraParam.array_type = $3->isArray;
		$$->add_param(extraParam);

		$$->offset = $1->offset+2;
	}
	| logic_expression{
		log_CFG_rule("arguments", "logic_expression");
		$$ = new SymbolInfo("null", "arguments");
		$$->add_branch($1);
		$$->grammar_rule = "arguments : logic_expression";

		Parameter extraParam($1->getName(), $1->type_specifier);
		extraParam.array_type = $1->isArray;
		$$->add_param(extraParam);

		$$->offset = 2;
	}
	;

left_curl : LCURL{
		$$ = $1;
		symbol_table -> enterScope();
		int st_off = 2;
		for(int k=function_params->parameter_list.size()-1; k>=0; k-- ){
			Parameter param = function_params->parameter_list[k];
			if(param.param_name == "") continue;
			SymbolInfo* extra = new SymbolInfo(param.param_name, "ID");
			forDelete.push_back(extra);
			extra->isArray = param.array_type;
			extra->type_specifier = param.dataType;

			st_off += 2;
			extra->offset = st_off;
			bool temp = symbol_table->insert(extra);
			if(temp == false){
				print_error("Redefinition of parameter", extra->getName(), line_number);
				free_symbol(extra);
				break;
			}
		}
		stored_fParam.clear();
		function_params->parameter_list.clear();
		symbol_table->currentScope->stack_offset = 0;
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
	assem_code.open("2005076_code.asm");

	symbol_table = new SymbolTable(symbolTable_size);
	//cout<<symbol_table->currentScope->get_scopeID()<<"\n";


	yyin=fp;
	yyparse();
	
	end_parse();
	code_optimizer();

	fclose(yyin);
	
	return 0;
}

