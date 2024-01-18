#include "binary.h"
#include "nullary.h"
#include <math.h>
#include "unary.h"  // I added

namespace sym 
{
	bool AddOp::is_add() const 
    { 
        return true;
    }

	__expr_t* AddOp::eval(const var_map_t& vars) const 
    { 
        
        if (rhs_->is_nullary() && lhs_->is_nullary()) 
        {
            const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
            const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
            
            double sum = const_lhs->get_value() + const_rhs->get_value();
            
            return new sym::Const(sum);
        } 
        
        else if (rhs_->is_nullary() && (rhs_->eval(vars) == 0)) 
        {
            return lhs_->eval(vars);
        } 
        
        else if (lhs_->is_nullary() && (lhs_->eval(vars) == 0)) 
        {
            return rhs_->eval(vars);
        } 
        
        else 
        {
            return new sym::AddOp(lhs_->eval(vars), rhs_->eval(vars));
        }
    }

	__expr_t* AddOp::diff(const std::string& v) const 
    { 
        __expr_t* diff_lhs = lhs_->diff(v);
        __expr_t* diff_rhs = rhs_->diff(v);
        
        return new sym::AddOp(diff_lhs, diff_rhs);
    }

	std::ostream& AddOp::operator<< (std::ostream &out) const 
    { 
        
        if(lhs_->is_nullary())
        {
            const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
            if(const_lhs != NULL && const_lhs->get_value() == 0)
            {
                rhs_->operator<<(out);
                
                return out;

            }

        }

        if(rhs_->is_nullary())
        {
            const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
            if(const_rhs != NULL && const_rhs->get_value() == 0)
            {
                lhs_->operator<<(out);
                        
                return out;

            }


        }
        //out << "(";
        if (!(lhs_->is_nullary())) 
        {
            out << "(";
            lhs_->operator<<(out);
            out << ")";
        } 
        else 
        {
            lhs_->operator<<(out);
        }
        
        out << " + ";
        
        if (!rhs_->is_nullary()) 
        {
            out << "(";
            rhs_->operator<<(out);
            out << ")";
            
        } 
        else 
        {
            rhs_->operator<<(out);
            
        }
        //out << ")";
        
        return out;
        
        
    }

	bool AddOp::operator==(const __expr_t& other_) const 
    { 
        if (const sym::AddOp* add_op = dynamic_cast<const sym::AddOp*>(&other_)) 
        {
                return (*lhs_ == *(add_op->lhs_)) && (*rhs_ == *(add_op->rhs_));
        }
        
        return false;
    }
}

namespace sym 
{
	bool MulOp::is_mul() const 
    { 
        return true;
    }

	__expr_t* MulOp::eval(const var_map_t& vars) const    //can be wrong, check again
    { 
        const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
        const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
        
        
        if (rhs_->is_nullary() && lhs_->is_nullary()) 
        {
            //const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
            //const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
            //const sym::NegOp* neg_op = dynamic_cast<const sym::NegOp*>(lhs_);
            //const sym::NegOp* neg_op = dynamic_cast<const sym::NegOp*>(rhs_);
            
            if(const_lhs != nullptr && const_rhs != nullptr)
            {
                /*if(const_lhs->get_value() == 0 && const_rhs->get_value() == 0)
                {
                    return new sym::Const(0.0);
                }*/
                
                double product = const_lhs->get_value() * const_rhs->get_value();
                
            
                return new sym::Const(product);
            }
        } 
        
        if (rhs_->is_nullary() && (const_rhs->get_value() == 1)) 
        {
            return lhs_->eval(vars);
        } 
        
        if (lhs_->is_nullary() && (const_lhs->get_value() == 1)) 
        {
            return rhs_->eval(vars);
        }
        
        else if (rhs_->is_nullary() && (rhs_->eval(vars) == 0)) 
        {
            return new sym::Const(0.0);
        } 
        
        else if (lhs_->is_nullary() && (lhs_->eval(vars) == 0)) 
        {
            return new sym::Const(0.0);
        } 
        
        /*else if (lhs_->eval(vars) == 0)
        {
            return new sym::Const(0.0);
        }*/
        
        
        else 
        {
            return new sym::MulOp(lhs_->eval(vars), rhs_->eval(vars));
        }
        
        
        
    }

