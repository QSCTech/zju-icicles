from __init__ import app
from user_system.user_models import *
from user_system.user_forms import *
from flask import render_template, request, url_for, redirect, session


@app.route('/account', methods=['POST', 'GET'])
def account():
    if 'username' in session:
        messages = user_info_query(session['username'], session['type'])
        if session['type'] == 1:
            usertype = "buyer"
        else:
            usertype = "seller"

        if request.method == 'GET':
            form_recharge = RechargeForm()
            value = return_balance(session['username'], session['type'])
            return render_template('user_template/recharge.html', form_recharge=form_recharge, value=value,
                                   username=session['username'], messages=messages, usertype=usertype)
        else:
            form_recharge = RechargeForm(formdata=request.form)
            value = return_balance(session['username'], session['type'])
            if form_recharge.validate():
                revalue = recharge_valid(form_recharge.data['cardnumber'], form_recharge.data['password'])
                if revalue:
                    recharge_value(session['username'], revalue)
                    return redirect(url_for('account'))
                else:
                        return redirect(url_for('account'))
            else:
                print(form_recharge.errors, "错误信息")
        return render_template('user_template/recharge.html', form_recharge=form_recharge, value=value,
                               username=session['username'], messages=messages, usertape=usertype)
    return redirect(url_for("index"))


@app.route('/register', methods=['POST', 'GET'])
def register():
    if request.method == 'GET':
        form_register = RegistrationForm()
        return render_template('user_template/register.html', form_register=form_register)
    else:
        form_register = RegistrationForm(formdata=request.form)
        if form_register.validate():
            if form_register.data['typeid'] == 1:
                if username_valid_register(form_register.data['username']):
                    buyer_register(form_register.data)
                    return redirect(url_for('index'))
            else:
                if username_valid_register(form_register.data['username']):
                    seller_register(form_register.data)
                    return redirect(url_for('index'))
    return render_template('user_template/register.html', form_register=form_register)


@app.route('/bill', methods=['POST', 'GET'])
def bill():
    if request.method == 'GET':
        form = BillForm()
        return render_template('user_template/bill.html', form=form, flag=0)
    else:
        form = BillForm(formdata=request.form)
        if form.validate():
            print(form.data)
            year = form.data['year']
            month = form.data['month']
            print(year)
            print(month)
            # username = session['username']
            username = "Zhang"
            data = search_bill(year, month, username)
            return render_template("user_template/bill.html", form=form, flag=1, bills=data)
        else:
            print(form.errors)
            return render_template("user_template/bill.html", form=form, flag=0)


@app.route('/info/for/login/pswd', methods=['POST','GET'])
def loginpswdmodify():
    if request.method == "GET":
        print("get")
        form = loginpswdmodifyform()
        return render_template("user_template/loginpwdmodify.html", form=form)
    else:
        form =  loginpswdmodifyform(formdata=request.form)
        if form.validate():
            print("loginpswd")
            if loginpswd_modify(session['username'], form.data):
                print("success!")
                return redirect(url_for('account'))
            else:
                print("wrongpassword")

        else:
            print("错误")
            print(form.errors, "错误信息")
        return render_template("user_template/loginpwdmodify.html", form=form)


@app.route('/info/forpaypswd', methods=['POST','GET'])
def paypswdmodify():
    if request.method == "GET":
        print("get")
        form = paypswdmodifyform()
        return render_template("user_template/paypwdmodify.html", form=form)
    else:
        form = paypswdmodifyform(formdata=request.form)
        if form.validate():
            print("success")
            print(form.data)
            print(session['username'])
            if paypswd_modify(session['username'], form.data):
                print("success!")
                return redirect(url_for('account'))
            else:
                print("wrongpassword")
        else:
            print(form.errors, "错误信息")
        return render_template("user_template/paypwdmodify.html", form=form)


@app.route('/info/modify', methods=['POST','GET'])
def infomodify():
    if request.method == "GET":
        form = ModifyForm()
        return render_template("user_template/infomodify.html", form=form)
    else:
        form = ModifyForm(formdata=request.form)
        if form.validate():
            print("success")
            print(form.data)
            print(session['username'])
            info_modify(session['username'], form.data)
            if form.data['username']:
                session['username'] = form.data['username']
                print("changed")
            print("notchanged")
            return redirect(url_for('account'))
        else:
            print(form.errors, "错误信息")
        return render_template("user_template/infomodify.html", form=form)