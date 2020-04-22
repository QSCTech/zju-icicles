from flask import Flask
app = Flask(__name__)
app.secret_key = 'fbaubfaibiuab21312/f'

app.config['MYSQL_DATABASE_USER'] = 'lcx'
app.config['MYSQL_DATABASE_PASSWORD'] = 'test'
app.config['MYSQL_DATABASE_DB'] = 'OnlinePayment'
app.config['MYSQL_DATABASE_HOST'] = '10.76.8.183'
