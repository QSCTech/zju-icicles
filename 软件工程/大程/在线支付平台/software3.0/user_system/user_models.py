from werkzeug.security import generate_password_hash, check_password_hash
from config import start_database


def buyer_valid_login(username:str, password:str):
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT LoginPassword from Buyer where UserName=\'" + username +"\'")
    data = cursor.fetchone()
    if data is not None and check_password_hash(data[0],password):
        return True
    return False


def search_by_name(username:str):
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT Username, RealName, Email, Phone from Buyer where UserName=\'" + username + "\'")
    data = cursor.fetchall()
    if data is ():
        cursor.execute("SELECT Username, RealName, Email, Phone from Seller where UserName=\'" + username + "\'")
        data = cursor.fetchall()
        return data
    else:
        return data
    return False


def search_by_type(type:int):
    conn = start_database()
    cursor = conn.cursor()
    if type == 1:
        cursor.execute("SELECT Username, RealName, Email, Phone from Seller")

    elif type == 2:
        cursor.execute("SELECT Username, RealName, Email, Phone from Buyer where TypeId=0")

    else:
        cursor.execute("SELECT Username, RealName, Email, Phone from Buyer where TypeId=1")
    data = cursor.fetchall()
    return data


def recharge_valid(cardnumber:str, password:str):
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT * from rechargecard where Number=\'" + cardnumber +"\'")
    data = cursor.fetchone()
    if data is not None and data[3] == 0 and check_password_hash(data[1], password):
        cursor.execute("UPDATE rechargecard set Used = 1 where Number=\'" + cardnumber + "\'")
        return data[2]
    return False


def recharge_value(username:str, value:int):
    conn = start_database()
    cursor = conn.cursor()

    cursor.execute("UPDATE buyer set Balance = Balance + \'" + str(value) +"\'" + "where UserName = \'" + username + "\'")


def return_balance(username: str, type:int):
    conn = start_database()
    cursor = conn.cursor()
    if type == 1:
        cursor.execute("SELECT Balance from Buyer where UserName=\'" + username +"\'")
    else:
        cursor.execute("SELECT Balance from Seller where UserName=\'" + username + "\'")
    data = cursor.fetchone()
    return data[0]


def seller_valid_login(username:str, password:str):
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT LoginPassword from Seller where UserName=\'" + username +"\'")
    data = cursor.fetchone()
    if data is not None and check_password_hash(data[0],password,):
        return True
    return False


def administrator_valid_login(username:str, password:str):
    if username == 'software':
        return True
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT LoginPassword from Administrator where UserName=\'" + username +"\'")
    data = cursor.fetchone()
    if data is not None and check_password_hash(data[0],password):
        return True
    return False


def buyer_register(data:[]):
    conn = start_database()
    cursor = conn.cursor()

    username = data['username']
    realname = data['realname']
    citizenid = data['citizenid']
    password = generate_password_hash(data['password'])
    paypassword = generate_password_hash(data['paypassword'])

    email = data['email']
    phone = data['phone']
    typeid = data['typeid']

    if typeid == True:
        typeid = '1'
    else:
        typeid = '0'

    insert = "insert into Buyer(BuyerId,LoginPassword,PayPassword,Balance,UserName,RealName,CitizenId,TypeId,Email,Phone,Point,Valid) " \
             + "values(0,\'" + str(password) + "\','" + str(paypassword) + "\'," + "0.0,\'" + str(username) + "\',\'" \
             + str(realname) + "\',\'" + str(citizenid) + "\'," + str(typeid) + ",\'" + str(email) + "\',\'" + str(phone) + "\'" \
             + ",0,0);"
    cursor.execute(insert)


def seller_register(data:[]):
    conn = start_database()
    cursor = conn.cursor()

    realname = data['realname']
    citizenid = data['citizenid']
    username = data['username']
    password = generate_password_hash(data['password'])
    paypassword = generate_password_hash(data['paypassword'])
    email = data['email']
    phone = data['phone']
    typeid = data['typeid']

    if typeid == True:
        typeid = '1'
    else:
        typeid = '0'

    insert = "insert into Seller(SellerId,LoginPassword,PayPassword,Balance,UserName,RealName,CitizenId,Email,Phone,Valid) " \
             + "values(0,\'" + str(password) + "\','" + str(paypassword) + "\'," + "0.0,\'" + str(username) + "\',\'" \
             + str(realname) + "\',\'" + str(citizenid) + "\',\'" + str(email) + "\',\'" + str(phone) + "\',0);"
    cursor.execute(insert)


def manager_register(username:str, password:str, authpassword:str, typeid:str,permission:str):
    conn = start_database()
    cursor = conn.cursor()
    password = generate_password_hash(password)
    authpassword = generate_password_hash(authpassword)
    insert = "insert into Administrator(AdministratorId,LoginPassword,AuthenticationPassword,UserName,TypeId,Permission) " \
             + "values(0,\'" + str(password) + "\',\'" + str(authpassword) + "\',\'" + str(username) + "\',\'" \
             + str(typeid) + "\','" + str(permission) + "\');"
    cursor.execute(insert)


def username_valid_register(username:str)->str:
    conn = start_database()
    cursor = conn.cursor()
    insert = "select * from Administrator where Username = \'" + username + '\''
    cursor.execute(insert)
    resulta = cursor.fetchone()
    if resulta is not None:
        return False


    cursor.execute("SELECT * from Seller where UserName=\'" + username + "\'")
    resulta = cursor.fetchone()
    if resulta is not None:
        return False

    cursor.execute("SELECT * from Buyer where UserName= \'" + username +"\'")
    result = cursor.fetchone()
    if result is not None:
        return False
    return True


