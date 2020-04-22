from config import start_database
import time
import datetime


def good_info_query(goodname: str) -> []:
    conn = start_database()
    cursor = conn.cursor()
    insert = "select * from Good where GoodName LIKE \'" + goodname + "%\';"
    cursor.execute(insert)
    data = cursor.fetchall()
    if data:
        return data


def buyer_booking(buyerid: int, sellerid: int, goodid: int, amount: int, price: int):
    ts = time.time()
    timestamp = datetime.datetime.fromtimestamp(ts).strftime('%Y%m%d%H%M%S')
    # timestamp = Date + Time
    conn = start_database()
    cursor = conn.cursor()
    # cursor = start_database()
    insert = """
INSERT INTO
  `Order` (
    `BuyerId`,
    `SellerId`,
    `GoodId`,
    `Numbers`,
    `OrderState`,
    `OrderTime`,
    `Amount`
  )
VALUES
  (
    %d,
    %d,
    %d,
    %d,
    %d,
    NOW(),
    %d
  );
    """ % (buyerid, sellerid, goodid, amount, 0, price)
    print(insert)
    cursor.execute(insert)
    # cursor.execute("INSERT into Order values ( ,"+buyerid+","+sellerid+","+goodname+",0,"+timestamp+", NULL, NULL, NULL, NULL,"+amount+")")
    data = cursor.fetchone()


def seller_add_good(goodname: str, price: int, From: str, Dest: str, Date: str, sellerid: int):
    conn = start_database()
    cursor = conn.cursor()
    insert = "insert into `Good` values( NULL, \'" \
             + goodname + "\',\'" + From + "\',\'" + Dest + "\',\'" + Date + "\'," + str(price) + "," + str(
        sellerid) + ", 0);"
    cursor.execute(insert)
    data = cursor.fetchone()


def seller_edit_model(goodid: int, goodname: str, price: int, From: str, Dest: str, Date: str):
    conn = start_database()
    cursor = conn.cursor()
    insert = "UPDATE `Good` set `GoodName` = \'" + goodname + "\', `From`=\'" \
             + From + "\', `Dest`=\'" + Dest + "\', `Date`=\'" + Date + "\', `Price`=" + str(
        price) + " where `GoodId`=" + str(goodid) + ";"
    print(insert)
    cursor.execute(insert)
    data = cursor.fetchone()


def show_good(good_type='hotel', start_limit=0, end_limit=100):
    conn = start_database()
    cursor = conn.cursor()
    if good_type == 'hotel':
        cursor.execute(f"SELECT * FROM Good WHERE Dest = '' and IsReview=1 LIMIT {start_limit},{end_limit};")
    else:
        cursor.execute(f"SELECT * FROM Good WHERE Dest <> '' and IsReview=1 LIMIT {start_limit},{end_limit}")
    data = cursor.fetchall()
    if data:
        return data
    else:
        return []


def show_all_good(good_type='hotel', start_limit=0, end_limit=1000):
    conn = start_database()
    cursor = conn.cursor()
    if good_type == 'hotel':
        cursor.execute(f"SELECT * FROM Good WHERE Dest is NULL and IsReview=1 LIMIT {start_limit},{end_limit};")
    else:
        cursor.execute(f"SELECT * FROM Good WHERE Dest is not NULL and IsReview=1 LIMIT {start_limit},{end_limit}")
    data = cursor.fetchall()
    if data:
        return data
    else:
        return []


def select_good(good_id):
    conn = start_database()
    cursor = conn.cursor()
    insert = f"SELECT * FROM Good WHERE GoodID={good_id}"
    print(insert)
    cursor.execute(insert)
    data = cursor.fetchall()
    if data:
        return data[0]


# def filter_hotel_company():
# def filter_hotel_price():
# def filter_hotel_price_range():

def select_all():
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute(f"SELECT * FROM Good WHERE IsReview=0")
    data = cursor.fetchall()
    if data:
        return data
    else:
        return 1


def is_pass(good_id):
    conn = start_database()
    cursor = conn.cursor()
    cursor.execute(f'UPDATE Good SET IsReview=1 WHERE GoodID={good_id}')
    conn.commit()


def seller_seelist(sellerid: int):
    conn = start_database()
    cursor = conn.cursor()
    insert = "select * from `Good` where SellerId = " + str(sellerid) + ";"
    print(insert)
    cursor.execute(insert)
    data = cursor.fetchall()
    if data:
        return data


def buyer_id_query(username: str):
    conn = start_database()
    cursor = conn.cursor()
    insert = "select BuyerId from Buyer where UserName = \'" + username + "\';"
    cursor.execute(insert)
    return cursor.fetchone()[0]


def seller_id_query(username: str):
    conn = start_database()
    cursor = conn.cursor()
    insert = "select SellerId from Seller where UserName = \'" + username + "\';"
    cursor.execute(insert)
    return cursor.fetchone()[0]
