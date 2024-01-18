#include <iostream>
#include "expr.h"
#include "unary.h"
#include "binary.h"

int main() {
	sym::Const c1 = 2.0;
    sym::Var x = "x", y = "y";
    
    sym::ExpOp op(x.eval());
    sym::Expr e = x * op * y;
    sym::Expr sex = x * op;
    sym::Expr de = e.diff(y);
    sym::Expr dex = op.diff(y);
    sym::Expr hay = sex.diff(y);
    //sym::MulOp a(&c1, &op);
    
    std::cout << "expression: " << e << std::endl;
    std::cout << "differentiation1: " << dex << std::endl;
    std::cout << "differentiation2: " << hay << std::endl;
    std::cout << "differentiation3: " << de << std::endl;
}
