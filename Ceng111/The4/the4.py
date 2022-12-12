
def inheritance(descriptions):
    inheritance = []
    def tidy(info):
        subset = []
        for i in info:
            if isinstance(i,tuple):
                subset.append(tidy)
            else:
                pass
        return subset

    def child_finder(tree):
        child_tree = {}
        for nodes in tree:
            child_tree[nodes] = []
            for descendant in tree[nodes]:
                if 'child' in descendant:
                    child_tree[nodes].append(descendant[0])
                else:
                    pass
        return child_tree

    def improved_descendant_finder(child_tree):
        for ascendant in child_tree:
            for descendant in child_tree[ascendant]:
                if descendant != []:
                    if child_tree[descendant] == []:
                        pass
                    else:
                        for person in child_tree[descendant]:
                            child_tree[ascendant].append(person)
                else:
                    pass
        descendant_tree = child_tree
        return descendant_tree

    def parent_finder(tree):
        parent_tree = {}
        for nodes in tree:
            parent_tree[nodes] = []
            for ascendant in tree[nodes]:
                if 'parent' in ascendant:
                    parent_tree[nodes].append(ascendant[0])
                else:
                    pass
        return parent_tree

    def improved_ascendent_finder(parenttree):
        for person in parenttree:
            for info in parenttree[person]:
                if info != []:
                    if parenttree[info] == []:
                        pass
                    else:
                        for parent in parenttree[info]:
                            if parent not in parenttree[person]:
                                parenttree[person].append(parent)
                else:
                    pass
        ascendent_tree = parenttree
        return ascendent_tree

    def deathbringer(moneytree,tree):
        new_money_tree = {}
        for person in moneytree:
                new_money_tree[person] = []
                if moneytree[person] == []:
                    pass
                else:
                    for ascendant in moneytree[person]:
                        if 'departed' not in tree[ascendant]:
                            new_money_tree[person].append(ascendant)
        return new_money_tree

    def child_counter(tree):
        child_info = {}
        for member in tree.keys():
            child_counter = 0
            for info in tree[member]:
                if 'child' in info:
                    child_counter += 1
            child_info[member] = child_counter
        return child_info

    def married_info(tree):
        married_tree = {}
        for member in tree.keys():
            married_tree[member] = []
            for info in tree[member]:
                if 'married' in info:
                    married_tree[member].append(info[0])
        return married_tree

    def check_alive(name):
        if 'departed' not in tree[name]:
            return 1
        else:
            return 0

    def eligible_list(tree,ascendants):
        eligiblelist = []
        for person in tree:
            if check_alive(person):
                eligiblelist.append(person)
                for asc in ascendants[person]:
                    if ascendants[person] != []:
                        if asc in eligiblelist:
                            pass
                        else:
                            eligiblelist.append(asc)
        return eligiblelist

    def business_pg1(wealth,dead,eligiblelist,child_tree):
        pie = []
        inheriters = []
        child_tree_dead = child_tree[dead]
        for person in child_tree_dead:
            money = 0
            if person in eligiblelist:
                inheriters.append(person)
        for mirasci in inheriters:
            if check_alive(mirasci):
                money = wealth / len(inheriters)
                pie.append((mirasci, money))
            else:
                pie.extend(business_pg1(wealth / len(inheriters), mirasci, eligiblelist, child_tree))

        return pie

    def business_pg2(wealth,dead,eligiblelist,parent_tree,child_tree):
        pie = []
        inheriters = []
        parent_tree_dead = parent_tree[dead]
        for person in parent_tree_dead:
            money = 0
            if person in eligiblelist:
                inheriters.append(person)
        for mirasci in inheriters:
            if check_alive(mirasci):
                money = wealth / len(inheriters)
                pie.append((mirasci, money))
            else:
                pie.extend(business_pg1(wealth / len(inheriters), mirasci, eligiblelist, child_tree))

        return pie
    def business_pg3(wealth,grandparents,eligiblelist,child_tree):
        el_grand = []
        pie = []
        for grandparent in grandparents:
            if grandparent in eligiblelist:
                el_grand.append(grandparent)
        for person in el_grand:
            if check_alive(person):
                money = wealth/len(el_grand)
                pie.append((person,money))
            else:
                pie.extend(business_pg1(wealth/len(el_grand),person,eligiblelist,child_tree))
        return pie
    def tree_maker(descriptions):
        info_tree = {}
        descriptions.sort()
        for i in descriptions:
            family = i.split()
            if family[0] == 'CHILD':
                for members in range(len(family)):
                    if members > 2:
                        if family[1] not in info_tree:
                            info_tree[family[1]] = [(family[members], 'child')]
                        else:
                            info_tree[family[1]].append((family[members], 'child'))
                        if family[2] not in info_tree:
                            info_tree[family[2]] = [(family[members], 'child')]
                        else:
                            info_tree[family[2]].append((family[members], 'child'))
                        if family[members] not in info_tree:
                            info_tree[family[members]] = [(family[1], 'parent'), (family[2], 'parent')]
                        else:
                            info_tree[family[members]].append((family[1], 'parent'))
                            info_tree[family[members]].append((family[2], 'parent'))
                    else:
                        pass

            elif family[0] == 'MARRIED':
                if family[1] not in info_tree:
                    info_tree[family[1]] = [(family[2], 'married')]
                else:
                    info_tree[family[1]].append((family[2], 'married'))
                if family[2] not in info_tree:
                    info_tree[family[2]] = [(family[1], 'married')]
                else:
                    info_tree[family[2]].append((family[1], 'married'))

            elif family[0] == 'DEPARTED':
                a = 'departed'
                if family[1] not in info_tree:
                    info_tree[family[1]] = [a]
                else:
                    info_tree[family[1]].append(a)
            else:
                if family[1] not  in info_tree:
                    info_tree[family[1]] = [(family[2])]
                else:
                    info_tree[family[1]].append(family[2])

        return info_tree

    descriptions.sort()
    tree = (tree_maker(descriptions))
    child_tree = child_finder(tree)
    descendant_tree = child_finder(tree)
    descendants= improved_descendant_finder(descendant_tree)
    parent_tree = parent_finder(tree)
    ascendant_tree = parent_finder(tree)
    ascendants = improved_ascendent_finder(ascendant_tree)
    not_dead_descendants = deathbringer(descendants,tree)
    not_dead_ascendants = deathbringer(ascendants,tree)
    child_amount = child_counter(tree)
    married = married_info(tree)
    eligibleList = eligible_list(tree,ascendants)

    for info in descriptions:
        information = info.split()
        if information[0] == 'DECEASED':
            dead = information[1] #mirasini dagitacagimiz kisi
            wealth = int(information[2]) #miras
            if married[dead] == []: # esi oluyse
                if not_dead_descendants[dead] != []:
                    pg_1 = business_pg1(wealth,dead,eligibleList,child_tree)
                    for i in pg_1:
                        inheritance.append(i)
                elif parent_tree[dead] != []:
                        if 'departed' not in tree[parent_tree[dead][0]] or 'departed' not in tree[parent_tree[dead][1]]:
                            pg_2 = business_pg2(wealth,dead,eligibleList,parent_tree,child_tree)
                            for i in pg_2:
                                inheritance.append(i)
                        else:
                            if not_dead_descendants[parent_tree[dead][0]] == [] and not_dead_descendants[parent_tree[dead][0]] == []:
                                grandparents =[]
                                for parent in parent_tree[dead]:
                                    for grandparent in parent_tree[parent]:
                                        grandparents.append(grandparent)
                                pg_3 = business_pg3(wealth,grandparents,eligibleList,child_tree)
                                for i in pg_3:
                                    inheritance.append(i)
                            else:
                                pg_2 = business_pg2(wealth,dead,eligibleList,parent_tree,child_tree)
                                for i in pg_2:
                                    inheritance.append(i)
                else:
                    return []
            elif 'departed' in tree[married[dead][0]]:
                if not_dead_descendants[dead] != []:
                    pg_1 = business_pg1(wealth,dead,eligibleList,child_tree)
                    for i in pg_1:
                        inheritance.append(i)
                elif parent_tree[dead] != []:
                        if 'departed' not in tree[parent_tree[dead][0]] or 'departed' not in tree[parent_tree[dead][1]]:
                            pg_2 = business_pg2(wealth,dead,eligibleList,parent_tree,child_tree)
                            for i in pg_2:
                                inheritance.append(i)
                        else:
                            if not_dead_descendants[parent_tree[dead][0]] == [] and not_dead_descendants[parent_tree[dead][0]] == []:
                                grandparents =[]
                                for parent in parent_tree[dead]:
                                    for grandparent in parent_tree[parent]:
                                        grandparents.append(grandparent)
                                pg_3 = business_pg3(wealth,grandparents,eligibleList,child_tree)
                                for i in pg_3:
                                    inheritance.append(i)
                            else:
                                pg_2 = business_pg2(wealth,dead,eligibleList,parent_tree,child_tree)
                                for i in pg_2:
                                    inheritance.append(i)
                else:
                    return []
            else:
                if not_dead_descendants[dead] != []:
                    spouse = wealth/4
                    inheritance.append((married[dead][0],spouse))
                    new_wealth = wealth*3/4
                    pg_1 = business_pg1(new_wealth,dead,eligibleList,child_tree)
                    for i in pg_1:
                        inheritance.append(i)
                elif parent_tree[dead] != []:
                    if 'departed' not in tree[parent_tree[dead][0]] or 'departed' not in tree[parent_tree[dead][1]]:
                        spouse = wealth / 2
                        new_wealth = wealth / 2
                        inheritance.append((married[dead][0], spouse))
                        pg_2 = business_pg2(new_wealth, dead, eligibleList, parent_tree, child_tree)
                        for i in pg_2:
                            inheritance.append(i)
                    else:
                        if not_dead_descendants[parent_tree[dead][0]] == [] and not_dead_descendants[parent_tree[dead][0]] == []:
                            spouse = wealth*3/4
                            new_wealth = wealth/4
                            inheritance.append((married[dead][0],spouse))
                            grandparents = []
                            for parent in parent_tree[dead]:
                                for grandparent in parent_tree[parent]:
                                    grandparents.append(grandparent)
                            pg_3 = business_pg3(new_wealth,grandparents,eligibleList,child_tree)
                            for i in pg_3:
                                inheritance.append(i)
                        else:
                            spouse = wealth / 2
                            new_wealth = wealth / 2
                            inheritance.append((married[dead][0], spouse))
                            pg_2 = business_pg2(new_wealth, dead, eligibleList, parent_tree, child_tree)
                            for i in pg_2:
                                inheritance.append(i)
                else:
                    spouse = wealth
                    inheritance.append((married[dead][0],spouse))
    back_up = inheritance[:]
    new_inheritance = []
    for i in inheritance:
        new_amount = i[1]
        back_up.remove(i)
        for h in back_up:
            if i[0] in h:
                for j in back_up:
                    if i[0] == j[0]:
                        new_amount += j[1]
                        new_inheritance.append((i[0],new_amount))
    back_up2 = inheritance[:]
    for k in new_inheritance:
        for l in inheritance:
            if k[0] == l[0]:
                back_up2.remove(l)
    inheritance = back_up2[:]
    for last in new_inheritance:
        inheritance.append(last)
    return inheritance
