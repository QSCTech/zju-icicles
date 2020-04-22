from config import start_database
import time
from datetime import timedelta, datetime

class TradeCompare():
    def __init__(self):
        # Database connection
        conn = start_database()
        cur = conn.cursor()

        try:
            # Get sell_trades information
            sql = "select * from SellerOrder"
            cur.execute(sql)
            self.seller_trades = cur.fetchall()

            # Get buyer_trades information
            sql = "select * from BuyerOrder"
            cur.execute(sql)
            self.buyer_trades = cur.fetchall()

            # close DB cursor
            conn.close()

        except:
            print("Error: Unable to fetch data")

    def compare(self):
        seller_OrderNo = []
        for seller_item in self.seller_trades:
            seller_OrderNo.append(seller_item[0])

        buyer_OrderNo = []
        flag = []
        for buyer_item in self.buyer_trades:
            buyer_OrderNo.append(buyer_item[0])
            # Add lable 'unvisited' for comparison
            flag.append(0)

        self.records = []

        date = datetime.today() + timedelta(-1)
        date = date.strftime("%Y-%M-%D %H:%M")
        self.records.append(str(date))
        for i in range(0, len(seller_OrderNo)):
            try:
                index = buyer_OrderNo.index(seller_OrderNo[i])
                seller_item = self.seller_trades[i]
                buyer_item = self.buyer_trades[index]

                error = {
                    'OrderNo': seller_OrderNo[i],
                    'sellerInfo': seller_item[2],
                    'buyerInfo': buyer_item[2]
                }
                if (seller_item[1] != buyer_item[1]):
                    error['error'] = 'Error: SellerID comflicts in two sides'
                    self.records.append(error)
                elif (seller_item[2] != buyer_item[2]):
                    error['error'] = 'Error: BuyerID comflicts in two sides'
                    self.records.append(error)
                elif (seller_item[3] != buyer_item[3]):
                    error['error'] = 'Error: Good id comflicts in two sides'
                    self.records.append(error)
                elif (seller_item[11] != buyer_item[11]):
                    error['error'] = 'Error: Amount comflicts'
                    self.records.append(error)
                elif (seller_item[5] != buyer_item[5]):
                    error['error'] = 'Error: State comflicts in two sides'
                    self.records.append(error)
                elif (seller_item[4] != buyer_item[4]):
                    error['error'] = 'Error: Good Discrption comflicts in two sides'
                    self.records.append(error)
                elif (seller_item[4] != buyer_item[4]):
                    error['error'] = 'Error: Good Discrption comflicts in two sides'
                    self.records.append(error)

                flag[index] = 1

            except:
                error = {
                    'OrderNo': seller_OrderNo[i],
                    'error': 'Error: Trade exists in seller_trades but not in buyer_trades',
                    'sellerInfo': seller_item[2],
                    'buyerInfo': 'NULL'
                }
                self.records.append(error)

        for i in range(len(buyer_OrderNo)):
            if flag[i] == 0:
                error = {
                    'OrderNo': buyer_OrderNo[i],
                    'error': 'Error: Trade exists in buyer_trades but not in seller_trades',
                    'sellerInfo': 'NULL',
                    'buyerInfo': self.buyer_trades[i][2]
                }
                self.records.append(error)
        self.update()
        return self.records


    def update(self):
        conn = start_database()
        cur = conn.cursor()

        flag = 0

        for item in self.records:
                if flag == 0:
                    flag = 1
                    continue
                ts = time.time()
                canceltime = datetime.fromtimestamp(ts).strftime('%Y%m%d%H%M%S')
                sql_seller = 'UPDATE SellerOrder SET CancelTime = ' + \
                    canceltime+' WHERE OrderNo = '+str(item['OrderNo'])
                cur.execute(sql_seller)
                sql_buyer = 'UPDATE BuyerOrder SET CancelTime = ' + \
                    canceltime+' WHERE OrderNo = '+str(item['OrderNo'])
                cur.execute(sql_buyer)

        conn.commit()
        conn.close()