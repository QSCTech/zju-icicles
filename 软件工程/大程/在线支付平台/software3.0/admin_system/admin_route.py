from __init__ import app
from admin_system.admin_models import *
from admin_system.admin_forms import *
from user_system.user_models import search_by_name, search_by_type
from user_system.user_models import username_valid_register,manager_register
from flask import render_template, request, url_for, redirect, session


@app.route('/maintain/user', methods=['POST', 'GET'])
def maintain_user():
    if request.method == 'GET':
        form = MaintainUserForm()
        return render_template('admin_template/search_users.html', form=form)
    else:
        form = MaintainUserForm(formdata=request.form)
        if form.validate():
            if form.data['username']:
                users = search_by_name(form.data['username'])
            else:
                users = search_by_type(form.data['type'])
        else:
            pass
    return render_template('admin_template/search_users.html', form=form, users=users)


@app.route('/delete/manager', methods=['POST', 'GET'])
def delete_manager():
    if 'username' in session and session['username'] == 'software':
        if request.method == "GET":
            form = DeleteManagerForm()
            return render_template("admin_template/delete-manager.html", form=form)
        else:
            form = DeleteManagerForm(formdata=request.form)
            if form.validate():
                username = form.data['username']
                if request.form['key'] == "query":
                    query = manager_query(username)
                    return render_template('admin_template/delete-manager.html', form=form, query=query)
                if request.form['key'] == "submit":
                    message = manager_delete(username)
                    return render_template('admin_template/delete-manager.html', form=form, message=message)
    else:
        return redirect(url_for("index"))


@app.route('/maintain/manager', methods=['POST', 'GET'])
def maintain_manager():
    if 'username' in session and session['username'] == 'software':
        if request.method == "GET":
            form = MaintainManagerForm()
            return render_template("admin_template/maintain-manager.html", form=form)
        else:
            form = MaintainManagerForm(formdata=request.form)
            if form.validate():
                username = form.data['username']
                if request.form['key'] == "query":
                    query = manager_query(username)
                    return render_template('admin_template/maintain-manager.html', form=form, query=query)
                if request.form['key'] == "submit":
                    permission = 0
                    if form.data['deleteright']:
                        permission += 16
                    if form.data['addright']:
                        permission += 8
                    if form.data['arbitrationright']:
                        permission += 4
                    if form.data['blacklistright']:
                        permission += 2
                    if form.data['viewright']:
                        permission += 1
                    message = manager_maintain(username, permission)
                    return render_template('admin_template/maintain-manager.html', form=form, message=message)
    else:
        return redirect(url_for("index"))


@app.route('/add/manager',methods = ['POST', 'GET'])
def add_manager():
    if 'username' in session and session['username'] == 'software' or 'type' in session and session['type'] == 2:
        if request.method == "GET":
            form = AddManagerForm()
            return render_template("admin_template/add-manager.html", form=form)
        else:
            form = AddManagerForm(formdata=request.form)
            if form.validate():
                data = form.data
                if data['checker']:
                    typeid = 3
                    permission = 0
                elif data['Super_admin']:
                    typeid = 2
                    permission = 31
                elif data['ticketchecker']:
                    typeid = 4
                    permission = 31
                else:
                    typeid = 1
                    permission = 0
                if username_valid_register(data['username']):
                    manager_register(data['username'], data['password'], data['AuthenticationPassword'], typeid, permission)
                    return redirect(url_for('add_manager'))
            return redirect(url_for('add_manager'))
    return redirect(url_for('index'))


@app.route('/manager/blacklists', methods=['POST','GET'])  #黑名单显示界面 blacklists.html界面展示
def blacklists():
    list = []
    conn = start_database()
    cursor = conn.cursor()
    sql = "SELECT * FROM Buyer where Valid = " + "1"
    cursor.execute(sql)
    list.append(cursor.fetchall())
    sql = "SELECT * FROM Seller where Valid = " + "1"
    cursor.execute(sql)
    list.append(cursor.fetchall())
    return render_template('admin_template/blacklists.html', users = list)  #u为传递信息


@app.route('/manager/addblacklists', methods=['POST','GET'])  #黑名单显示界面 blacklists.html界面展示
def addblacklists():
    if request.method == "GET":
        form = AddBlacklistsForm()
        return render_template("admin_template/add_blacklists.html", form=form)
    else:
        form = AddBlacklistsForm(formdata=request.form)
        if form.validate():
            data=form.data
            add_blacklists(data)
            return redirect(url_for('blacklists'))
    return render_template('add_blacklists.html.html')


@app.route('/manager/deleteblacklists', methods=['POST','GET'])  #黑名单显示界面 blacklists.html界面展示
def deleteblacklists():
        if request.method == "GET":
            form = DeleteBlacklistsForm()
            return render_template("admin_template/delete_blacklists.html", form=form)
        else:
            form = DeleteBlacklistsForm(formdata=request.form)
            if form.validate():
                data = form.data
                delete_blacklists(data)
                return redirect(url_for('blacklists'))
        return render_template('admin_template/delete_blacklists.html')