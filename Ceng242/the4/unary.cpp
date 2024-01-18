#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const 
    { 
        return true;
    }

	__expr_t* NegOp::eval(const var_map_t& vars) const 
    { 
        if (operand->is_nullary()) 
        {
            const sym::Const* const_operand = dynamic_cast<const sym::Const*>(operand);
            
            if(const_operand)
            {
                double neg_value = -const_operand->get_value();
                //delete const_operand;
                return new sym::Const(neg_value);
            }
        } 
        
        else 
        {
            return new sym::NegOp(operand->eval(vars));
        }
    }

	__expr_t* NegOp::diff(const std::string& v) const 
    { 
        /*__expr_t* diff_op = operand->diff(v);
        if(const sym::Const* const_op = dynamic_cast<const sym::Const*>(diff_op))
        {
            if(const_op->get_value() == 0)
            {
                return new sym::Const(0);
            }
        }*/
        return NegOp(operand->diff(v)).eval();
    }

	std::ostream& NegOp::operator<< (std::ostream &out) const 
    { 
        out << "-";
        if (!(operand->is_nullary())) 
        {
            out << "(";
            operand->operator<<(out);
            out << ")";
        } 
        
        else 
        {
            operand->operator<<(out);
        }
        
        return out;
    }

	bool NegOp::operator==(const __expr_t& other_) const 
    { 
        if (const sym::NegOp* neg_op = dynamic_cast<const sym::NegOp*>(&other_)) 
        {
            if(neg_op)
            {
                return (*operand == *(neg_op->operand));
                //delete neg_op;
            }
        }
        return false;
    }
}

namespace sym 
{
	bool ExpOp::is_exp() const 
    { 
        return true;
    }

	__expr_t* ExpOp::eval(const var_map_t& vars) const 
    { 
        if (operand->is_nullary()) 
        {
            const sym::Const* const_operand = dynamic_cast<const sym::Const*>(operand);
            
            if(const_operand)
            {
                double expo_value = std::exp(const_operand->get_value());
            
                if(const_operand->get_value() == 0)
                {
                    return new sym::Const(1);
                }
                if(const_operand->get_value() == 1)
                {
                    return new sym::Const(std::exp(1));
                }
                
                return new sym::Const(expo_value);
            }
        } 
        
        else 
        {
            return new sym::ExpOp(operand->eval(vars));
        }
    }

	__expr_t* ExpOp::diff(const std::string& v) const 
	{ 
	    __expr_t* diff_operand = operand->diff(v);
	    const sym::Const* const_operand = dynamic_cast<const sym::Const*>(diff_operand);
	    
	    if(const_operand)
	    {
	        if(const_operand->get_value() == 0)
	        {
	            return new sym::Const(0.0);
	        }
	        
	        
	        
	    }

        // Create a new multiplication operation: diff_operand * ExpOp(operand)
        __expr_t* mul_expr = new MulOp(diff_operand, new ExpOp(operand));


        return mul_expr;
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const 
    { 
        
        out << "e^";
        if (!(operand->is_nullary())) 
        {
            out << "(";
            operand->operator<<(out);
            out << ")";
        } 
        
        else 
        {
            operand->operator<<(out);
        }
        return out;
    }

	bool ExpOp::operator==(const __expr_t& other_) const 
    { 
        if (const sym::ExpOp* exp_op = dynamic_cast<const sym::ExpOp*>(&other_)) 
        {
            if(exp_op)
            {
                return *operand == *(exp_op->operand);
            }
        }
        return false;
    }
}
