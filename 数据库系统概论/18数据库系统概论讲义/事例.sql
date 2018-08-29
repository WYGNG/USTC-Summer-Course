drop database   yjp;
create database yjp;
use yjp;
create table 学生(
   学号 char(5) not null unique,
   姓名 char(8) not null,
   年龄 smallint default 20,
   性别 char(2),
   所在系 char(20),
   constraint c2 check(性别 in ('男','女') )
   );
drop table 学生

create Table 课程(
   课程号 char(5) primary Key,
   课程名 char(20),
   先行课 char(5) 

);

create Table 选课(
   学号 char(5),
   课程号 char(5),
   成绩 smallint,
   constraint c3 check(成绩 between 0 and 100),
   constraint c4 primary key(学号,课程号),
   constraint c5 Foreign key(学号) references 学生(学号),
   constraint c6 Foreign key (课程号) references 课程(课程号)
);

alter table 课程 add 学时  smallint;

alter table 课程 add 学时1  smallint,学时2 smallint;

alter table 课程 alter column 学时 int;

alter table 学生 drop c2;

alter table 课程 drop column 学时2,学时1;

alter table 学生 add constraint c2 check(性别 in ('男','女') );

alter table 选课 drop c3;

alter table 选课 alter column 成绩 int not null;


create unique index 学号 on 学生(学号);

drop index 学生.学号;

create unique index 选课号 on 课程(课程号);

drop index 课程.选课号;

create clustered index 学号 on 学生(学号); 

create unique index 选课号 on 选课(学号 asc,课程号 desc);

create view 成绩表(学号,姓名,课程名,成绩)
  as select 学生.学号,学生.姓名,课程.课程名,选课.成绩
      from 学生,课程,选课
        where 学生.学号=选课.学号 and 课程.课程号=选课.课程号

select * from 成绩表;
select * from 成绩表 where 成绩 is not null;
select * from 成绩表 where 成绩 >=80;


create view 学生成绩(学号,姓名,课程名,成绩,所在系)
  as select 学生.学号,学生.姓名,课程.课程名,选课.成绩,学生.所在系
      from 学生,课程,选课
        where 学生.学号=选课.学号 and 课程.课程号=选课.课程号 and 学生.所在系='计算机系'

drop view 学生成绩;

select * from 学生成绩;

create view 学生成绩表(学号,总成绩,平均成绩)
  as select 学号,sum(成绩),avg(成绩)
   from 选课
   group by 学号

select * from 学生成绩表







select 学号,姓名
   from 学生
     where 所在系='计算机系';

select 学号 from 选课;

select distinct 学号 from 选课;

select all 学号 from 选课;



select 学号,成绩
   from 选课
   where 课程号='2'
    order by 成绩 desc,学号 asc;


select 学号,成绩*0.8
  from 选课
   where 课程号='2' and 成绩 between 82 and 99;

select 学号 as 学生编号,成绩*1.1 as 总评,'杨俊朋' as 任课教师
  from 选课
   where 课程号='2' and 成绩 between 60 and 90;


select * 
from 学生
where 所在系 in ('计算机系','信息系') and 姓名 like '钱%'

select * 
from 学生
where 所在系 in ('计算机系','信息系') and 姓名 like '钱_'

select * 
from 学生
where 所在系 in ('计算机系','信息系') and 姓名 like '%二'

select * 
from 学生
where (所在系='计算机系' or 所在系='信息系') and 姓名 like '%二'


select 学号,课程号
from 选课
where 成绩 is null;

select 学号,课程号,成绩
from 选课
where 成绩 is not Null;


select  学号,课程号,成绩
from 选课
where 成绩 <> '';

update 选课
set 成绩=成绩-1

select * from 选课

select 学生.*,选课.*
  from 学生,选课
  where 学生.学号=选课.学号;


select 学生.学号 as 学生号码 ,姓名 as 学生姓名,课程名,成绩
from 学生,课程,选课
where 学生.学号=选课.学号 and 选课.课程号=课程.课程号

select * from 课程

select a.课程号,a.课程名,b.课程名
from 课程 a,课程 b
where a.先行课=b.课程号

select  a.课程号,a.课程名,第一先行课=b.课程名,c.课程名 as 第二先行课
from 课程 a,课程 b,课程 c
where a.先行课=b.课程号 and b.先行课=c.课程号

