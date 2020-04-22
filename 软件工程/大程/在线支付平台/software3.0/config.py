from flaskext.mysql import MySQL
from __init__ import app




def start_database():
    db = MySQL()
    db.init_app(app)
    conn = db.connect()
    conn.autocommit(1)
    return conn