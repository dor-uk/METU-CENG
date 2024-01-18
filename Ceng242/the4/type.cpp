#include "type.h"

namespace sym 
{
	__nullary_op_t::~__nullary_op_t() 
    { 
        //delete this;
    }

	bool __nullary_op_t::is_nullary() const 
    { 
        return true;
    }

	bool __nullary_op_t::is_con() const 
    { 
        return false;
    }
	bool __nullary_op_t::is_var() const 
    { 
        return false;
    }

}

namespace sym 
{
	__unary_op_t::~__unary_op_t() 
	{ 
	    delete operand;
	}

	bool __unary_op_t::is_unary() const 
    { 
        return true;
    }

	bool __unary_op_t::is_neg() const 
    { 
        return false;
    }
	bool __unary_op_t::is_exp() const 
    { 
        return false;
    }

}

namespace sym 
{
	__binary_op_t::~__binary_op_t() 
	{ 
	    //delete lhs_;
	    //delete rhs_;
	}

	bool __binary_op_t::is_binary() const 
    { 
        return true;
    }

	bool __binary_op_t::is_add() const 
    { 
        return false;
    }
	bool __binary_op_t::is_mul() const 
    { 
        return false;
    }

}