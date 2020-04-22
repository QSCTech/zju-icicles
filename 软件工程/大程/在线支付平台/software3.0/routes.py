from __init__ import app
from flask import render_template, request, url_for, redirect, session
from user_system.user_forms import LoginForm
from user_system.user_models import buyer_valid_login,seller_valid_login,administrator_valid_login


from user_system.user_route import *
from admin_system.admin_route import *
from account_check.check_order_route import *
from ticket_book.ticket_route import *


@app.route('/', methods=['POST','GET'])
@app.route('/index', methods=['POST','GET'])
def index():
    if request.method == "GET":
        loginform = LoginForm()
        querygood = QueryGoodsForm()
        hotels = show_good()
        planes = show_good(good_type='plane')
        return render_template("ticket_template/tourist_index.html",logform=loginform, goodform=querygood,hotels=hotels,planes=planes)
    else:
        if request.form['key'] == "login":
            loginform = LoginForm(formdata=request.form)
            if loginform.validate():
                username = loginform.data['username']
                password = loginform.data['password']
                session['username'] = username
                if buyer_valid_login(username, password) and query_permission_type(username):
                    session['type'] = 1
                    print("success")
                    return redirect(url_for("buyer_index"))
                if seller_valid_login(username, password) and query_permission_type(username):
                    session['type'] = 0
                    return redirect(url_for('seller_listofgoods'))
                if username == "software" or administrator_valid_login(username, password):
                    if username == "software" or query_administrator_type(username) == 2:
                        session['type'] = 2
                        return redirect(url_for('add_manager'))
                    elif query_administrator_type(username) == 3:
                        session['type'] = 3
                        return redirect(url_for("list0"))
                    elif query_administrator_type(username) == 4:
                        session['type'] = 4
                        return redirect(url_for("admin_verification"))
        elif request.form['key'] == 'query':
            querygoodform = QueryGoodsForm(form=request.form)
            loginform = LoginForm()
            if querygoodform.validate():
                goodname = querygoodform.data['goodname']
                query = good_info_query(goodname)
            return render_template('ticket_template/tourist_index.html', title='Home', logform=loginform, goodform=querygoodform,query=query)
        return redirect(url_for("index"))


@app.route('/logout',methods=['POST', "GET"])
def logout():
    session.pop('username', None)
    session.pop('type', None)
    return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()


