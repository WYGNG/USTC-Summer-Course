USE master
GO
drop database 学生选课库

USE [yjp]
GO

/****** Object:  Table [dbo].[课程]    Script Date: 2015-10-26 15:01:30 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO
primary
CREATE TABLE [dbo].[课程](
	[课程号] [char](5) NOT NULL,
	[课程名] [char](20) NULL,
	[先行课] [char](5) NULL,
	[学时] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[课程号] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO




CREATE DATABASE 学生选课库
ON PRIMARY
  ( NAME='学生选课主文件',
   FILENAME=
      'd:\选课主文件.mdf',
   SIZE=10,
   MAXSIZE=100,
   FILEGROWTH=10MB),
FILEGROUP 学生选课次文件组
  ( NAME = '学生选课次文件1',
   FILENAME =
      'd:\学生选课次文件1.ndf',
   SIZE = 1MB,
   MAXSIZE=10,
   FILEGROWTH=10%),
  ( NAME = '学生选课次文件2',
   FILENAME =
      'd:\学生选课次文件2.ndf',
   SIZE = 1MB,
   MAXSIZE=10,
   FILEGROWTH=1)
LOG ON
  ( NAME='学生选课库日志',
   FILENAME =
      'd:\学生选课日志.ldf',
   SIZE=1,
   MAXSIZE=10,
   FILEGROWTH=1)
GO

ALTER DATABASE 学生选课库
MODIFY FILEGROUP [学生选课次文件组] DEFAULT
GO
ALTER DATABASE 学生选课库
MODIFY FILEGROUP [primary] DEFAULT
GO


USE 学生选课库

drop database 学生选课库


CREATE TABLE 选课
  ( id  int   PRIMARY KEY,
   学号      char(10),
   课程号   char(8),
   成绩     smallint
 ) ON 学生选课次文件组
GO
 
create table 部门(
  代码 smallint identity(1,1) primary key clustered,
  名称 varchar(50) not null,
  负责人 char(8)

)

create table 职工(
 代码 smallint Primary key clustered,
 姓名 char(8),
 基本工资 smallmoney,
 附加工资 smallmoney,
 实发工资 as 基本工资+附加工资,
 部门代码 smallint references 部门(代码),
 性别 char(2) default '男' check(性别 in ('男','女'))
 )

alter table 选课
    alter column 成绩 smallint not null;

alter table 选课
    add  constraint 成绩约束  check(成绩 between 0 and 100);

alter  table 选课  add  性别 char(2) default '男' ,check(性别 in ('男','女'))

create table 学生(
    学号 int identity(1,1) primary key,
	性别 char(2) check(性别 in('男','女')),
	年龄 int

)
alter table 学生 add constraint 默认性别 default 20 for 性别


alter table 选课 nocheck constraint CK__选课__性别__1920BF5C;


alter table 选课 drop constraint CK__选课__性别__1920BF5C;
alter table 选课 drop constraint DF__选课__性别__182C9B23

alter table 选课  drop column 性别;

create unique index 职工号 on 职工(代码)

drop index 职工.职工号

create unique index 职工号 on 职工(代码 asc) with pad_index ,fillfactor=10,
   ignore_dup_key,statistics_norecompute on 学生选课次文件组;

IGNORE_DUP_KEY

控制当尝试向属于唯一聚集索引的列插入重复的键值时所发生的情况。如果为索引指定了 IGNORE_DUP_KEY，并且执行了创建重复键的 INSERT 语句，SQL Server 将发出警告消息并忽略重复的行。

STATISTICS_NORECOMPUTE

指定过期的索引统计不会自动重新计算。若要恢复自动更新统计，可执行没有 NORECOMPUTE 子句的 UPDATE STATISTICS。

重要  如果禁用分布统计的自动重新计算，可能会妨碍 SQL Server 查询优化器为涉及该表的查询选取最佳执行计划。

update STATISTICS 职工 
EXEC sp_autostats 职工, 'ON'
alter index 职工号 on 职工 rebuild with (statistics_norecompute=on)

drop index 职工.职工号

create view 职工工资1
  as select * from 职工 with check option 

create view 职工工资
  with encryption
  as select * from 职工 with check option

  drop view 职工工资2

create view 职工工资2
  with schemabinding
  as select 代码,基本工资 from dbo.职工 with check option

  drop table 职工

create unique clustered index 职工工资号 on 职工工资2(代码)

drop view 职工工资2


create default 默认基本工资 as 500
exec sp_bindefault '默认基本工资','职工.基本工资'
exec sp_unbindefault  '职工.基本工资','默认基本工资'

drop default 默认基本工资

create rule 基本工资规则 as @range>=$100 and @range<=1000

create rule 性别 as @sex in ('男','女')

exec sp_bindrule '基本工资规则','职工.基本工资'

exec sp_unbindrule '职工.基本工资','基本工资规则' 

drop rule 性别


create procedure 查询全部学生
   as select * from dbo.学生

exec 查询全部学生

drop procedure 查询全部学生


create procedure 查询学生
 @id smallint
 as
   begin 
   select * from 学生 where 学号=@id
   select * from 学生 where 学号=@id+1
   end 

exec 查询学生 '2'

drop procedure 查询学生

create trigger 查询 on 职工
  with encryption
  for insert
  as select * from 职工

drop trigger 查询

select * from 职工

insert into 职工 values('314','张思',20,'女')

select * from 学生

begin transaction
update 学生 set 年龄=年龄+1
select * from 学生

rollback transaction

create trigger 录入职工 on 职工
    for insert
    as if (select count(*)
            from 部门,inserted
            where inserted.部门代码=部门.代码         
          )<1
           rollback transaction

select * from 部门


drop trigger 录入职工
 
create trigger 录入职工1 on 职工
    after insert
    as if (select count(*)
            from 部门,inserted
            where inserted.部门代码=部门.代码         
          )>0
           rollback transaction

drop trigger 录入职工

 
create trigger 录入职工 on 职工
    instead of insert
    as if (select count(*)
            from 部门,inserted
            where inserted.部门代码=部门.代码         
          )>0
           rollback transaction

create trigger 删除部门 on 部门
     for delete
     as if (select count(*)
        from 职工,deleted
        where 职工.部门代码=deleted.代码)>0
          rollback transaction
        else
           delete 部门
            from 部门,deleted
            where 部门.代码=deleted.代码

delete from 部门 where 部门.代码=1


CREATE TRIGGER member_delete  ON member
         FOR DELETE
         AS IF (SELECT COUNT(*)
              FROM loan，deleted
              WHERE loan.member_no=deleted.member_no)>0
              ROLLBACK TRANSACTION
            ELSE
               DELETE reservation 
               From reservation,deleted
               where reservation.member_no=deleted.member_no              



insert into 部门 values('计算机','李司')

insert into 职工 values(1,'张三',500,500,1,'男')

drop trigger 查询

insert into 职工 values(2,'李三',500,500,1,'男')

declare @id int
declare @姓名 char(8)
set @id=100
set @姓名='张三'
print @id
print @姓名
go 

declare @姓名 char(8)
set @姓名=(select top 1 姓名 from 学生)
select @姓名
go

declare @minichengji  int
select @minichengji=min(成绩) from 选课 where 成绩 is not null
print @minichengji



declare @t table(id int identity,col varchar(4))
declare @sql varchar(60)
set @sql='吕布赵云马超典韦关羽张飞许褚黄忠颜良文丑庞德孙策'
declare @i int;
set @i=1
declare @n int;
set @n=2 --定义分段长度
while(@i<len(@sql))
begin
    insert into @t select substring(@sql,@i,@n)
    set @i=@i+@n
end
select * from @t
go 

declare @学生变量  table(
       学号 char(5) not null unique,
       姓名 char(8) not null,
      年龄 smallint default 20,
      性别 char(2),
      所在系 char(20))
insert into  @学生变量 select 学号,姓名,年龄,性别,所在系  from 学生
select * from  @学生变量
go

print @@language
go 

print @@version
go

print '目前SQL Server服务器名称为：'+@@SERVERNAME
go
print '目前所用服务器为：'+@@SERVICENAME
go

insert into table_1 values('杨')
print @@identity
go

update 学生 set 年龄=年龄+1
print @@rowcount
go

select * from 学生3
go
print @@error
go

declare @姓名 char(8)
select @姓名=姓名
 from 学生
 where 学号=1
print @姓名
go

declare @id int
set @id=cast('1111' as int)
print @id
go

SELECT '学号:'+cast(学号 as char(5))+'姓名：'+ 姓名+ '年龄：' + CAST(年龄 AS varchar(4))
FROM 学生


GO


declare @date1 datetime
set @date1=cast('12/7/1999' as datetime)
print @date1
go

declare @date2 datetime
set @date2=convert(datetime,'12-7-1999')
print @date2
go


declare @date2 datetime
set @date2=convert(datetime,'12-7-1999  9:10:50:333 PM')
declare @date3 char(30)
set @date3=convert(char(30),@date2,109)
print @date3
go

declare @date2 datetime
set @date2=convert(smalldatetime,'12-7-1999')
declare @date3 char(20)
set @date3=convert(char(20),@date2,104)
print @date3
go



if (
    select count(*)
     from 学生
)>2
begin
 print '学生人数大于2'
end
else
begin
print '学生人数小于等于2'
end
go

declare @countid int
set @countid=0
while (@countid<10)
begin
 set @countid=@countid+1
 print @countid
end
go

declare @countid int
set @countid=0
while (@countid<10)
begin
set @countid=@countid+1
if @countid=5   continue
if @countid=9   break
print @countid
end

DECLARE @s int,@times int  
set @s=1
set @times=1
label1:
set @s=@s*@times
set @times=@times+1
if @times<=10
    goto label1
print '结果为:'+str(@s)

/*
  注释
*/
--注释
go

declare @countid int
set @countid=0
while (@countid<10)
begin
 set @countid=@countid+1
if @countid=5
  return
 print @countid
end

select  学号,课程号,成绩=case 
                  when 成绩>60 then '及格'
                   else '不及格' 
                   end
from 选课



declare 全部学生查询 scroll cursor  for select * from 学生
open 全部学生查询
fetch next from 全部学生查询
fetch first from 全部学生查询
fetch last from 全部学生查询
close 全部学生查询

create table #临时表
(id int,
 name char(8)
)

create table ##全局临时表
(id int,
 name char(8)
)

print db_name()
print host_name()
print suser_ID()
print suser_name()
print user_ID()
print user_name()

print dateadd(mm,3,sysdatetime())
print datediff(d,cast('2015-01-01' as datetime),sysdatetime())

SELECT DATEPART(month, GETDATE())  AS  'Month Number'

SELECT MONTH('03/12/1998'), DAY('03/12/1998'),YEAR('03/12/1998')

create function student()
returns TABLE
as 
  return(select * from 学生);

drop function student

select * from student()

create function student1(@id int)
returns char(10)
as 
   begin
     return (select 姓名 from 学生 where 学号 = @id)
   end

select dbo.student1(1)

drop function student1