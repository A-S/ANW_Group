
#ifndef	AST_H
#define AST_H

#include <iostream>
using std::cout;
using std::endl;

#include <sstream>


#include <vector>
using std::vector;

#include <string>
using std::string;

class Node;
class File;
class Root;
class Class;
class ClassInher;
class Members;
class Member;
class Global;
class Constructor;
class Function;
class Arg;
class Args;
class Variables;
class Variable;
class AccessModif;
class Type;
class NoArrayType;
class ArrayType;
class Ident;
class Expr;
class Incr;
class Decr;
class Not;
class Minus;
class Plus;
class Paren;
class Assign;
class Invoke;
class InvokeArr;
class NewObject;
class NewArr;
class Equal;
class NotEq;
class Smaller;
class SmallerEq;
class Larger;
class LargerEq;
class Add;
class Sub;
class Mult;
class Div;
class Mod;
class And;
class Or;
class Is;
class Cast;
class Integer;
class Real;
class True;
class False;
class This;
class Null;
class ArrayIndex;
class ArrayIndex_1;
class ArrayIndex_2;
class ArrayIndex_3;
class QualNArray;
class QualNArray_ID_Index;
class QualNArray_Exp_Index;
class QualName;
class QualName_ID;
class QualName_Exp;
class ExprList;
class Stat;
class Stats;
class If;
class IfElse;
class While;
class For;
class ExprStat;
class VariablesStat;
class Semi;
class Block;
class Return;
class Variables_e;

class Sym;
class Scope;
class SymTab;
class Deffered;

class Errors;

class Visitor;

//*******      Node		*************
class Node
{
public:
	int		line;
	int		column;
	Node	*father;

	Node(int, int);
	virtual void accept(Visitor *);
};
class File :public Node
{
public :
	File(int, int);
	virtual void accept(Visitor *);
};
//*******     Root		*************
class Root : public File
{
public:
	vector<Class *>	*classes;

	Root(int, int);
	void AddClass(Class *);
	virtual void accept(Visitor *);
};

//*******       Class		*********
class Class : public Node		// Class without Inheritance
{
public:
	Ident	*name;
	Members	*members;
	vector<Ident *>	*Parents;

	void AddParent(Ident * );
	Class(Ident *, Members *, int, int);
	virtual void accept(Visitor *);
};

class ClassInher : public Class	// Class with Inheritance
{
public:
	Ident	*parent;

	ClassInher(Ident *, Ident *, Members *, int, int);
	virtual void accept(Visitor *);
};

//*******     Members		*********
class Members : public Node
{
public:
	vector<Member *>	*members;

	Members(int, int);
	void AddMember(Member *);
	virtual void accept(Visitor *);
};

class Member : public Node
{
public:
	Member(int, int);
	virtual void accept(Visitor *);
};

//*******     Global		*********
class Global : public Member
{
public:
	AccessModif	*accessModif;
	Type		*type;
	Variables	*variables;

	Global(AccessModif	*, Type *, Variables *, int , int);
	virtual void accept(Visitor *);
};

//*******   Constructor		*********
class Constructor : public Member
{
public:
	AccessModif	*accessModif;
	Ident		*name;
	Args		*args;
	Stats		*stats;

	Constructor(AccessModif *, Ident *, Args *, Stats *, int, int);
	virtual void accept(Visitor *);
};

//*******     Function		*********
class Function : public Member
{
public:
	AccessModif	*accessModif;
	Type		*type;
	Ident		*name;
	Args		*args;
	Stats		*stats;

	Function(AccessModif *, Type *, Ident *, Args *, Stats *, int, int);
	Function(AccessModif *, Ident *, Args *, Stats *, int, int);
	virtual void accept(Visitor *);
};

//*******       Args		*********
class Args : public Node
{
public:
	vector<Arg *>	 *args;

	Args(int, int);
	Args(Arg *, int, int);
	void AddArg(Arg *);
	virtual void accept(Visitor *);
};

class Arg : public Node
{
public:
	Type	*type;
	Ident	*name;

	Arg(Type *, Ident *, int, int);
	virtual void accept(Visitor *);
};

//*******     Variables		*********
class Variables	: public Node
{
public:
	vector<Variable *>	*variables;

	Variables(int, int);
	Variables(Variable *, int, int);
	void AddVariable(Variable *);
	virtual void accept(Visitor *);
};

class Variable : public Node
{
public:
	Ident	*name;
	Expr	*expr;

