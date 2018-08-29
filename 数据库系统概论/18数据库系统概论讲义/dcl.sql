use 学生
GRANT ALL ON Course(cno) TO yjp1 
revoke update on course(cno) from yjp1
grant all on course to yjp1 with grant option
revoke grant option for update on course from yjp1 cascade
revoke grant option for all on course from yjp1 cascade

grant alter table to yjp1

grant all on course to public    
revoke all on course from yjp1
revoke all on course from public
grant all on course to public
deny all on course to yjp1


grant create table to yjp1

create table scc(             /*以yjp1执行*/
sno int,
cno char(4) foreign key references course(cno)
)              
grant references on course to yjp1
revoke references on course from yjp1


EXEC sp_addlogin 'yjp3', '123', 'five' 
EXEC sp_droplogin 'yjp3'
exec sp_grantlogin 'IBMYJP\jpyang'
exec sp_revokelogin 'ibmyjp\jpyang'

exec sp_grantdbaccess 'yjp3', 'yjp3'
exec sp_revokedbaccess 'yjp3'
exec sp_adduser test,test

Exec  sp_addrole yjp4
Exec sp_droprole yjp4
exec sp_addrolemember 'db_owner','yjp3'
Exec sp_droprolemember 'db_owner','yjp3'

exec sp_addsrvrolemember 'yjp3','sysadmin'
exec sp_addsrvrolemember 'ibmyjp\jpyang','sysadmin'
exec sp_dropsrvrolemember 'ibmyjp\jpyang','sysadmin'

