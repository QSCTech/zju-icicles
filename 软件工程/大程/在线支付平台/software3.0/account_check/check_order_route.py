from __init__ import app
from flask_socketio import SocketIO
import json
async_mode = None
socketio = SocketIO(app)
from flask import render_template, request, url_for, redirect, session
from account_check.check_order  import *


@app.route('/check/index',methods=["POST","GET"])
def list0():
    return render_template('account_check/product.html')


@app.route('/check/error/show',methods=["POST","GET"])
def error_disp():
    global error_list
    return render_template('account_check/contact.html')



@app.route('/check/result',methods=["POST","GET"])
def search_result():
    global data
    global error_list
    if request.method == "POST":
        res = request.form.get('data1')
    return render_template('account_check/test.html', res=res)


@app.route('/check/index/test',methods=["POST","GET"])
def test():
    global error_list

    flag_c = '0'
    if request.method == "POST":
        flag_c = request.form.get('flag_cli')
        id_t = request.form.get('id')
        print(id_t)

    if(flag_c == '1'):
        for i in range(0, len(error_list)):
            if(id_t == error_list[i]['trade_id']):
                error_list[i]['flag'] = '已审核'
    return render_template('account_check/contact.html')


@socketio.on('connect', namespace='/test_conn')
def test_connect():

        T = TradeCompare()
        rec = T.compare()
        ans = json.dumps(rec)
        socketio.emit('server_response',
                      {'data': ans},
                      namespace='/test_conn')
        print(ans)
        return ans
