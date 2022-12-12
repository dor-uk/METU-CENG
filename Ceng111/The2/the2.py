


num = input()
soru = num.find('?')
if soru == -1:
    if num[5] == 'X':
        digtop = int(num[0]) * 2 + int(num[1]) * 3 + int(num[2]) * 5 + int(num[3]) * 7
        checkdig = digtop % 11
        if checkdig == 10:
            print('VALID')
        else:
            print('INVALID')
    else:
        digtop = int(num[0]) * 2 + int(num[1]) * 3 + int(num[2]) * 5 + int(num[3]) * 7
        checkdig = digtop % 11
        if checkdig == int(num[5]):
            print('VALID')
        else:
            print('INVALID')
elif soru == 5:
    digtop = int(num[0]) * 2 + int(num[1]) * 3 + int(num[2]) * 5 + int(num[3]) * 7
    checkdig = str(digtop % 11)
    if checkdig == '10':
        print(num[0:5] + 'X')
    else:
        print(num[0:5] + checkdig)
else:
    new = num[0] + ',' + num[1] + ',' + num[2] + ',' + num[3]
    sp = new.split(",")
    if num[5] != 'X':
        if sp[0] == '?':
            ilk = int(sp[1]) * 3 + int(sp[2]) * 5 + int(sp[3]) * 7 - int(num[5])
            if ilk % 11 == 0:
                print('0' + num[1:6])
            else:
                if ((22 - ilk % 11) / 2) != int(((22 - ilk % 11) / 2)):
                    n2 = int((11 - ilk % 11) / 2)
                    print(str(n2) + num[1:6])
                else:
                    n = int(((22 - ilk % 11) / 2))
                    if n == 10:
                        print('0' + num[1:6])
                    else:
                        print(str(n) + num[1:6])
        elif sp[1] == '?':
            iki = int(sp[0]) * 2 + int(sp[2]) * 5 + int(sp[3]) * 7 - int(num[5])
            if iki % 11 == 0:
                print(num[0] + '0' + num[2:6])
            else:
                if int((11 - iki % 11) / 3) == ((11 - iki % 11) / 3):
                    n3 = int((11 - iki % 11) / 3)
                    print(num[0] + str(n3) + num[2:6])
                elif int((33 - iki % 11) / 3) == (33 - iki % 11) / 3:
                    n4 = int((33 - iki % 11) / 3)
                    if n4 == 10:
                        print(num[0] + '0' + num[2:6])
                    else:
                        print(num[0] + str(n4) + num[2:6])
                else:
                    n = int((22 - iki % 11) / 3)
                    print(num[0] + str(n) + num[2:6])
        elif sp[2] == '?':
            uc = int(sp[0]) * 2 + int(sp[1]) * 3 + int(sp[3]) * 7 - int(num[5])
            if uc % 11 == 0:
                print(num[0:2] + '0' + num[3:6])
            else:
                if ((11 - uc % 11) / 5) == int((11 - uc % 11) / 5):
                    n5 = int((11 - uc % 11) / 5)
                    print(num[0:2] + str(n5) + num[3:6])
                elif ((33 - uc % 11) / 5) == int((33 - uc % 11) / 5):
                    n6 = int((33 - uc % 11) / 5)
                    print(num[0:2] + str(n6) + num[3:6])
                elif ((44 - uc % 11) / 5) == int((44 - uc % 11) / 5):
                    n7 = int((44 - uc % 11) / 5)
                    print(num[0:2] + str(n7) + num[3:6])
                elif ((55 - uc % 11) / 5) == int((55 - uc % 11) / 5):
                    n8 = int((55 - uc % 11) / 5)
                    if n8 == 10:
                        print(num[0:2] + '0' + num[3:6])
                    else:
                        print(num[0:2] + str(n8) + num[3:6])
                else:
                    n = int((22 - uc % 11) / 5)
                    print(num[0:2] + str(n) + num[3:6])
        else:
            son = int(sp[0]) * 2 + int(sp[1]) * 3 + int(sp[2]) * 5 - int(num[5])
            if son % 11 == 0:
                print(num[0:3] + '0' + num[4:6])
            else:
                if ((11 - son % 11) / 7) == int((11 - son % 11) / 7):
                    n9 = int((11 - son % 11) / 7)
                    print(num[0:3] + str(n9) + num[4:6])
                elif ((33 - son % 11) / 7) == int((33 - son % 11) / 7):
                    n10 = int((33 - son % 11) / 7)
                    print(num[0:3] + str(n10) + num[4:6])
                elif ((44 - son % 11) / 7) == int((44 - son % 11) / 7):
                    n11 = int((44 - son % 11) / 7)
                    print(num[0:3] + str(n11) + num[4:6])
                elif ((55 - son % 11) / 7) == int((55 - son % 11) / 7):
                    n12 = int((55 - son % 11) / 7)
                    print(num[0:3] + str(n12) + num[4:6])
                elif ((66 - son % 11) / 7) == int((66 - son % 11) / 7):
                    n13 = int((66 - son % 11) / 7)
                    print(num[0:3] + str(n13) + num[4:6])
                elif ((77 - son % 11) / 7) == int((77 - son % 11) / 7):
                    print(num[0:3] + '0' + num[4:6])
                else:
                    n = int((22 - son % 11) / 7)
                    print(num[0:3] + str(n) + num[4:6])
    else:
        if sp[0] == '?':
            ilk = int(sp[1]) * 3 + int(sp[2]) * 5 + int(sp[3]) * 7 - 10
            if ilk % 11 == 0:
                print('0' + num[1:6])
            else:
                if ((22 - ilk % 11) / 2) != int(((22 - ilk % 11) / 2)):
                    n2 = int((11 - ilk % 11) / 2)
                    print(str(n2) + num[1:6])
                else:
                    n = int(((22 - ilk % 11) / 2))
                    if n == 10:
                        print('0' + num[1:6])
                    else:
                        print(str(n) + num[1:6])
        elif sp[1] == '?':
            iki = int(sp[0]) * 2 + int(sp[2]) * 5 + int(sp[3]) * 7 - 10
            if iki % 11 == 0:
                print(num[0] + '0' + num[2:6])
            else:
                if int((11 - iki % 11) / 3) == ((11 - iki % 11) / 3):
                    n3 = int((11 - iki % 11) / 3)
                    print(num[0] + str(n3) + num[2:6])
                elif int((33 - iki % 11) / 3) == (33 - iki % 11) / 3:
                    n4 = int((33 - iki % 11) / 3)
                    if n4 == 10:
                        print(num[0] + '0' + num[2:6])
                    else:
                        print(num[0] + str(n4) + num[2:6])
                else:
                    n = int((22 - iki % 11) / 3)
                    print(num[0] + str(n) + num[2:6])
        elif sp[2] == '?':
            uc = int(sp[0]) * 2 + int(sp[1]) * 3 + int(sp[3]) * 7 - 10
            if uc % 11 == 0:
                print(num[0:2] + '0' + num[3:6])
            else:
                if ((11 - uc % 11) / 5) == int((11 - uc % 11) / 5):
                    n5 = int((11 - uc % 11) / 5)
                    print(num[0:2] + str(n5) + num[3:6])
                elif ((33 - uc % 11) / 5) == int((33 - uc % 11) / 5):
                    n6 = int((33 - uc % 11) / 5)
                    print(num[0:2] + str(n6) + num[3:6])
                elif ((44 - uc % 11) / 5) == int((44 - uc % 11) / 5):
                    n7 = int((44 - uc % 11) / 5)
                    print(num[0:2] + str(n7) + num[3:6])
                elif ((55 - uc % 11) / 5) == int((55 - uc % 11) / 5):
                    n8 = int((55 - uc % 11) / 5)
                    if n8 == 10:
                        print(num[0:2] + '0' + num[3:6])
                    else:
                        print(num[0:2] + str(n8) + num[3:6])
                else:
                    n = int((22 - uc % 11) / 5)
                    print(num[0:2] + str(n) + num[3:6])
        else:
            son = int(sp[0]) * 2 + int(sp[1]) * 3 + int(sp[2]) * 5 - 10
            if son % 11 == 0:
                print(num[0:3] + '0' + num[4:6])
            else:
                if ((11 - son % 11) / 7) == int((11 - son % 11) / 7):
                    n9 = int((11 - son % 11) / 7)
                    print(num[0:3] + str(n9) + num[4:6])
                elif ((33 - son % 11) / 7) == int((33 - son % 11) / 7):
                    n10 = int((33 - son % 11) / 7)
                    print(num[0:3] + str(n10) + num[4:6])
                elif ((44 - son % 11) / 7) == int((44 - son % 11) / 7):
                    n11 = int((44 - son % 11) / 7)
                    print(num[0:3] + str(n11) + num[4:6])
                elif ((55 - son % 11) / 7) == int((55 - son % 11) / 7):
                    n12 = int((55 - son % 11) / 7)
                    print(num[0:3] + str(n12) + num[4:6])
                elif ((66 - son % 11) / 7) == int((66 - son % 11) / 7):
                    n13 = int((66 - son % 11) / 7)
                    print(num[0:3] + str(n13) + num[4:6])
                elif ((77 - son % 11) / 7) == int((77 - son % 11) / 7):
                    print(num[0:3] + '0' + num[4:6])
                else:
                    n = int((22 - son % 11) / 7)
                    print(num[0:3] + str(n) + num[4:6])
