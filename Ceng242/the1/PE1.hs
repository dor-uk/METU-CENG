module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
--getIngredientCost _ _ = 0
getIngredientCost tuple_x price_l = getRounded (second/kilo*price)  --Does the thing you want
                                    where   first = fst(tuple_x)    --Assign elements of tuple
                                            second = snd(tuple_x)   --Assign elements of tuple
                                            (Price name kilo price) = head $filter (\(Price name _ _) ->name == first) price_l
                                            --assign the values to price name and kilo = filter your price list with your predicate
                                            --head takes the first element of the list. In this case we only have one element in the list
                                            --(Price name _ _) is the predicate = what you want to find in the list


-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (Recipe _ []) _ = 0
recipeCost (Recipe _ ingredient_l) price_l = let (ingredient,kilo) = head ingredient_l                      --take the first element of the ingredient list
                                                 cost = getIngredientCost (ingredient,kilo) price_l         --calculate the cost of it
                                              in getRounded(cost + recipeCost (Recipe "" (tail ingredient_l)) price_l ) --use recursion to calculate the cost of ingredient list
                                                                                                            --used "" to create a new Recipe with an empty name, since
                                                                                                            --we don't need to specify the name for the recursive call.
                                                                                                            --used tail to because we need the ingredient list without
                                                                                                            --the first ingredient in the list until we have 0 ingredient

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients (Recipe _ []) _  = []
missingIngredients (Recipe _ ingredient_l) stock_l = let (ingredient,kilo) = head ingredient_l
                                                         (name, stock_kilo) = case filter (\(name, _) ->name == ingredient) stock_l of
                                                                                [] -> (ingredient, 0)                       --case where filter returns an empty list
                                                                                [(name,stock_kilo)] -> (name,stock_kilo)    --case where filter returns an list
                                                      in if stock_kilo < kilo
                                                            then (ingredient,getRounded(kilo-stock_kilo)): missingIngredients (Recipe "" (tail ingredient_l)) stock_l  --important
                                                            else missingIngredients (Recipe "" (tail ingredient_l)) stock_l

-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe _ (Recipe _ []) = []
makeRecipe stock_l (Recipe nameR ingredient_l) = let missing = missingIngredients (Recipe nameR ingredient_l) stock_l
                                                  in if missing /= []
                                                        then stock_l
                                                        else let (ingredient_s,stock_kilo) = head stock_l
                                                                 newlist = if filter (\(name, quantity) ->name == ingredient_s) ingredient_l == []
                                                                              then [(ingredient_s,stock_kilo)]
                                                                              else let [(ingredient,kilo)] = filter (\(name, quantity) ->name == ingredient_s) ingredient_l
                                                                                       in [(ingredient,getRounded(stock_kilo - kilo))]
                                                                 ing_name_list_comp = filter (\(name, quantity) ->name /= ingredient_s) ingredient_l                      
                                                                 in concat[newlist, makeRecipe (tail stock_l) (Recipe "" ing_name_list_comp)] 




findcost :: [(String, Double)] -> [Price] -> [(String, Double, Double)]
findcost [] _ = []
findcost missing_l price_l = let (ingredient,kilo) = head missing_l                      
                                 cost = getIngredientCost (ingredient,kilo) price_l
                                 in (ingredient,kilo,cost): findcost (tail missing_l) price_l                       --concat the element with the recursive result
                                                
                                                
                                                


merge_helper :: [Recipe] -> [(String, Double)]
merge_helper [] = []
merge_helper ((Recipe name first):others)  = if length(others) == 0
                                                then first 
                                                else first ++ merge_helper others                                   --(Recipe name first):others
                                                                                                                    --(Recipe name first) = head of recipe list
                                                                                                                    --others = tail of recipe list

sum_helper :: [(String, Double)] -> Double
sum_helper [] = 0
sum_helper (first:others) = snd(first) + sum_helper others



remove_duplicates :: [(String, Double)] -> [(String, Double)]
remove_duplicates [] = []
remove_duplicates clist = let (ingredient, kilo) = head clist
                              ing_name_list = filter (\(name, quantity) -> name == ingredient) clist                 --find same ingredient in different recipes
                              ing_name_list_comp = filter (\(name, quantity) -> name /= ingredient) (tail clist)     --find ingredients that not equal to our ingredient
                              in [(ingredient, sum_helper(ing_name_list))] ++ remove_duplicates ing_name_list_comp   -- ++ = concat



--in (ingredient,stock_kilo-kilo): makeRecipe stock_l (Recipe "" (tail ingredient_l))                                                                
-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList _ [] _ = []
makeShoppingList stock_l recipe_l price_l = let merged_list = remove_duplicates(merge_helper recipe_l)
                                                missing = missingIngredients (Recipe "" merged_list) stock_l
                                                in if missing == []
                                                      then []
                                                      else findcost missing price_l
                                           