	Variable(Ident *, int, int);
	Variable(Ident *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******    AccessModif	*********
class AccessModif : public Node
{
public:
	// 1: no AccessModif , 2: private , 3: static , 4: private static
	int acctype;

	AccessModif(int, int, int);
	virtual void accept(Visitor *);
};

//*******       Type		*********
class Type : public Node
{
public:
	//-1: no type, 0 = Null, 1 = int , 2 = double , 3 = boolean, 4: void, 5:object, 6:ident
	int type;
	Ident *name;

	Type(int, int);
	virtual void accept(Visitor *);
};

//*******    NoArrayType	*********
class NoArrayType : public Type
{
public:

	NoArrayType(int, int, int);
	NoArrayType(Ident *, int, int);
	virtual void accept(Visitor *);
};

//*******     ArrayType		*********
class ArrayType : public Type
{
public:
	// 1: a single Array []
	// 2: Matrix of bilateral [,]
	// 3: Matrix trilogy [,,]
	int arrayType;

	ArrayType(int, int, int, int);
	ArrayType(int, Ident *, int, int);
	virtual void accept(Visitor *);
};

//*******       Ident		*********
class Ident : public Node
{
public:
	string	name;
	Sym *symbol;
	Ident(string, int, int);
	virtual void accept(Visitor *);
};

//***********************************************************************
//					Expression
//***********************************************************************

class Expr : public Node
{
public:
	//-1: no type, 0 = Null, 1 = int , 2 = double , 3 = boolean, 4: void
	int type;
	Expr(int, int);
	virtual void accept(Visitor *);
};

//*******       Incr		*********
class Incr  : public Expr
{
public:
	QualNArray	*qual;
	bool	isPrev;

	Incr(QualNArray *, bool, int, int);
	virtual void accept(Visitor *);
};

//*******       Decr		*********
class Decr  : public Expr
{
public:
	QualNArray	*qual;
	bool	isPrev;

	Decr(QualNArray *, bool, int, int);
	virtual void accept(Visitor *);
};

//*******        Not		*********
class Not  : public Expr
{
public:
	Expr	*expr;

	Not(Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******      Minus		*********
class Minus  : public Expr
{
public:
	Expr	*expr;

	Minus(Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******       Plus		*********
class Plus : public Expr
{
public:
	Expr	*expr;

	Plus(Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******      Paren		*********
class Paren : public Expr
{
public:
	Expr	*expr;
	Ident	*name;

	Paren(Expr *, int, int);
	Paren(Ident *, int, int);
	virtual void accept(Visitor *);
};

//*******     QualNArrExp		*********
class QualNArrExp : public Expr
{
public:
	QualNArray	*qualNArray;

	QualNArrExp(QualNArray *, int, int);
	virtual void accept(Visitor *);
};

//*******      Assign		*********
class Assign : public Expr
{
public:
	QualNArray	*qualNArray;
	Expr		*expr;

	Assign(QualNArray *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******       Invoke		*********
class Invoke : public Expr
{
public:
	QualName	*qualName;
	ExprList	*exprList;

	Invoke(QualName *, ExprList *, int, int);
	virtual void accept(Visitor *);
};

//*******     InvokeArr		*********
class InvokeArr : public Expr
{
public:
	QualName	*qualName;
	ExprList	*exprList;
	ArrayIndex	*arrayIndex;

	InvokeArr(QualName *, ExprList *, ArrayIndex *, int, int);
	virtual void accept(Visitor *);
};

//*******     NewObject		*********
class NewObject : public Expr
{
public:
	Ident		*ident;
	ExprList	*exprList;

	NewObject(Ident *, ExprList *, int, int);
	virtual void accept(Visitor *);
};

//*******      NewArr		*********
class NewArr : public Expr
{
public:
	Ident		*ident;
	ArrayIndex	*arrayIndex;

	NewArr(Ident *, ArrayIndex *, int, int);
	virtual void accept(Visitor *);
};

//*******      Equal		*********
class Equal  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Equal(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******      NotEq		*********
class NotEq  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	NotEq(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******     Smaller		*********
class Smaller  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Smaller(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******     SmallerEq		*********
class SmallerEq  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	SmallerEq(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******     Larger		*********
class Larger  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Larger(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******     LargerEq		*********
class LargerEq  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	LargerEq(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        Add		*********
class Add  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Add(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        Sub		*********
class Sub  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Sub(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        Mult		*********
class Mult  : public Expr
{
	public:
	Expr	*left;
	Expr	*right;

	Mult(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        Div		*********
class Div  : public Expr
{
	public:
	Expr	*left;
	Expr	*right;

	Div(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        Mod		*********
class Mod  : public Expr
{
	public:
	Expr	*left;
	Expr	*right;

	Mod(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******        And		*********
class And  : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	And(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******         Or		*********
class Or : public Expr
{
public:
	Expr	*left;
	Expr	*right;

	Or(Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******         Is		*********
class Is : public Expr
{
public:
	Expr	*expr;
	Type	*typ;

	Is(Expr *, Type *, int, int);
	virtual void accept(Visitor *);
};

//*******        Cast		*********
class Cast : public Expr
{
public:
	Type	*typ;
	Expr	*expr;

	Cast(Type *, Expr *, int, int);
	Cast(Ident *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******      Integer		*********
class Integer : public Expr
{
public:
	int value;

	Integer(int, int, int);
	virtual void accept(Visitor *);
};

//*******       Real		*********
class Real : public Expr
{
public:
	double value;

	Real(double, int, int);
	virtual void accept(Visitor *);
};

//*******       True		*********
class True : public Expr
{
public:
	True(int, int);
	virtual void accept(Visitor *);
};

//*******      False		*********
class False : public Expr
{
public:
	False(int, int);
	virtual void accept(Visitor *);
};

//*******       This		*********
class This : public Expr
{
public:
	This(int, int);
	virtual void accept(Visitor *);
};

//*******       Null		*********
class Null : public Expr
{
public:
	Null(int, int);
	virtual void accept(Visitor *);
};

//*******     ArrayIndex	*********
class ArrayIndex : public Node
{
public:
	ArrayIndex( int, int);
	virtual void accept(Visitor *);
};

class ArrayIndex_1 :public ArrayIndex
{
public:
	Expr	*expr1;

	ArrayIndex_1(Expr *, int, int);
	virtual void accept(Visitor *);
};

class ArrayIndex_2 : public ArrayIndex
{
public:
	Expr	*expr1;
	Expr	*expr2;

	ArrayIndex_2(Expr *,Expr *, int, int);
	virtual void accept(Visitor *);
};

class ArrayIndex_3 : public ArrayIndex
{
public:
	Expr	*expr1;
	Expr	*expr2;
	Expr	*expr3;

	ArrayIndex_3(Expr *, Expr *, Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******   QualNameOrArr	*********
class QualNArray : public Expr
{
public:
	Ident   *ident;

	QualNArray(int, int);
	virtual void accept(Visitor *);
};

class QualNArray_ID_Index : public QualNArray
{
public:
	ArrayIndex	*index;

	QualNArray_ID_Index(Ident *, ArrayIndex *, int, int);
	virtual void accept(Visitor *);
};

class QualNArray_Exp_Index : public QualNArray
{
public:
	Expr  *expr;
	ArrayIndex *index;

	QualNArray_Exp_Index(Ident*, Expr*,ArrayIndex*,int, int);
	virtual void accept(Visitor *);
};

//*******   QualifiedName	*********

class QualName : public QualNArray
{
public:
	Ident   *ident ;

	QualName( int, int);
	virtual void accept(Visitor *);
};

class QualName_ID : public QualName
{
public:
	QualName_ID(Ident *, int, int);
	virtual void accept(Visitor *);
};

class QualName_Exp : public QualName
{
public:
	Expr	*expr;

	QualName_Exp(Ident *,Expr * , int, int);
	virtual void accept(Visitor *);
};

//*******     ExprList		*********
class ExprList : public Node
{
public:
	vector<Expr *>	*exprList;

	ExprList(int, int);
	ExprList(Expr *, int, int);
	void AddExpr(Expr *);
	virtual void accept(Visitor *);
};

//***********************************************************************
//					Statement
//***********************************************************************

class Stat : public Node
{
public:
	Stat(int, int);
	virtual void accept(Visitor *);
};

class Stats : public Node
{
public:
	vector<Stat	*>	*stats;

	Stats(int, int);
	Stats(Stat *, int, int);
	void AddStat(Stat *);
	virtual void accept(Visitor *);
};

//*******         If		*********
class If : public Stat
{
public:
	Expr	*expr;
	Stat	*stat;
	
	If(Expr *, Stat *, int, int);
	virtual void accept(Visitor *);
};

//*******      If Else		*********
class IfElse : public If
{
public:
	Stat		*elseStat;

	IfElse(Expr *, Stat *, Stat *, int , int );
	virtual void accept(Visitor *);
};

//*******      While		*********
class While : public Stat
{
public:
	Expr	*expr;
	Stat	*stat;
	
	While(Expr *, Stat *, int, int);
	virtual void accept(Visitor *);
};

//*******        For		*********
class For : public Stat
{
public:
	Variables_e	*variables_e;
	Expr		*exprCond;
	Expr		*exprCount;
	Stat		*stat;
	
	For(Variables_e *, Expr *, Expr *, Stat *, int , int );
	virtual void accept(Visitor *);
};

//*******      ExprStat		*********
class ExprStat : public Stat
{
public:
	Expr	*expr;
	ExprStat(Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******   VariablesStat	*********
class VariablesStat : public Stat
{
public:
	Type		*type;
	Variables	*variables;
	VariablesStat(Type *, Variables *, int, int);
	virtual void accept(Visitor *);
};

//*******     Semicolon		*********
class Semi : public Stat
{
public:
	Semi(int, int);
	virtual void accept(Visitor *);
};

//*******      Block		*********
class Block : public Stat
{
public:
	Stats *stats;

	Block(Stats *, int , int );
	virtual void accept(Visitor *);
};

//*******      Return		*********
class Return : public Stat
{
public:
	Expr	*expr;
	Return(Expr *, int, int);
	virtual void accept(Visitor *);
};

//*******     Variable_e	*********
class Variables_e : public Node
{
public:
	Type	*type;
	Variables	*variables;
	Variables_e(Type *, Variables *, int, int);
	virtual void accept(Visitor *);
};

#endif