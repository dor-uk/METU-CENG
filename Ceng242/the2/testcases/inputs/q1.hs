import PE2

dungeonMap = Node NarrowPassage [] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf NarrowPassage [Treasure (Gold 10), Treasure (Potion 5)],
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)],
        Leaf Cavern [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]]]

path1 = traversePath 50 dungeonMap [0, 0]
path2 = traversePath 15 dungeonMap [1, 0]
path3 = traversePath 40 dungeonMap [1, 1]
path4 = traversePath 15 dungeonMap [1, 2]

main = do
    putStrLn (show path1)
    putStrLn (show path2)
    putStrLn (show path3)
    putStrLn (show path4)

data Tree a b = EmptyTree | Leaf a b | Node a b [Tree a b] deriving (Show, Eq)

-- Every location in the tree is of some Chamber type.
data Chamber = Cavern |
               NarrowPassage |
               UndergroundRiver |
               SlipperyRocks deriving (Show, Eq)

-- An enemy has a name, an amount of damage that it deals
-- and an amount of gold that it drops (in that order).
data Enemy = Enemy String Integer Integer deriving (Show, Eq)

-- Gold n gives n amount of gold
-- Potion n heals n hp
data Loot = Gold Integer | Potion Integer deriving (Show, Eq)

-- An encounter is either a Fight with an Enemy, or a treasure where
-- you find Loot
data Encounter = Fight Enemy | Treasure Loot deriving (Show, Eq)

-- This is a type synonym for how we will represents our dungeons
type Dungeon = Tree Chamber [Encounter]

-- First argument is starting HP
-- Second argument is the dungeon map
-- Third argument is the path (each integer in the list shows what child
-- you descend into)
-- Calculate how much HP you have left and how much gold you've
-- accumulated after traversing the given path

preorder :: Dungeon -> [Chamber]
preorder EmptyTree = []
preorder (Leaf chamber encounter) = [chamber]
preorder (Node chamber info subtrees) = [chamber] ++ concatMap preorder subtrees
--preorder (Node chamber info [Tree left right]) = [chamber] ++ preorder left ++ preorder right


------------------------------------apply encounter-------------------------------------------------------
action_merge :: [Encounter] -> [(Integer, Integer)]
action_merge [] = []
action_merge (first:rest) = case first of
                               Fight (Enemy name damage loot) -> (-damage, loot) : action_merge rest
                               Treasure action -> case action of
                                                     Gold loot -> (0, loot) : action_merge rest
                                                     Potion loot -> (loot, 0) : action_merge rest
                                                     --_ -> action_merge rest
sum_first :: [(Integer, Integer)] -> Integer
sum_first [] = 0
sum_first (first:rest) = fst(first) + sum_first rest     

sum_second :: [(Integer, Integer)] -> Integer
sum_second [] = 0
sum_second (first:rest) = snd(first) + sum_second rest 

sum_total :: [(Integer, Integer)] -> (Integer, Integer)
sum_total [] = (0,0)
sum_total list = (sum_first list, sum_second list) 

--apply_encounter :: Integer -> Integer -> [Encounter] -> (Integer, Integer)
--apply_encounter hp money [] = (hp,money)
--apply_encounter hp money encounter_l = let merged_list = action_merge encounter_l
--                                           (hp_sum, money_sum) = sum_total merged_list
--                                           in (hp + hp_sum, money + money_sum)

apply_encounter :: Integer -> Integer -> [Encounter] -> (Integer, Integer)
apply_encounter hp money [] = (hp,money)
apply_encounter hp money (first:rest) =
  case first of
    Fight (Enemy _ damage loot) -> apply_encounter (hp - damage) (money + loot) rest
    Treasure (Gold loot) -> apply_encounter hp (money + loot) rest
    Treasure (Potion heal) -> apply_encounter (hp + heal) money rest
--    _ -> apply_encounter hp money rest
                                  
-------------------------------------------------------------------------------------------------------------

--------------------------------------------- find node-----------------------------------------------------


