from __init__ import app
from flask import render_template, request, url_for, redirect, session
from ticket_book.ticket_forms import *
from ticket_book.ticket_models import *


@app.route('/tourist_product_detail')
def tourist_product_detail():
    user = {'nickname': 'Miguel'}  # fake user
    return render_template('ticket_template/tourist_product_detail.html', title='Product detail', user=user)


@app.route('/tourist_hotel_detail/<int:id>', methods=['GET', 'POST'])
def tourist_hotel_detail(id):
    user = {'nickname': 'Miguel'}  # fake user
    hotel = select_good(id)
    if request.method == 'GET':
        form = ProductDetailForm()
        return render_template('ticket_template/tourist_hotel_detail.html', title='hotel detail', hotel=hotel, form=form)
    else:
        form = ProductDetailForm(formdata=request.form)
        amount = form.data['amount']
        if form.validate():
            # buyer_booking(buyerid:int, sellerid:int, goodid:int, amount:int, price:int):
            buyerid = buyer_id_query("liyuxuan")
            buyer_booking(buyerid, hotel[6], hotel[1], form.data['amount'])
    return render_template('ticket_template/tourist_hotel_detail.html', title='hotel detail', hotel=hotel, form=form)


@app.route('/tourist_plane_detail/<int:id>', methods=['GET', 'POST'])
def tourist_plane_detail(id):
    user = {'nickname': 'Miguel'}  # fake user
    plane = select_good(id)
    if request.method == 'GET':
        form = ProductDetailForm()
        return render_template('ticket_template/tourist_plane_detail.html', title='Plane detail', plane=plane, form=form)
    else:
        form = ProductDetailForm(formdata=request.form)
        amount = form.data['amount']
        if form.validate():
            buyerid = buyer_id_query(session['username'])
            buyer_booking(buyerid, plane[6], plane[1], form.data['amount'])
    return render_template('ticket_template/tourist_plane_detail.html', title='Plane detail', plane=plane, form=form)


@app.route('/buyer_hotel_detail/<int:id>', methods=['GET', 'POST'])
def buyer_hotel_detail(id):
    hotel = select_good(id)
    if request.method == 'GET':
        form = ProductDetailForm()
        return render_template('ticket_template/buyer_hotel_detail.html', title='hotel detail', hotel=hotel, form=form)
    else:
        form = ProductDetailForm(formdata=request.form)
        amount = form.data['amount']
        if form.validate():
            # buyer_booking(buyerid:int, sellerid:int, goodid:int, amount:int, price:int):
            buyerid = buyer_id_query(session['username'])
            buyer_booking(buyerid, hotel[6], hotel[0], amount, amount * hotel[5])
    return render_template('ticket_template/buyer_hotel_detail.html', title='hotel detail', hotel=hotel, form=form)


@app.route('/buyer_plane_detail/<int:id>', methods=['GET', 'POST'])
def buyer_plane_detail(id):
    user = {'nickname': 'Miguel'}  # fake user
    plane = select_good(id)
    if request.method == 'GET':
        form = ProductDetailForm()
        return render_template('ticket_template/buyer_plane_detail.html', title='Plane detail', plane=plane, form=form)
    else:
        form = ProductDetailForm(formdata=request.form)
        amount = form.data['amount']
        if form.validate():
            print(session["username"])
            buyerid = buyer_id_query(session['username'])
            print(buyerid)
            buyer_booking(buyerid, plane[6], plane[0], amount, amount * plane[5])
    return render_template('ticket_template/buyer_plane_detail.html', title='Plane detail', plane=plane, form=form)


@app.route('/admin_comment_review')
def admin_comment_review():
    user = {'nickname': 'Miguel'}  # fake user
    return render_template('ticket_template/admin_comment_review.html', title='Product detail', user=user)


# @app.route('/admin_verification')
# def admin_verification():
#    user = { 'nickname': 'Miguel' } # fake user
#    return render_template('admin_verification.html',title = 'Product detail',user = user)
@app.route('/admin_verification', methods=['POST', 'GET'])
def admin_verification():
    if request.method == 'GET':
        if select_all() == 1:
            return render_template('ticket_template/admin_verification.html', title='Product detail')
        else:
            goods = select_all()
            return render_template('ticket_template/admin_verification.html', title='Product detail', goods=goods)
    # elif request.method == 'POST':
    #     good_id = request.form['goodid']
    #     is_pass(good_id)
    #     return json.dumps({'ok': 1})


