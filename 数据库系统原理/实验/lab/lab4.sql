show grants;
Create user 'test'@'localhost' identified by '123';
./mysql -u test -p  

grant select on testDB.* to test@localhost;
revoke all on testDB.* from test@localhost;

use miaosha;
select * from user_info;

Create VIEW view 
as
select name,gender,age
from user_info;

grant select on view to test@localhost;