from config import start_database


def add_blacklists(data):
    conn = start_database()
    cursor = conn.cursor()
    if data['typeid'] ==1:  #买家
        insert = "update Buyer SET Valid = \'" + str(1) + "\' where Username = \'" + data['username'] + '\''
        cursor.execute(insert)
        result = cursor.fetchone()
    elif data['typeid'] ==0:
        insert = "update Seller SET Valid = \'" + str(1) + "\' where Username = \'" + data['username'] + '\''
        cursor.execute(insert)
        result = cursor.fetchone()
    else:
        print("Not found the user!")  #警告框
    return


def delete_blacklists(data):
    conn = start_database()
    cursor = conn.cursor()
    print(data)

    if data['typeid'] == True:
        print("1")
        data['typeid']='1'
    else:
        print("0")
        data['typeid']='0'

    insert = """ select * from Blacklists where Username = '"""+ data['username'] + """' and TypeId = '"""+ data['typeid'] + """' """
    print(insert)
    cursor.execute(insert)
    result = cursor.fetchone()
    print(result)
    if result:
        print("in the blacklists")
        insert = """delete from Blacklists where UserName = '"""+ data['username'] + """'  and TypeId =  '"""+ data['typeid'] + """' """
        cursor.execute(insert)
        print("already delete")
        insert = """ select * from Blacklists where Username = '""" + data['username'] + """' and TypeId = '""" + data['typeid'] + """' """
        print(insert)
        cursor.execute(insert)
        result = cursor.fetchone()
        print(result)
    else:
        print("Not in!")


def manager_maintain(username:str, permission:int)->str:
    conn = start_database()
    cursor = conn.cursor()
    insert = "update Administrator SET Permission = \'" + str(permission) + "\' where Username = \'" + username + '\''
    cursor.execute(insert)


def manager_right(value:int)->[]:
    right = []
    if value >= 16:
        right.append('DeleteRight')
        value = value - 16
    if value >= 8:
        right.append('AddRight')
        value = value - 8
    if value >= 4:
        right.append('ArbitrationRight')
        value = value - 4
    if value >= 2:
        right.append('BlacklistRight')
        value = value - 2
    if value >= 1:
        right.append('ViewRight')
        value = value - 1
    return right


def manager_query(username:str)->[]:
    conn = start_database()
    cursor = conn.cursor()
    insert = "select * from Administrator where Username = \'" + username + '\''
    cursor.execute(insert)
    result = cursor.fetchone()
    if result:
        return manager_right(result[5])
    right = []
    right.append('Username Not Found')
    return right


def manager_delete(username:str)->str:
    conn = start_database()
    cursor = conn.cursor()
    insert = "delete from Administrator where Username = \'" + username + '\''
    cursor.execute(insert)
    insert = "select * from Administrator where Username = \'" + username + '\''
    cursor.execute(insert)
    result = cursor.fetchone()
    if result:
        return "Delete Succeed"
    else:
        return "User Not Found"



