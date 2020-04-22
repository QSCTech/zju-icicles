from flask_wtf import Form
from wtforms import IntegerField, StringField, BooleanField, validators, SelectField, DateTimeField
from wtforms.validators import DataRequired


class ProductDetailForm(Form):
	amount = IntegerField('amount', default = 1, validators=[DataRequired()])


class QueryGoodsForm(Form):
	goodname = StringField('goodname', validators=[validators.DataRequired(message="Goodname can not be empty")])


class HotelFilter(Form):
    sort = SelectField(choices=[('none', '無'), ('company', '公司名称'), ('price', '价格(低至高)'), ('review', '评价(高至低)')])
    price = SelectField(choices=[('none', '無'),('low', '0-500'), ('mid', '500-1000'), ('high', '1000~')])


class SellerAdd(Form):
	goodname = StringField ('goodname', validators=[DataRequired()])
	price = IntegerField ('price', validators=[DataRequired()])
	hotel = BooleanField ('hotel', default = False)
	flight = BooleanField ('flight', default = False)
	RoomType = StringField ('RoomType', default = 'none')
	From = StringField ('From', default = 'none')
	Dest = StringField ('Dest', default = 'none')
	date = StringField ('date', validators=[DataRequired()])