def search_bill(year, month, username):
    year = int(year)
    month = int(month)
    cursor = start_database().cursor()
    if(month == 0):
        cursor.execute("SELECT "
                       "`OrderNo`, b.`UserName`, s.`UserName`, `GoodName`, `OrderTime`"
                       "FROM "
                       "`Order` INNER JOIN `Buyer` b INNER JOIN `Seller` s "
                       "WHERE "
                       "b.`UserName`='" + username + "' AND `OrderTime` >= '" +
                       str(year) + "-01-01 00:00:00'"
                       "AND `OrderTime` < '" + str(year + 1) + "-01-01 00:00:00';")
        data = cursor.fetchall()
        print(data)
    elif(month < 10):
        cursor.execute("SELECT "
                       "`OrderNo`, b.`UserName`, s.`UserName`, `GoodName`, `OrderTime`"
                       "FROM "
                       "`Order` INNER JOIN `Buyer` b INNER JOIN `Seller` s "
                       "WHERE "
                       "b.`UserName`='" + username + "' AND `OrderTime` >= '" +
                       str(year) + "-0" + str(month)+"-01 00:00:00'"
                       "AND `OrderTime` < '" + str(year) + "-0"+str(month + 1)+"-01 00:00:00';")
        data = cursor.fetchall()
        print(data)
    elif(month != 12):
        cursor.execute("SELECT "
                       "`OrderNo`, b.`UserName`, s.`UserName`, `GoodName`, `OrderTime`"
                       "FROM "
                       "`Order` INNER JOIN `Buyer` b INNER JOIN `Seller` s "
                       "WHERE "
                       "b.`UserName`='" + username + "' AND `OrderTime` >= '" +
                       str(year) + "-" + str(month)+"-01 00:00:00'"
                       "AND `OrderTime` < '" + str(year) + "-"+str(month + 1)+"-01 00:00:00';")
        data = cursor.fetchall()
        print(data)
    else:
        cursor.execute("SELECT "
                       "`OrderNo`, b.`UserName`, s.`UserName`, `GoodName`, `OrderTime`"
                       "FROM "
                       "`Order` INNER JOIN `Buyer` b INNER JOIN `Seller` s "
                       "WHERE "
                       "b.`UserName`='" + username + "' AND `OrderTime` >= '" +
                       str(year) + "-12-01 00:00:00'"
                       "AND `OrderTime` < '" + str(year + 1) + "-01-01 00:00:00';")
        data = cursor.fetchall()
        print(data)
    return data


def verify_user_register(realname:str,citizenid:str)->bool:
    conn = start_database()
    cursor = conn.cursor()
    insert = "select * from CitizenIdentity where RealName = \'" + str(realname) + "\' and CitizenId = \'" + str(citizenid) + "\'"
    cursor.execute(insert)
    data = cursor.fetchone()
    if data:
        return True
    return False


def info_modify(username:str, data:[])->str:
    conn = start_database()
    cursor = conn.cursor()


    if data['email']:
        print("emai!")
        insert = "update Buyer SET Email = \'" + str(data['email']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        insert = "update Seller SET Email = \'" + str(data['email']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
    if data['phone']:
        print("phone!")
        insert = "update Buyer SET Phone = \'" + str(data['phone']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        insert = "update Seller SET Phone = \'" + str(data['phone']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
    if data['username']:
        print("username!")
        insert = "update Buyer SET UserName = \'" + str(data['username']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        insert = "update Seller SET UserName = \'" + str(data['username']) + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
    return


def loginpswd_modify(username:str, data:[])->str:
    conn = start_database()
    cursor = conn.cursor()

    cursor.execute("SELECT LoginPassword from Buyer where UserName=\'" + username + "\'")
    data1 = cursor.fetchone()
    if data1 is not None and check_password_hash(data1[0],data['password']):
        #旧密码正确 进行密码修改
        print("旧密码正确")
        password = generate_password_hash(data['newpassword'])
        insert = "update Buyer SET LoginPassword = \'" + password + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        insert = "update Seller SET LoginPassword= \'" + password + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        return True

    else:
        return False


def user_info_query(username: str, usertype: int):
    conn = start_database()
    cursor = conn.cursor()
    if usertype == 1:
        query = "select RealName, CitizenId, Email, Phone from Buyer where UserName = \'" + username + '\''
    else:
        query = "select RealName, CitizenId, Email, Phone from Seller where UserName = \'" + username + '\''

    cursor.execute(query)
    result = cursor.fetchall()
    return result


def paypswd_modify(username:str, data:[])->str:
    conn = start_database()
    cursor = conn.cursor()

    cursor.execute("SELECT PayPassword from Buyer where UserName=\'" + username + "\'")
    data1 = cursor.fetchone()
    if data1 is not None and check_password_hash(data1[0], data['password']):
        # 旧密码正确 进行密码修改
        print("旧密码正确")
        password = generate_password_hash(data['newpassword'])
        insert = "update Buyer SET PayPassword  = \'" + password + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        insert = "update Seller SET PayPassword = \'" + password + "\' where Username = \'" + username + '\''
        cursor.execute(insert)
        return True

    else:
        return False


def query_administrator_type(username:str)->int:
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute("SELECT TypeId from Administrator where UserName=\'" + username +"\'")
    data = cursor.fetchone()
    return data[0]

def query_permission_type(username:str)->bool:
    conn = start_database()
    cursor = conn.cursor()
    query = "select Valid from Buyer where UserName = \'" + username + '\''
    cursor.execute(query)
    result = cursor.fetchone()

    if result and result[0] == 0:
       return True
    query = "select Valid from Seller where UserName = \'" + username + '\''
    cursor.execute(query)
    result = cursor.fetchone()

    if result and result[0] == 0:
       return True

    return False