getNodeByPath :: Tree a b -> [Int] -> [Tree a b]                       --takes a dungeon and a path to follow, gives a visited list and the last visited node
getNodeByPath EmptyTree _ = [EmptyTree]
getNodeByPath node [] = [node]
getNodeByPath (Leaf a b) [0] = ([Leaf a b])                              --if we reach a leaf, then there is no place left to traverse
getNodeByPath (Node a b subtrees) (index:indices)                                --if we are at a node then there are three possibilities
    | index >= length subtrees = error "Index out of bounds"                     --index can be bigger than the tree, in this case throw an error
    | null indices = let (visited) = getNodeByPath (subtrees !! index) [0]  --we may be at the last location of the desired path
                     in ((Node a b visited):visited)                        --(Node a b visited):visited represents the path of the tree that was traversed to reach the desired node
    | otherwise = let (visited) = getNodeByPath (subtrees !! index) indices --we may still have a path to follow 
                  in ((Node a b visited):visited)                           --res: this is a tuple that contains the values stored in the node that was reached, (a, b) 
--getNodeByPath _ _ = error "Invalid path"

getNodeValuesByPath :: Tree a b -> [Int] -> [Tree a b]                           --used fst to extract the visited list
getNodeValuesByPath t path = concat [tail $ getNodeByPath t path]          --used tail to not include the root, question doesn't want to include

-------------------------------------------------------------------------------------------------------------------

traversePath_h :: Integer -> Integer -> Dungeon -> [Int] -> (Integer, Integer)
traversePath_h hp money EmptyTree _ = (hp, money)
traversePath_h hp money _ [] = (hp, money)
traversePath_h hp money (Leaf a b) [0] = apply_encounter hp money b
traversePath_h hp money dungeon path = let nodes = getNodeValuesByPath dungeon path
                                           first = head nodes
                                           (encounter, next) = case first of
                                                                 (Node chamber encount second) -> (encount,second)
                                           (new_hp, new_money) = apply_encounter hp money encounter
                                           in traversePath_h new_hp new_money (head next) (tail path) 

--traversePath :: Integer -> Dungeon -> [Int] -> (Integer, Integer)
--traversePath hp dungeon path = case getNodeValuesByPath dungeon path of
--                                 [node] -> case node of
--                                             Leaf _ encounter -> apply_encounter hp 0 encounter
--                                             Node _ _ _ -> (hp, 0)
--                                 _ -> (hp, 0)


traversePath :: Integer -> Dungeon -> [Int] -> (Integer, Integer)
traversePath hp dungeon path = let money = 0
                                   (new_hp, new_money) = traversePath_h hp money dungeon path
                                   in (new_hp, new_money)
--mylist = preorder dungeonMap
dungeonMap = Node NarrowPassage [] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf NarrowPassage [Treasure (Gold 10), Treasure (Potion 5)],
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)],
        Leaf Cavern [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]]]


mylist = action_merge [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]

tot_list = sum_total mylist
res = apply_encounter 50 0 [Fight (Enemy "Goblins" 5 2),Fight (Enemy "Imp" 4 4),Treasure (Potion 15),Fight (Enemy "Bear" 15 9)]
nodes = getNodeValuesByPath dungeonMap [1,0]
first = head nodes
(encounter, next) = case first of
                       (Node chamber encount second) -> (encount,second)

path1 = traversePath 50 dungeonMap [0, 0]
path2 = traversePath 15 dungeonMap [1, 0]
path3 = traversePath 40 dungeonMap [1, 1]
path4 = traversePath 15 dungeonMap [1, 2]

main = do
    putStrLn (show path1)
    putStrLn (show path2)
    putStrLn (show path3)
    putStrLn (show path4)

--main = print(traversePath 20 dungeonMap [1,0])
--main = print res
--main = let nodes = getNodeValuesByPath dungeonMap [1,2]
           --encounter = concatMap (\(Node _ _ encounters) -> encounters) nodes
           --in print encounter
--main = print (make_encounter_list first)
--main = print (encounter,next)