select 学生.学号,姓名,选课.课程号  as 所选课,成绩
from 学生,选课
 where 学生.学号*=选课.学号

select 学号, 选课.课程号,课程名
from 选课,课程
where 选课.课程号=*课程.课程号 


select a.课程号,a.课程名,b.课程名
from 课程 a left join 课程 b on a.先行课=b.课程号


select  a.课程号,a.课程名,b.课程名 as 第一先行课,c.课程名 as 第二先行课
from 课程 a left join 课程 b on a.先行课=b.课程号 left join 课程 c on b.先行课=c.课程号


select 学号,姓名
from 学生
where 学号 in (select 学号
               from 选课
               where 课程号=(
                           select 课程号
                             from 课程
                             where 课程名='数据库'
                            ))

select 学号,成绩
from 选课
where 课程号='2' and  成绩>(
                        select 成绩
                         from 选课
                         where 课程号='2' and 学号=(select 学号 
                                                       from 学生 
                                                       where 姓名='钱二') 
                             )
select *
from 学生
where 年龄< any(select 年龄 from 学生 where 所在系='计算机系') and  所在系<>'信息系';

select *
from 学生
where 年龄< all(select 年龄 from 学生 where 所在系='计算机系') and  所在系<>'信息系';

select 学号,姓名
from 学生
where exists (select *
               from 选课
              where 学生.学号=选课.学号 and 课程号='2'
              )

select 姓名
from 学生
where not exists(
           select *
           from 选课
           where 学生.学号=学号 and 课程号='2'
)

select 学号, 姓名 
from 学生
where not exists (
           select *
           from 课程
           where not exists(select *
                 from 选课
                 where 学生.学号=学号 and 课程.课程号=课程号
                            )
                  )

select 学号, 姓名
from 学生
where not exists(select *
                 from 选课 a
                 where a.学号='2' and  not exists(select *
                                                     from 选课 b
                                                      where 学生.学号=b.学号 and a.课程号=b.课程号
                                                     )
    
               )

select 学号
from 选课
where 课程号='2'
union
select 学号
from 选课
where 课程号='3'

select 选课.学号
from 选课,(select 选课1.学号 from 选课 选课1 where 选课1.课程号='3') sc
where 选课.学号=sc.学号 and 选课.课程号='2'


select 学号
from 选课
where 课程号='2'
union all
select 学号
from 选课
where 课程号='3'


select count(*)
from 学生

select count(distinct 学号)
from 选课;

select 课程号,count(学号) as 选修人数
from 选课
group by 课程号;

select  学号,count(课程号) as 选课数
from 选课
group by 学号;

select 学号,count(课程号) as 选课数
from 选课
group by 学号 having count(*)>3;


insert 
into 学生
values('9','张九',20,'男','计算机系')

insert into 选课(学号,课程号)
values('9','1')

create table 平均成绩(学号 char(5),平均成绩 smallint);
insert
into 平均成绩
select 学号,avg(成绩)
from 选课
group by 学号

drop table 平均成绩; 

select 学号,avg(成绩) as 平均成绩
into 平均成绩
from 选课
group by 学号;

update 选课
set 成绩=成绩*0.9
where 课程号=(select 课程号
              from 课程
              where 课程名='数据库'
             )


update 选课
set 成绩=成绩/0.9
where '数据库'=(select 课程名
               from 课程
               where 选课.课程号=课程.课程号
               )

delete from 选课 where 学号='9';
delete from 学生 where 学号='9';

delete from 选课
where 学号 in (select 学号
               from 学生
               where 所在系='信息系')

grant create table to yang

revoke create table from yang

grant select on 学生(学号,姓名) to yang with grant option

grant select on 学生 to yang with grant option

revoke grant option for select  on 学生  from yang cascade

revoke select on 学生 from  yang

grant all on 选课 to yjp

grant update(成绩) on 选课 to yjp
revoke update(成绩) on 选课 from yjp

revoke all on 选课 from yjp

update 选课
set 成绩=成绩+1

revoke all on 选课 from yang
deny all on 选课 to yang

select 选课1.学号
from 选课 选课1,选课 选课2
where 选课1.课程号='2' and 选课2.课程号='3' and 选课1.成绩>选课2.成绩 and 选课1.学号=选课2.学号