create table employee (
    ID int, 
    person_name varchar(50),
    street varchar(50),
    city varchar(50)
	primary key ID);
create table works (
    ID int, 
    company_name varchar(50),
    salary int
    FOREIGN KEY (ID)
    REFERENCES employee (ID),
    FOREIGN KEY (company_name)
    REFERENCES company (company_name));
create table company (
    company_name varchar(50),
    city varchar(50)
    primary key (company_name));
create table manages (
    ID int, 
    manager_id int,
    FOREIGN KEY (ID)
    REFERENCES employee (ID));
CREATE TRIGGER trig1 AFTER INSERT
    ON works FOR EACH ROW
    INSERT INTO  employee (`ID`, `person_name`, `street`, `city`) VALUES ('3', 'en','eww', 'wecity');
INSERT INTO  works (`ID`, `company_name`,`salary` ) VALUES ('1', 'cw', 3);

INSERT INTO `db_3180103721`.`employee` (`ID`, `person_name`, `street`, `city`) VALUES ('1', 'we', 'wewe', 'wecity');
INSERT INTO `db_3180103721`.`employee` (`ID`, `person_name`) VALUES ('1', 'en', 'wed', 'weds');
INSERT INTO manages (`ID`, ` manager_id `) VALUES ('1', '23');
DELETE FROM employee WHERE id=1;
Select
TABLE_NAME,COLUMN_NAME,CONSTRAINT_NAME, REFERENCED_TABLE_NAME,REFERENCED_COLUMN_NAME
     from INFORMATION_SCHEMA.KEY_COLUMN_USAGE
     where REFERENCED_TABLE_NAME ='employee';
alter table manages drop foreign key  ` manages_ibfk_1 `;
ALTER TABLE manages
    ADD CONSTRAINT fkt1
    FOREIGN KEY(id)
REFERENCES  employee (id) 
on update cascade on delete cascade;
INSERT INTO manages (`ID`, ` manager_id `) VALUES ('1', '23');
UPDATE employee  SET id=2 WHERE id=1;
INSERT INTO works (`ID`, `company_name`, `salary`) VALUES ('1', 'comp1', '-2');