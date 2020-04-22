from wtforms.fields import simple, core
from wtforms import Form, validators, widgets, ValidationError
from user_system.user_models import verify_user_register, recharge_valid
import calendar


class LoginForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    password = simple.PasswordField(
        label='Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput()
    )


class RechargeForm(Form):
    def validate_rechargement(self, field):
        if not recharge_valid(self.realname.data,self.citizenid.data):
            raise ValidationError(u'Card Number not match password or this card has been used')
    cardnumber = simple.StringField(
        label='Card number',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Card Number can not be empty")])
    password = simple.PasswordField(
        label='Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput()
    )


class RegistrationForm(Form):
    def validate_realname(self, field):
        if not verify_user_register(self.realname.data,self.citizenid.data):
            raise ValidationError(u'Real Name not match CitizenId')

    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    password = simple.PasswordField(
        label='Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    password2 = simple.PasswordField(
        label='Repeat Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty'),
                    validators.EqualTo('password',message='Two password not same')])
    paypassword = simple.PasswordField(
        label='PayPassword',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    paypassword2 = simple.PasswordField(
        label='Repeat PayPassword',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty'),
                    validators.EqualTo('paypassword',message='Two password not same')])
    realname = simple.StringField(
        label='Real name',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="RealName can not be empty")])
    citizenid = simple.StringField(
        label='Citizen ID',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Citizen ID can not be empty"),validate_realname])
    email = simple.StringField(
        label='Email',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message='Email can not be empty'),
                    validators.Email(message='Wrong Email Syntax')])
    phone = simple.StringField(
        label='Phone',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="phone can not be empty")])
    typeid = simple.BooleanField(
        label='IS Buyer',
        widget=widgets.CheckboxInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class BillForm(Form):
    MONTHS = [(str(0), 'ALL')]
    for i in range(1, 13):
        MONTHS.append((str(i), calendar.month_name[i]))
    year = core.IntegerField(
        label='Year',
        validators=[validators.NumberRange(min=1970, max=2019)])
    month = core.SelectField(choices=MONTHS)
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class loginpswdmodifyform(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput())
    password = simple.PasswordField(
        label='Old Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    password2 = simple.PasswordField(
        label='Repeat Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty'),
                    validators.EqualTo('password', message='Two password not same')])
    newpassword = simple.PasswordField(
        label='New Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    email = simple.StringField(
        label='Email',
        widget=widgets.TextInput())
    phone = simple.StringField(
        label='Phone',
        widget=widgets.TextInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class paypswdmodifyform(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput())
    password = simple.PasswordField(
        label='Old PayPassword',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    password2 = simple.PasswordField(
        label='Repeat the Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty'),
                    validators.EqualTo('password', message='Two password not same')])
    newpassword = simple.PasswordField(
        label='New PayPassword',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    email = simple.StringField(
        label='Email',
        widget=widgets.TextInput())
    phone = simple.StringField(
        label='Phone',
        widget=widgets.TextInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class ModifyForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput())
    email = simple.StringField(
        label='Email',
        widget=widgets.TextInput())
    phone = simple.StringField(
        label='Phone',
        widget=widgets.TextInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())

