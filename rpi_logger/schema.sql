--Table for samples.  Right now, you have to run this manually.
CREATE TABLE Samples (
    DateTime date NOT NULL,
    NodeID int,
    Topic varchar(64),
    Value double,
    Unit varchar(16)
);