	__expr_t* MulOp::diff(const std::string& v) const 
    { 
        
        __expr_t* diff_lhs = lhs_->diff(v);
        __expr_t* diff_rhs = rhs_->diff(v);

        // Check if differentiation of any operand is zero
        const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(diff_lhs);
        const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(diff_rhs);
    
        
        
        /*if((const_lhs != nullptr && const_lhs->get_value() == 0) && (const_rhs != nullptr && const_rhs->get_value() == 0))
        {
            
            __expr_t* zeroth = new Const(0);
            return zeroth;
             
        }*/
        
        if ((const_lhs != nullptr && const_lhs->get_value() == 0))  
        {
            // If differentiation of any operand is zero, return zero
            if((const_rhs != nullptr && const_rhs->get_value() == 1))
            {
                if(const sym::Const* yama = dynamic_cast<const sym::Const*>(lhs_))
                {
                    return new sym::Const(yama->get_value());
            
                }
                else
                {
                    return MulOp(lhs_, diff_rhs).eval();
                }
            }
            
            /*if((const_rhs != nullptr && const_rhs->get_value() == 0))
            {
                return MulOp(new Const(0), new Const(0)).eval();
            }*/
            return new sym::MulOp(lhs_, diff_rhs);
        }
        
        if ((const_rhs != nullptr && const_rhs->get_value() == 0))
        {
            if((const_lhs != nullptr && const_lhs->get_value() == 1))
            {
                if(const sym::Const* yama = dynamic_cast<const sym::Const*>(rhs_))
                {
                    return new sym::Const(yama->get_value());
            
                }
                /*else
                {
                    return MulOp(diff_lhs, rhs_).eval();
                }*/
                
            }
            return new sym::MulOp(diff_lhs, rhs_);
        }
        
        if((const_lhs != nullptr && const_lhs->get_value() == 1) && (const_rhs != nullptr && const_rhs->get_value() == 1))
        {
            
            __expr_t* add_expr = new AddOp(rhs_, lhs_);
            return add_expr;
             
        }
            
        
        if ((const_lhs != nullptr && const_lhs->get_value() == 1))  
        {
            
            __expr_t* mul_expr1 = new MulOp(lhs_, diff_rhs);
            __expr_t* add_expr = new AddOp(rhs_, mul_expr1);
            return add_expr;
            
        }
        
        if ((const_rhs != nullptr && const_rhs->get_value() == 1))
        {
            __expr_t* mul_expr2 = new MulOp(diff_lhs, rhs_);
            __expr_t* add_expr = new AddOp(mul_expr2, lhs_);
            //std::cout<<"sex";
            return add_expr;
        }
        
        
        __expr_t* mul_expr1 = new MulOp(lhs_, diff_rhs);
        //std::cout<<"sex";
        __expr_t* mul_expr2 = new MulOp(diff_lhs, rhs_);
    
        
        __expr_t* add_expr = new AddOp(mul_expr2, mul_expr1);
    
        return add_expr;
        //return AddOp(MulOp(diff_lhs,rhs_->eval()).eval(),MulOp(lhs_->eval(),diff_rhs).eval()).eval(); 
        
    }

	std::ostream& MulOp::operator<< (std::ostream &out) const 
    { 
        
        
        if(lhs_->is_nullary())
        {
            const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
            if(const_lhs != NULL && const_lhs->get_value() == 1)
            {
                rhs_->operator<<(out);
                return out;

            }

        }

        if(rhs_->is_nullary())
        {
            const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
            if(const_rhs != NULL && const_rhs->get_value() == 1)
            {
                lhs_->operator<<(out);
                        
                return out;

            }


        }
        
        
        
        if(lhs_->is_nullary())
        {
            const sym::Const* const_lhs = dynamic_cast<const sym::Const*>(lhs_);
            if(const_lhs != NULL && const_lhs->get_value() == 0)
            {
                out << 0;
                
                return out;

            }

        }

        if(rhs_->is_nullary())
        {
            const sym::Const* const_rhs = dynamic_cast<const sym::Const*>(rhs_);
            if(const_rhs != NULL && const_rhs->get_value() == 0) //duzelt unutma
            {
                out << 0;
                        
                return out;

            }


        }
        //out << "(";
        if (!lhs_->is_nullary()) 
        {
            out << "(";
            lhs_->operator<<(out);
            out << ")";
        } 
        else 
        {
            lhs_->operator<<(out);
        }
        
        out << " * ";
        
        if (!rhs_->is_nullary()) 
        {
            out << "(";
            rhs_->operator<<(out);
            out << ")";
        } 
        else 
        {
            rhs_->operator<<(out);
        }
        //out << ")";
        
        return out;
        
        
    }

	bool MulOp::operator==(const __expr_t& other_) const 
    { 
        if (const sym::MulOp* mul_op = dynamic_cast<const sym::MulOp*>(&other_)) 
        {
            return (*lhs_ == *(mul_op->lhs_)) && (*rhs_ == *(mul_op->rhs_));
        }
        
        return false;
    }
}
