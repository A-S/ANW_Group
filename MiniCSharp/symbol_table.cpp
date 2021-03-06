#include "ast.h"

Sym::Sym(string name, int kind, int type)
{

	this->name = name;
	this->kind = kind;
	this->type = type;
	this->argTypes = NULL;

}

Sym::Sym(string n, int kind, int type, 
		 Args *ps, int returnType, Function *meth)
{
	this->name = n;
	this->kind = kind;
	this->type = type;
	this->method = meth;
	this->returnType = returnType;
	this->argTypes = new vector<int>;

	for(int i = 0; i < ps->args->size(); i++)
		this->argTypes->push_back(ps->args->at(i)->type->type);
}


Scope::Scope()
{
	this->father = NULL;
	this->hashTab = new HashTab;
	this->children = new vector<Scope *>;
}

void
Scope::AddChild()
{
	Scope *child = new Scope();
	this->children->push_back(child);
	child->father = this;
}

//************************************************

SymTab::SymTab(Errors *errors)
{
	this->errors = errors;
	types[0] = "null";
	types[1] = "int";
	types[2] = "double";
	types[3] = "BOOL";
	types[4] = "void";
	kinds[0] = "c";//class
	kinds[1] = "f";//function
	kinds[2] = "v";//variable
}

void
SymTab::AddNewScope()
{
	this->current->AddChild();
	this->current = this->current->children->at(this->current->children->size() - 1);
}

void
SymTab::OutScope()
{
	this->current = this->current->father;
}

Sym *
SymTab::Lookup(std::string name)
{
	Scope *scope = this->current;
	Sym  *sym = NULL;
	while(scope != NULL)
	{
		sym = scope->hashTab->GetMember(name);
		if(sym != NULL)
			return sym;
		scope = scope->father;
	}

	return NULL;
}

bool
SymTab::IsDeclared(Ident *id )
{
	if(id->symbol!= NULL)
	{
		string key =kinds[id->symbol->kind]+id->name;
		Sym *sym = this->Lookup(key);
		if(sym != NULL)
		{
			id->symbol = sym;
			return true;
		}
		}
		else
		{
			this->errors->AddError("Undeclared Identifier '" + id->name + "'", id->line, id->column);
			return false;
		}

}
bool
SymTab::IsDeclared(Ident *id , int kind  ,int type )
{

		string key =kinds[kind]+id->name;
		Sym *sym = this->Lookup(key);
		if(sym != NULL)
		{
			id->symbol = sym;
			return true;
		}
	
		else
		{
			this->errors->AddError("Undeclared Identifier '" + id->name + "'", id->line, id->column);
			return false;
		}

}
/*
	SymTab::IsDeclared(Ident *id, ExprList *el)
	this function is for the case of invoking 
	a function like func(3+2, 6 * x), there are expresions list (el)
*/
bool
SymTab::IsDeclared(Ident *id, ExprList *el)
{
	string key=id->name;
	for(int i = 0 ; i < el->exprList->size(); i++)
	{
		int t = el->exprList->at(i)->type;
		key += "@" + types[t];
	}
	Sym *sym = this->Lookup(key);
	if(sym != NULL)
	{
		id->symbol = sym;
		return true;
	}
	else
	{
		this->errors->AddError("Undeclared Identifier '" + id->name + "'", id->line, id->column);
		return false;
	}
}

bool
SymTab::IsDeclared(Ident *id, Deffered *def )
{
	string key=id->name;
	Sym *sym = this->Lookup(key);
	if(sym != NULL)
	{
		id->symbol = sym;
		return true;
	}
	else
	{
		def->AddIdent(id);
		return false;
	}
}

bool
SymTab::AddSym(Ident *id, int kind, int type)
{
	string key =kinds[kind]+id->name;
	if(this->Lookup(key) == NULL)
	{
		Sym *sym = new Sym(key, kind, type);
		this->current->hashTab->AddKey(key, sym);
		id->symbol = sym;
		return true;
	}
	else
	{
		this->errors->AddError("Redefinition of Identifier '" + id->name + "'", id->line, id->column);
		return false;
	}
}

bool
SymTab::AddSym(Ident *id, int kind, int type, Args *ps, int returnType, Function *meth)
{
	string key = id->name;
	for(int i = 0; i < ps->args->size(); i++)
	{
		int t = ps->args->at(i)->type->type;
		
		key += "@" + types[t];
	}

	if(this->Lookup(key) == NULL)
	{
		Sym *sym = new Sym(id->name, kind, type, ps, returnType, meth);
		this->current->hashTab->AddKey(key, sym);
		id->symbol = sym;
		return true;
	}
	else
	{
		this->errors->AddError("Redefinition of Identifier '" + id->name + "'", id->line, id->column);
		return false;
	}
}

void 
SymTab::AddVars(Variables *v, Type *et)
{
	for(int i = 0; i < v->variables->size(); i++)
		this->AddSym(v->variables->at(i)->name, 3, et->type);
}


///****************  Deffered  **********************************8
Deffered::Deffered()
{
	this->ids = new vector<Ident *>;
}


void
Deffered::AddIdent(Ident *id)
{
	this->ids->push_back(id);
}

void
Deffered::CheckAll(SymTab *symtab)
{
	for(int i = 0; i < this->ids->size(); i++)
	{
		Sym *sym = symtab->current->hashTab->GetMember(this->ids->at(i)->name);
		if(sym != 0)
			this->ids->at(i)->symbol = sym;
		else
			symtab->errors->AddError("Undeclared Identifier '" + this->ids->at(i)->name + "'", this->ids->at(i)->line, this->ids->at(i)->column);
	}

}