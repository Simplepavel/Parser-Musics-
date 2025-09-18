from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from DataBase.model import Base


engine1 = create_engine("sqlite+pysqlite:///DataBase.db", echo=True)


SessionLocal = sessionmaker(bind = engine1)

def create_table():
    Base.metadata.create_all(engine1)


def drop_table():
    Base.metadata.drop_all(engine1)

