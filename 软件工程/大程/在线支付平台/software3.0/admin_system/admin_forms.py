from wtforms.fields import simple, core
from wtforms import Form, validators, widgets, ValidationError


class AddBlacklistsForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    typeid = simple.BooleanField(
        label='IS Buyer',
        widget=widgets.CheckboxInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class DeleteBlacklistsForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    typeid = simple.BooleanField(
        label='IS Buyer',
        widget=widgets.CheckboxInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class AddManagerForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    password = simple.PasswordField(
        label='Password',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    AuthenticationPassword = simple.PasswordField(
        label='AuthenticationPassword',
        widget=widgets.PasswordInput(),
        validators=[validators.DataRequired(message='Password can not be empty')])
    checker = simple.BooleanField(
        label='Create checker',
        widget=widgets.CheckboxInput())
    admin = simple.BooleanField(
        label='Create admin',
        widget=widgets.CheckboxInput())
    Super_admin = simple.BooleanField(
        label='Create super admin',
        widget=widgets.CheckboxInput())
    ticketchecker = simple.BooleanField(
        label='Create ticket checker',
        widget=widgets.CheckboxInput())
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class DeleteManagerForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])


class MaintainUserForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput())
    type = core.SelectField(
        label="UserType",
        choices=[
            (1, "Seller"),
            (2, "Buyer-Ordinary"),
            (3, "Buyer-VIP"),
        ],
        coerce=int
    )
    submit = simple.SubmitField(
        label='Submit',
        widget=widgets.SubmitInput())


class MaintainManagerForm(Form):
    username = simple.StringField(
        label='Username',
        widget=widgets.TextInput(),
        validators=[validators.DataRequired(message="Username can not be empty")])
    deleteright = simple.BooleanField(
        label='DeleteRight',
        widget=widgets.CheckboxInput())
    addright = simple.BooleanField(
        label='AddRight',
        widget=widgets.CheckboxInput())
    arbitrationright = simple.BooleanField(
        label='ArbitrationRight',
        widget=widgets.CheckboxInput())
    blacklistright = simple.BooleanField(
        label='BlackListRight',
        widget=widgets.CheckboxInput())
    viewright = simple.BooleanField(
        label='ViewRight',
        widget=widgets.CheckboxInput())