@app.route('/admin_verification/<int:id>', methods=['POST', 'GET'])
def admin_verification_pass(id):
    if request.method == 'GET':
        is_pass(id)
        return redirect(url_for("admin_verification"))

    else:
        return redirect(url_for("admin_verification"))


@app.route('/buyer_comment')
def buyer_comment():
    user = {'nickname': 'Miguel'}  # fake user
    return render_template('ticket_template/buyer_comment.html', title='Product detail', user=user)


@app.route('/buyer_index', methods=['POST', 'GET'])
def buyer_index():
    if 'username' in session:
        Hform = HotelFilter()
        if request.method == 'GET':
            form = QueryGoodsForm()
            hotels = show_good()
            planes = show_good(good_type='plane')
            return render_template('ticket_template/buyer_index.html', title='Home', form=form, Hform=Hform, hotels=hotels,
                                   planes=planes)
        else:
            form = QueryGoodsForm(formdata=request.form)
            if form.validate():
                goodname = form.data['goodname']
                query = good_info_query(goodname)
            return render_template('ticket_template/buyer_index.html', title='Home', form=form, Hform=Hform, query=query)
    else:
        return redirect(url_for("buyer_index"))


@app.route('/seller_add', methods=['GET', 'POST'])
def seller_add():
    user = {'nickname': 'Miguel'}  # fake user
    if request.method == 'GET':
        form = SellerAdd()
        return render_template('ticket_template/seller_add.html', title='seller add', form=form, user=user)
    else:
        form = SellerAdd(formdata=request.form)
        goodname = form.data['goodname']
        price = form.data['price']
        hotel = form.data['hotel']
        flight = form.data['flight']
        RoomType = form.data['RoomType']
        From = form.data['From']
        Dest = form.data['Dest']
        date = form.data['date']
        sellerid = seller_id_query(session['username'])
        if (hotel == True and RoomType != 'none'):
            seller_add_good(goodname, price, RoomType, "", date,sellerid)
            return redirect('/seller_listofgoods')
        elif (flight == True and From != 'none' and Dest != 'none'):
            seller_add_good(goodname, price, From, Dest, date,sellerid)
            return redirect('/seller_listofgoods')
        else:
            return render_template('ticket_template/seller_add.html', title='seller add', form=form, user=user)
    return render_template('ticket_template/seller_add.html', title='seller add', form=form, user=user)


@app.route('/seller_edit', methods=['GET', 'POST'])
def seller_edit():
    user = {'nickname': 'Miguel'}  # fake user
    return render_template('ticket_template/seller_edit.html', title='Product detail', user=user)


@app.route('/seller_edit/<int:id>', methods=['POST', 'GET'])
def seller_edit_good(id):
    user = {'nickname': 'Miguel'}  # fake user
    good = select_good(id)
    print(good)
    if request.method == 'GET':
        form = SellerAdd()
        return render_template('ticket_template/seller_edit.html', title='seller edit', good=good, form=form)
    else:
        form = SellerAdd(formdata=request.form)
        goodname = form.data['goodname']
        price = form.data['price']
        hotel = form.data['hotel']
        flight = form.data['flight']
        RoomType = form.data['RoomType']
        From = form.data['From']
        Dest = form.data['Dest']
        date = form.data['date']
        if (hotel == True and RoomType != 'none'):
            seller_edit_model(id, goodname, price, RoomType, "", date)
            return redirect('/seller_listofgoods')
        elif (flight == True and From != 'none' and Dest != 'none'):
            seller_edit_model(id, goodname, price, From, Dest, date)
            return redirect('/seller_listofgoods')
        else:
            return render_template('ticket_template/seller_add.html', title='seller edit', form=form, user=user)
    return render_template('ticket_template/seller_add.html', title='seller edit', form=form, user=user)


@app.route('/seller_listofgoods', methods=['GET', 'POST'])
def seller_listofgoods():
    user = {'nickname': 'Miguel'}  # fake user
    if request.method == 'GET':
        seller_id = seller_id_query(session['username'])
        seelist = seller_seelist(seller_id)
        return render_template('ticket_template/seller_listofgoods.html', title='Product detail', user=user, seelist=seelist)
    else:
        seller_id = seller_id_query(session['username'])
        seelist = seller_seelist(seller_id)
        return render_template('ticket_template/seller_listofgoods.html', title='Product detail', user=user, seelist=seelist)
    return render_template('ticket_template/seller_listofgoods.html', title='Product detail', user=user, seelist=seelist)


@app.route('/seller_response')
def seller_response():
    user = {'nickname': 'Miguel'}  # fake user
    return render_template('ticket_template/seller_response.html', title='Product detail', user=user)
