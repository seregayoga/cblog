CREATE TABLE posts (
    id serial primary key not null,
    add_time timestamp not null default now(),
    mod_time timestamp not null default now(),
    title text not null,
    content text not null
);
