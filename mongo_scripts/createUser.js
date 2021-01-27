use mydb;

db.createUser({user: "pi",pwd: "raspberry",roles: [ { role: "readWrite", db: "mydb" }]})