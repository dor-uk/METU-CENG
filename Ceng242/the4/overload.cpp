#include "nullary.h"
#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include "expr.h" //I added !!
#include <iostream>  // I added !!

namespace sym {
	
	__expr_t& operator-(const __expr_t &op) 
	{ 
		return *new NegOp(&op);

	} 
	__expr_t& exp(const __expr_t &op) 
	{ 
	    return *new ExpOp(&op);
	}

	__expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs) 
	{ 
	    return *new AddOp(&lhs, &rhs);
	}
	__expr_t& operator+(double lhs, const __expr_t &rhs) 
	{ 
	    return *new AddOp(new Const(lhs), &rhs);
	}
	__expr_t& operator+(const __expr_t &lhs, double rhs) 
	{ 
	    return *new AddOp(&lhs, new Const(rhs));
	}

	__expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs) 
	{ 
	    return *new MulOp(&lhs, &rhs);
	}
	__expr_t& operator*(double lhs, const __expr_t &rhs) 
	{ 
	    return *new MulOp(new Const(lhs), &rhs);
	}
	__expr_t& operator*(const __expr_t &lhs, double rhs) 
	{ 
	    return *new MulOp(&lhs, new Const(rhs));
	}
	
	
}