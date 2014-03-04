CREATE TABLE [auto_type] (
  [process_id] INTEGER, 
  [module_name] TEXT, 
  [title] TEXT, 
  [type_id] INTEGER NOT NULL ON CONFLICT ROLLBACK, 
  [priority] INTEGER NOT NULL ON CONFLICT ROLLBACK DEFAULT 0);


CREATE TABLE [record] (
  [id] INTEGER NOT NULL ON CONFLICT ROLLBACK PRIMARY KEY ON CONFLICT ROLLBACK, 
  [process_id] INTEGER NOT NULL ON CONFLICT ROLLBACK, 
  [title] TEXT NOT NULL ON CONFLICT ROLLBACK, 
  [start] INTEGER8 NOT NULL ON CONFLICT ROLLBACK DEFAULT (cast(strftime('%s','now') as integer8)*1000), 
  [last_active] INTEGER NOT NULL ON CONFLICT ROLLBACK DEFAULT (cast(strftime('%s','now') as integer8)*1000 + 500), 
  [type_id] INTEGER, 
  [module_name] TEXT NOT NULL ON CONFLICT ROLLBACK DEFAULT '');


CREATE TABLE [type] (
  [id] INTEGER NOT NULL ON CONFLICT ROLLBACK PRIMARY KEY ON CONFLICT ROLLBACK, 
  [name] TEXT NOT NULL ON CONFLICT ROLLBACK);


CREATE VIEW [total_time_by_id_and_title] AS 
select process_id, title, module_name, sum(last_active - start) / 1000.0 / 60 as total, sum(last_active - start) * 100.0 / (select sum(last_active - start) from record) as percent from
record group by process_id, module_name, title, type_id having type_id is null;


CREATE VIEW [total_time_by_type] AS 
select t.name, sum(diff) as total_time, sum(diff) * 100.0 / (select sum(last_active - start) from record where type_id is not null) as total_percent from
(select t.name, r.type_id, last_active - start as diff from record r inner join type t on r.type_id = t.id) t
group by t.type_id;


